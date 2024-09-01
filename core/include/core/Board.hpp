#pragma once
#include "Symbol.hpp"
#include "core/ContiguousMatrix.hpp"

namespace plut::core {

class Board {
public:
  using BoardMatrix = ContiguousDynamicMatrix<Symbol>;

  Board(std::size_t maxRows, std::size_t maxCols);

  void resetState();

  constexpr auto operator[](std::size_t i)
      -> BoardMatrix::RowProxy<BoardMatrix&> {
    return m_CurrentState[i];
  }
  constexpr auto operator[](std::size_t i) const
      -> BoardMatrix::RowProxy<const BoardMatrix&> {
    return m_CurrentState[i];
  }

  [[nodiscard]] auto getSize() const -> BoardMatrix::Dimensions;
  [[nodiscard]] auto inBounds(std::size_t i, std::size_t j) const -> bool;

private:
  BoardMatrix m_CurrentState;
};

} // namespace plut::core
