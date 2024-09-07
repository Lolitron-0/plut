#include "Runner.hpp"
#include "Measurer.hpp"

namespace plut::benchmark {

int Runner::s_IdCounter{ 0 };

Runner::Runner(SessionOptions opts,
               const std::shared_ptr<core::SlotBase>& instance,
               Measurer* supervisor)
    : m_Id{ s_IdCounter++ },
      m_SessionOptions{ std::move(opts) },
      m_SlotInstance{ std::make_unique<core::SlotBase>(*instance) },
      m_Supervisor{ supervisor } {
}

auto Runner::getId() const -> int {
  return m_Id;
}

void Runner::run() {
  m_ShouldStop = false;
  m_Thread     = std::make_unique<std::thread>([this] {
    while (!m_ShouldStop) {
      m_SlotInstance->spin();
      m_CurrentStatsBatch.numSpins++;
      m_CurrentStatsBatch.sumWins +=
          m_SlotInstance->getCurrentPayoutBetMultiplier();

      if (m_CurrentStatsBatch.numSpins >= s_StatsBatchSize) {
        m_Supervisor->addBatch(std::move(m_CurrentStatsBatch));
        m_CurrentStatsBatch = {};
      }
    }
  });
}

void Runner::stop() {
  m_ShouldStop = true;
  m_Thread->join();
}

} // namespace plut::benchmark
