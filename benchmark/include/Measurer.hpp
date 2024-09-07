#pragma once
#include "Runner.hpp"
#include "SessionOptions.hpp"
#include "plut.hpp"
#include <queue>

namespace plut::benchmark {

struct ExperimentStats {
  int totalTrials{ 0 };
  int trialSpins{ 0 };
  int totalSpins{ 0 };
  float calculatedRTP{ 0 };
};

class Measurer : std::enable_shared_from_this<Measurer> {
public:
  friend class Runner;

  explicit Measurer(SessionOptions opts);
  ~Measurer();

  void startExperiment(
      const std::shared_ptr<core::SlotBase>& slotInstance);
  void stop();

private:
  void addBatch(RunnerStatsBatch batch);

  void _mergeStats();

private:
	bool m_Running{true};
  SessionOptions m_Opts;
  ExperimentStats m_Stats;
  std::vector<std::unique_ptr<Runner>> m_Runners;
  std::queue<RunnerStatsBatch> m_StatBatches;
  std::mutex m_BatchQueueMutex;

  constexpr static int s_UpdateSleepMs{ 1000 };
};

} // namespace plut::benchmark
