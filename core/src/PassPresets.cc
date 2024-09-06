#include "core/PassPresets.hpp"
#include "core/Assert.h"
#include "core/SlotBase.hpp"
#include "core/SymbolManager.hpp"

namespace plut::core::PassPresets {

namespace Fill {

auto weightedRandomizeBoardPassImpl(SlotBase& slot) -> void {

  auto [rows, cols]{ slot.board.getSize() };
  for (int i{ 0 }; i < rows; i++) {
    for (int j{ 0 }; j < cols; j++) {
      if (!slot.board[i][j].shouldFill()) {
        continue;
      }

      slot.board[i][j].setContent(
          slot.getSymbolManager()->selectRandomSymbol());
    }
  }
}

auto Manager::getWeightedRandomizeBoardPass() -> FillPass {
  return weightedRandomizeBoardPassImpl;
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
  auto lineSymbol{ slot.board[i][j].value() };
  int counter{ 1 };

  for (const auto& edge : winLine.path.edges) {
    i += edge.i;
    j += edge.j;
    if (slot.board.inBounds(i, j) &&
        slot.board[i][j].value() == lineSymbol) {
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
              "Some winLines go out of bounds");

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
