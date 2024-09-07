#include "core/Board.hpp"
#include <algorithm>

namespace plut::core {

Board::Board(std::size_t maxRows, std::size_t maxCols)
    : m_CurrentState{ maxRows, maxCols } {
}

void Board::resetState() {
  std::ranges::for_each(m_CurrentState, [](auto& cell) {
    cell.setContent(std::nullopt);
  });
}

auto Board::getSize() const -> BoardMatrix::Dimensions {
  return m_CurrentState.getSize();
}

auto Board::inBounds(std::size_t i, std::size_t j) const -> bool {
  return m_CurrentState.inBounds(i, j);
}
} // namespace plut::core
