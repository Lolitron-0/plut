#pragma once
#include "Symbol.hpp"
#include "core/ContiguousMatrix.hpp"

namespace plut::core {

class Board {
public:
  Board(std::size_t maxRows, std::size_t maxCols);

  [[nodiscard]] auto getCurrentState() const
      -> const ContiguousDynamicMatrix<Symbol>&;

  void resetState() { std::ranges::fill(m_CurrentState, Symbol{}); }

private:
  ContiguousDynamicMatrix<Symbol> m_CurrentState;
};

} // namespace plut::core
