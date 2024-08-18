#pragma once
#include "core/ContiguousMatrix.hpp"
#include "core/Symbol.hpp"
#include "core/Board.hpp"
#include <random>

namespace plut::core {

class SlotBase {
public:
  SlotBase(std::initializer_list<Reel> reels);

  [[nodiscard]] auto getBoardState() const -> const ContiguousDynamicMatrix<Symbol>&;
  void addSymbols(std::vector<Symbol>&& symbols);

  void spin();

private:
  Board m_Board;
  std::vector<Symbol> m_Symbols;
  std::mt19937_64 m_RandEngine;
};

} // namespace plut::core
