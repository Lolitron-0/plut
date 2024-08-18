#include "core/SlotBase.hpp"

namespace plut::core {

SlotBase::SlotBase(size_t rows, size_t columns) : m_Board{rows, columns} {
  std::random_device rd;
  m_RandEngine.seed(rd());
}

void SlotBase::setSymbols(std::vector<Symbol>&& symbols) {
  m_Symbols = std::move(symbols);
}

void SlotBase::spin() {
  auto [rows, cols]{m_Board.getSize()};
  std::uniform_int_distribution<size_t> range{0, m_Symbols.size() - 1};
  for (int i{0}; i < rows; i++) {
    for (int j{0}; j < cols; j++) {
      m_Board[i][j] = m_Symbols[range(m_RandEngine)];
    }
  }
}

auto SlotBase::getBoard() const
    -> const ContiguousDynamicMatrix<Symbol>& {
  return m_Board;
}
} // namespace plut::core
