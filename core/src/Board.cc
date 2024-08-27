#include "core/Board.hpp"

namespace plut::core {

Board::Board(std::size_t maxRows, std::size_t maxCols)
    : m_CurrentState{ maxRows, maxCols } {}

void Board::resetState() { std::ranges::fill(m_CurrentState, Symbol{}); }

auto Board::getSize() const -> BoardMatrix::Dimensions {
  return m_CurrentState.getSize();
}

} // namespace plut::core
