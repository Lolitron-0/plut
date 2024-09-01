#include "core/PassPresets.hpp"
#include "core/Assert.h"
#include "core/SlotBase.hpp"

namespace plut::core::PassPresets {

namespace Fill {

auto uniformRandomizeBoardPassImpl(
    SlotBase& slot, const RandEngineRef& randEngineRef) -> void {
  CORE_ASSERT(slot.getSymbols().size() > 0,
              "No symbols to generate from");

  auto [rows, cols]{ slot.board.getSize() };
  std::uniform_int_distribution<std::size_t> distrib{
    0, slot.getSymbols().size() - 1
  };
  for (int i{ 0 }; i < rows; i++) {
    for (int j{ 0 }; j < cols; j++) {
      if (!slot.board[i][j].isEmpty() || slot.board[i][j].isDisabled()) {
        continue;
      }
      auto rnd{ distrib(*randEngineRef) };
      slot.board[i][j] = slot.getSymbols()[rnd];
    }
  }
}

auto Manager::getUniformRandomizeBoardPass() -> FillPass {
  return uniformRandomizeBoardPassImpl;
}

} // namespace Fill

namespace WinCollection {

static auto winLinesInBounds(
    const SlotBase& slot, const std::vector<WinLine>& winLines) -> bool {
  return std::ranges::all_of(winLines, [&slot](const auto& winLine) {
    if (!winLine.startPoint) {
      return true; // no start point lines won't go off bounds
    }
    auto [i, j]{ winLine.startPoint.value() };
    for (const auto& edge : winLine.path.edges) {
      i += edge.i;
      j += edge.j;
      if (!slot.board.inBounds(i, j)) {
        return false;
      }
    }
    return true;
  });
}

static auto countLineFrom(SlotBase& slot, const WinLine& winLine, int i,
                          int j) -> int {
  auto lineSymbol{ slot.board[i][j] };
  int counter{ 1 };

  for (const auto& edge : winLine.path.edges) {
    i += edge.i;
    j += edge.j;
    if (slot.board.inBounds(i, j) && slot.board[i][j] == lineSymbol) {
      counter++;
    } else {
      return counter;
    }
  }
  return counter;
}

static auto winLinePassImpl(SlotBase& slot,
                            const std::vector<WinLine>& winLines)
    -> WinCollectionPassResult {
  CORE_ASSERT(winLinesInBounds(slot, winLines),
              "WinLine goes out of bounds");

  auto [rows, cols]{ slot.board.getSize() };
  for (const auto& winLine : winLines) {
    auto startPos{ winLine.startPoint.value_or(Offset2D{ 0, 0 }) };
    bool strictStart{ winLine.startPoint.has_value() };

    for (int startOffI{ startPos.i }; startOffI < rows; startOffI++) {
      for (int startOffJ{ startPos.j }; startOffJ < rows; startOffJ++) {
        // for each starting point
        auto counter{ countLineFrom(slot, winLine, startOffI,
                                    startOffJ) };

        if (counter >= winLine.minSymbols) {
          // TODO: paytable as parameter
          slot.addToPayoutMultiplier(counter);
        }

        if (strictStart) {
          goto winlineBreak;
        }
      }
    }
  winlineBreak:;
  }
  return WinCollectionPassResult::nextPass;
}

auto Manager::getWinLinesPass(const std::vector<WinLine>& winLines)
    -> WinCollectionPass {
  return [winLines](SlotBase& slot) {
    return winLinePassImpl(slot, winLines);
  };
}

} // namespace WinCollection

} // namespace plut::core::PassPresets
