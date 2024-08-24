gi#pragma once
#include "core/Board.hpp"
#include <functional>
#include <memory>
#include <random>


namespace plut::core {

class SlotBase;

// TODO: event driven

// add states
enum WinCollectionPassResult {
  endWin = 0,
  fillBoard = 1,
  respin = 2
};

using RandEngineRef = std::shared_ptr<std::mt19937_64>;
// FIXME: GenerationPass is void 0_0
using GenerationPass =
    std::function<void(SlotBase&, const RandEngineRef&)>;
using WinCollectionPass = std::function<WinCollectionPassResult(SlotBase&)>;
using TraversalPath = std::vector<std::pair<int, int>>;

} // namespace plut::core
