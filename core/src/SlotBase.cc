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

<<<<<<< HEAD
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
=======
generation:;
  for (auto&& generationPass : m_GenerationPasses) {
    auto result{ std::invoke(generationPass, *this, m_RandEngine) };
    if (result.rerunGeneration) {
      goto generation;
    }
  }

  for (auto&& winCollectionPass : m_WinCollectionPasses) {
    auto result{ std::invoke(winCollectionPass, *this) };
    if (result.rerunGeneration) {
      goto generation;
    }
    if (result.endWinCollection) {
      break;
    }
  }
>>>>>>> users/Lolitron-0
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
