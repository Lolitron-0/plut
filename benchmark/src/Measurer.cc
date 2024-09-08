#include "Measurer.hpp"
#include "BenchmarkLogger.hpp"
#include "Runner.hpp"
#include <utility>

namespace plut::benchmark {

Measurer::Measurer(const SessionOptions& opts)
    : m_Opts{ opts },
      m_Renderer{ opts } {
}

Measurer::~Measurer() {
  if (m_Running) {
    stop();
  }
}

void Measurer::startExperiment(
    const std::shared_ptr<core::SlotBase>& slotInstance) {
  m_Running = true;

  // supervisor thread does not count
  for (int i{ 0 }; i < m_Opts.numJobs; i++) {
    m_Runners.push_back(
        std::make_unique<Runner>(m_Opts, slotInstance, this));
    m_Runners.back()->run();
    BenchmarkLogger().trace("Started runner #{}", i);
  }
  m_Stats.uptimeSW.reset();

  m_Renderer.startTUIThread();
  BenchmarkLogger().info("Started UI threads");

  while (m_Running && (m_Opts.maxTrials == -1 ||
                       m_Stats.totalTrials < m_Opts.maxTrials)) {
    while (m_Running && m_Stats.trialSpins < m_Opts.spinsPerTrial) {
      // BenchmarkLogger().debug("RTP: {:.2f}%; Spins: {}",
      //                         m_Stats.calculatedRTP * 100.F,
      //                         m_Stats.totalSpins);
      m_Renderer.sendStats(m_Stats);

      _mergeStats();
      std::this_thread::sleep_for(
          std::chrono::milliseconds{ s_UpdateSleepMs });
    }

    m_Stats.totalTrials++;
    m_Stats.trialSpins = 0;
  }
}

void Measurer::addBatch(RunnerStatsBatch batch) {
  std::lock_guard lock{ m_BatchQueueMutex };
  m_BatchQueue.push(std::move(batch));
};

void Measurer::_mergeStats() {
  m_BatchQueueMutex.lock();
  auto batchesToMerge{ m_BatchQueue };
  {
    std::queue<RunnerStatsBatch> empty{};
    std::swap(m_BatchQueue, empty);
  }
  m_BatchQueueMutex.unlock();

  m_Stats.valid = m_Stats.valid || !batchesToMerge.empty();

  while (!batchesToMerge.empty()) {
    auto batch{ batchesToMerge.front() };
    batchesToMerge.pop();

    auto curSpins{ m_Stats.totalSpins + m_Stats.trialSpins };
    m_Stats.calculatedRTP =
        (m_Stats.calculatedRTP * curSpins + batch.sumWins) /
        static_cast<float>(curSpins + batch.numSpins);
    m_Stats.totalSpins += batch.numSpins;
  }

  m_Stats.spinsPerSec = m_Stats.totalSpins /
                        (m_Stats.uptimeSW.elapsed_ms().count() / 1000.);
}

void Measurer::stop() {
  m_Running = false;
  for (auto& runner : m_Runners) {
    runner->stop();
  }
  m_Renderer.stop();
}

} // namespace plut::benchmark
