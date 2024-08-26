#include "core/SlotBase.hpp"

namespace plut::core {

SlotBase::SlotBase(std::size_t maxRows, std::size_t maxCols)
    : board{ maxRows, maxCols } {
  std::random_device rd;
  m_RandEngine = std::make_shared<std::mt19937_64>(rd());
}

void SlotBase::setSymbols(std::vector<Symbol>&& symbols) {
  m_Symbols = std::move(symbols);
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
} // namespace plut::core
