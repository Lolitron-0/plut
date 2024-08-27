#pragma once
#include "core/Board.hpp"
#include <functional>
#include <memory>
#include <random>


namespace plut::core {

class SlotBase;

// TODO: event driven

// TODO: maybe add states
enum WinCollectionPassResult {
  endWin = 0,
  fillBoardInstantly = 1,
  fillBoardAfterPass = 2,
  respin = 3
};

using RandEngineRef = std::shared_ptr<std::mt19937_64>;
using FillPass =
    std::function<void(SlotBase&, const RandEngineRef&)>;
using WinCollectionPass = std::function<WinCollectionPassResult(SlotBase&)>;
using TraversalPath = std::vector<std::pair<int, int>>;

} // namespace plut::core
