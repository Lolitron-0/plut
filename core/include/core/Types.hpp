#pragma once
#include "core/Board.hpp"
#include <functional>
#include <memory>
#include <random>


namespace plut::core {

class SlotBase;

// TODO: event driven
struct GenerationPassResult {
  bool rerunGeneration{ false };
};

struct WinCollectionPassResult {
  bool rerunGeneration{ false };
  bool endWinCollection{ false };
};

using RandEngineRef = std::shared_ptr<std::mt19937_64>;
using GenerationPass =
    std::function<GenerationPassResult(SlotBase&, const RandEngineRef&)>;
using WinCollectionPass = std::function<WinCollectionPassResult(Board&)>;
using TraversalPath = std::vector<std::pair<int, int>>;

} // namespace plut::core
