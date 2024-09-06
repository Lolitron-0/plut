#pragma once
#include <functional>
#include <memory>
#include <random>

namespace plut::core {

class SlotBase;
class SymbolManager;

// TODO: event driven

// TODO: maybe add states
enum class WinCollectionPassResult {
  nextPass = 0,
  endWin,
  fillBoardInstantly,
  fillBoardAfterPass,
  respin,
  numResults
};

using FillPass = std::function<void(SlotBase&)>;
using WinCollectionPass =
    std::function<WinCollectionPassResult(SlotBase&)>;

using RandEngineRef    = std::shared_ptr<std::mt19937_64>;
using TraversalPath    = std::vector<std::pair<int, int>>;
using SymbolManagerRef = std::shared_ptr<SymbolManager>;

} // namespace plut::core
