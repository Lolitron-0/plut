#include "core/SlotBase.hpp"
#include "core/Assert.h"
#include "core/Symbol.hpp"
#include <algorithm>
#include <list>
#include <set>

namespace plut::core {

SlotBase::SlotBase(std::size_t maxRows, std::size_t maxCols)
    : board{ maxRows, maxCols } {
  std::random_device rd;
  m_RandEngine = std::make_shared<std::mt19937_64>(rd());
}

void SlotBase::setSymbols(const std::vector<Symbol>& symbols) {
  CORE_ASSERT(std::set(symbols.begin(), symbols.end()).size() ==
                  symbols.size(),
              "Slot contains repeating symbols");
  m_Symbols = symbols;
}

void SlotBase::addSymbol(const Symbol& symbol) {
  CORE_ASSERT(std::ranges::find(m_Symbols, symbol) == m_Symbols.end(),
              "Slot contains repeating symbols");
  m_Symbols.push_back(symbol);
}

void SlotBase::spin() {
  board.resetState();

  _fillBoard();

  // TODO: what if a few states appear simutaneously
  bool winCollectionInvalidated{ true };
  std::list<std::function<void(void)>> afterPassJobs;

  while (winCollectionInvalidated) {
    winCollectionInvalidated = false; // assume this is final collection

    for (auto&& winCollectionPass : m_WinCollectionPasses) {
      auto passResult{ std::invoke(winCollectionPass, *this) };

      switch (passResult) {
      case WinCollectionPassResult::endWin:
        goto breakWinCollection;
        break;

      case WinCollectionPassResult::fillBoardInstantly:
        _fillBoard();
        break;

      case WinCollectionPassResult::fillBoardAfterPass:
        winCollectionInvalidated = true;
        afterPassJobs.emplace_back([&] {
          _fillBoard();
        });
        break;

      case WinCollectionPassResult::respin:
        winCollectionInvalidated = true;
        afterPassJobs.emplace_back([&] {
          board.resetState();
          _fillBoard();
        });
        break;

      default:
        CORE_ASSERT(false, "Unhandled pass result");
      }
    }
  breakWinCollection:;

    for (auto&& afterPassJob : afterPassJobs) {
      std::invoke(afterPassJob);
    }
    afterPassJobs.clear();
  }
}

void SlotBase::registerFillPass(const FillPass& newPass) {
  m_FillPasses.push_back(newPass);
}

void SlotBase::registerWinCollectionPass(
    const WinCollectionPass& newPass) {
  m_WinCollectionPasses.push_back(newPass);
}

void SlotBase::_fillBoard() {
  for (auto&& fillPass : m_FillPasses) {
    std::invoke(fillPass, *this, m_RandEngine);
  }
}

auto SlotBase::getTraversalPath() const -> TraversalPath {
  return m_TraversalPath;
}
void SlotBase::setTraversalPath(const TraversalPath& traversalPath) {
  m_TraversalPath = traversalPath;
};
auto SlotBase::getSymbols() const -> std::vector<Symbol> {
  return m_Symbols;
}

} // namespace plut::core
