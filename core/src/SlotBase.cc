#include "core/SlotBase.hpp"

namespace plut::core {

SlotBase::SlotBase(std::size_t maxRows, std::size_t maxCols)
    : m_Board{ maxRows, maxCols } {
  std::random_device rd;
  m_RandEngine = std::make_shared<std::mt19937_64>(rd());
}

void SlotBase::addSymbols(std::vector<Symbol>&& symbols) {
  m_Symbols = std::move(symbols);
}

void SlotBase::spin() {
  board.resetState();

  auto generateBoard = [this]() {
    for (auto&& generationPass : m_GenerationPasses) {
      std::invoke(generationPass, *this, m_RandEngine);
    }
  };

  bool end{ true };
  do {
    for (auto&& winCollectionPass : m_WinCollectionPasses) {
      auto result{ std::invoke(winCollectionPass, *this) };
      if (result == WinCollectionPassResult::fillBoard) {
        generateBoard();
      } else if (result == WinCollectionPassResult::respin) {
        generateBoard();
        end = false;
      } else { // why even to have result endWin?
      }
    }
  } while (end);
}

void SlotBase::registerGenerationPass(const GenerationPass& newPass) {
  m_GenerationPasses.push_back(newPass);
}

void SlotBase::registerWinCollectionPass(
    const WinCollectionPass& newPass) {
  m_WinCollectionPasses.push_back(newPass);
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
