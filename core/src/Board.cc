#include "core/Board.hpp"

namespace plut::core {

Board::Board(std::size_t maxRows, std::size_t maxCols)
    : m_CurrentState{ maxRows, maxCols } {}

auto Board::getCurrentState() const
    -> const ContiguousDynamicMatrix<Symbol>& {
  return m_CurrentState;
}
} // namespace plut::core
