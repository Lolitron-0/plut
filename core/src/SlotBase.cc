#include "core/SlotBase.hpp"
#include "core/Assert.h"
#include "core/Symbol.hpp"
#include <set>

namespace plut::core {

SlotBase::SlotBase(std::size_t maxRows, std::size_t maxCols)
    : board{ maxRows, maxCols } {
  std::random_device rd;
  m_RandEngine = std::make_shared<std::mt19937_64>(rd());
}

void SlotBase::setSymbols(std::vector<Symbol>&& symbols) {
  CORE_ASSERT(symbolsUniqueSet(symbols),
              "Slot contains repeating symbols");
  // TODO: move anyway or return?
  m_Symbols = std::move(symbols);
}

void SlotBase::addSymbol(Symbol&& symbol) {
  CORE_ASSERT(symbolsUniqueAdd(symbol),
              "Slot contains repeating symbols");
  m_Symbols.emplace_back(symbol);
}

void SlotBase::spin() {
  board.resetState();

  // states
  // TODO: what if a few states appear simutaniously
  bool fillBoard{ false };
  bool respin{ false };

  do {
    do {
      _generateBoard();

      for (auto&& winCollectionPass : m_WinCollectionPasses) {
        auto passResult{ std::invoke(winCollectionPass, *this) };
        switch (passResult) {
        case WinCollectionPassResult::endWin:
          break;

        case WinCollectionPassResult::fillBoardInstantly:
          _generateBoard();
          break;

        case WinCollectionPassResult::fillBoardAfterPass:
          fillBoard = true;
          break;

        case WinCollectionPassResult::respin:
          respin = true;
          break;

        default:
          break;
        }
      }
    } while (fillBoard);
  } while (respin);
}

void SlotBase::registerGenerationPass(const GenerationPass& newPass) {
  m_GenerationPasses.push_back(newPass);
}

void SlotBase::registerWinCollectionPass(
    const WinCollectionPass& newPass) {
  m_WinCollectionPasses.push_back(newPass);
}

void SlotBase::_generateBoard() {
  for (auto&& generationPass : m_GenerationPasses) {
    std::invoke(generationPass, *this, m_RandEngine);
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

auto SlotBase::symbolsUniqueSet(const std::vector<Symbol>& symbols) const -> bool {
  std::set<Symbol> seen{};

  for (const Symbol& s : symbols) {
    if (seen.contains(s) != 0) {
      return false;
    }
    seen.insert(s);
  }
  return true;
}

auto SlotBase::symbolsUniqueAdd(const Symbol& symbol) const -> bool {
  std::set<Symbol> seen{m_Symbols.begin(), m_Symbols.end()};
  return seen.contains(symbol);
}

} // namespace plut::core
