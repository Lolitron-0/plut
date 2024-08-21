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

void SlotBase::spin() { m_Board.resetState(); }

auto SlotBase::getBoardState() const
    -> const ContiguousDynamicMatrix<Symbol>& {
  return m_Board.getCurrentState();
}
} // namespace plut::core
