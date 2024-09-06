#pragma once
#include "SessionOptions.hpp"
#include "plut.hpp"

namespace plut::benchmark {

class Measurer {
public:
  explicit Measurer(SessionOptions opts, const std::shared_ptr<core::SlotBase>& slotInstance);

private:
  SessionOptions m_Opts;
	std::shared_ptr<core::SlotBase> m_SlotInstance;
};

} // namespace plut::benchmark
