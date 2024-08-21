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
  _resetState();

generation:;
  for (auto&& generationPass : m_GenerationPasses) {
    auto result{ std::invoke(generationPass, m_Board) };
    if (result.rerunGeneration) {
      goto generation;
    }
  }

  for (auto&& winCollectionPass : m_WinCollectionPasses) {
    auto result{ std::invoke(winCollectionPass, m_Board) };
    if (result.rerunGeneration) {
      goto generation;
    }
    if (result.endWinCollection) {
      break;
    }
  }
}

auto SlotBase::getBoardState() const
    -> const ContiguousDynamicMatrix<Symbol>& {
  return m_Board.getCurrentState();
}

void SlotBase::_resetState() { m_Board.resetState(); }

void SlotBase::registerGenerationPass(const GenerationPass& newPass) {
  m_GenerationPasses.push_back(newPass);
}

void SlotBase::registerWinCollectionPass(
    const WinCollectionPass& newPass) {
  m_WinCollectionPasses.push_back(newPass);
}

} // namespace plut::core
