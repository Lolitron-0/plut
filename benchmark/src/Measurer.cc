#include "Measurer.hpp"
#include "BenchmarkLogger.hpp"
#include <utility>

namespace plut::benchmark {

Measurer::Measurer(SessionOptions opts,
                   const std::shared_ptr<core::SlotBase>& slotInstance)
    : m_Opts{ std::move(opts) },
      m_SlotInstance(slotInstance) {
  BenchmarkLogger().info("Measurer initialized");
}

} // namespace plut::benchmark
