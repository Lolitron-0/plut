#include "core/SlotBase.hpp"
#include "core/Assert.h"
#include "core/SymbolManager.hpp"
#include <list>

namespace plut::core {

SlotBase::SlotBase(std::size_t maxRows, std::size_t maxCols)
    : board{ maxRows, maxCols },
      m_SymbolManager{ std::make_shared<SymbolManager>() } {}

auto SlotBase::getCurrentPayoutBetMultiplier() const -> float {
  return m_CurrentPayoutBetMultiplier;
}

void SlotBase::addToPayoutMultiplier(float value) {
  m_CurrentPayoutBetMultiplier += value;
}

void SlotBase::spin() {
  _resetState();

  _fillBoard();

  // TODO: what if a few states appear simutaneously
  bool winCollectionInvalidated{ true };
  std::list<std::function<void(void)>> afterPassJobs;

  while (winCollectionInvalidated) {
    winCollectionInvalidated = false; // assume this is final collection

    for (auto&& winCollectionPass : m_WinCollectionPasses) {
      auto passResult{ std::invoke(winCollectionPass, *this) };

      switch (passResult) {
      case WinCollectionPassResult::nextPass:
        break;

      case WinCollectionPassResult::endWin:
        goto breakWinCollection;
        break;

      case WinCollectionPassResult::fillBoardInstantly:
        winCollectionInvalidated = true;
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

void SlotBase::clearFillPasses() { m_FillPasses.clear(); }

void SlotBase::clearWinCollectionPasses() {
  m_WinCollectionPasses.clear();
}

void SlotBase::registerFillPass(const FillPass& newPass) {
  m_FillPasses.push_back(newPass);
}

void SlotBase::registerWinCollectionPass(
    const WinCollectionPass& newPass) {
  m_WinCollectionPasses.push_back(newPass);
}

void SlotBase::_resetState() {
  board.resetState();
  m_CurrentPayoutBetMultiplier = 0;
}

void SlotBase::_fillBoard() {
  for (auto&& fillPass : m_FillPasses) {
    std::invoke(fillPass, *this);
  }
}

auto SlotBase::getTraversalPath() const -> TraversalPath {
  return m_TraversalPath;
}
void SlotBase::setTraversalPath(const TraversalPath& traversalPath) {
  m_TraversalPath = traversalPath;
};
auto SlotBase::getSymbolManager() const -> SymbolManagerRef {
  return m_SymbolManager;
}

} // namespace plut::core
