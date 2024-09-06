#pragma once
#include <string>

namespace plut::benchmark {

struct SessionOptions {
  int spinsPerTrial{ 1'000'000 };
  int maxTrials{ -1 };
	std::string pathToSlot;
};

} // namespace plut::benchmark
