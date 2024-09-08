#pragma once
#include "SessionOptions.hpp"
#include "plut.hpp"

namespace plut::benchmark {

class Measurer;

struct RunnerStatsBatch {
  int numSpins{ 0 };
  float sumWins{ 0 };
};

class Runner {
public:
  Runner(SessionOptions opts,
         const std::shared_ptr<core::SlotBase>& instance,
         Measurer* supervisor);

  [[nodiscard]] auto getId() const -> int;

  void run();
  void stop();

private:
  int m_Id;
  bool m_ShouldStop;
  SessionOptions m_SessionOptions;
  RunnerStatsBatch m_CurrentStatsBatch;
  std::unique_ptr<core::SlotBase> m_SlotInstance; // copy
  std::unique_ptr<std::thread> m_Thread;
  Measurer* m_Supervisor;

  static int s_IdCounter;
  static constexpr int s_StatsBatchSize{
#ifdef NDEBUG
    10'000
#else
    100
#endif
  };
};

} // namespace plut::benchmark
