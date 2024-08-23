#pragma once
#include "Symbol.hpp"
#include "core/ContiguousMatrix.hpp"

namespace plut::core {

class Board {
public:
  Board(std::size_t maxRows, std::size_t maxCols);

  [[nodiscard]] auto getCurrentState() const
      -> const ContiguousDynamicMatrix<Symbol>&;
  [[nodiscard]] auto getCurrentState()
      -> ContiguousDynamicMatrix<Symbol>&;

  void resetState() { std::ranges::fill(m_CurrentState, Symbol{}); }

  auto operator[](std::size_t i)
      -> ContiguousDynamicMatrix<Symbol>::RowProxy<
          ContiguousDynamicMatrix<Symbol>&> {
    return m_CurrentState[i];
  }
  auto operator[](std::size_t i) const
      -> ContiguousDynamicMatrix<Symbol>::RowProxy<
          const ContiguousDynamicMatrix<Symbol>&> {
    return m_CurrentState[i];
  }

  [[nodiscard]] auto getSize() const { return m_CurrentState.getSize(); }

private:
  ContiguousDynamicMatrix<Symbol> m_CurrentState;
};

} // namespace plut::core
