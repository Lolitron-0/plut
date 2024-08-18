#include "core/Board.hpp"
#include <algorithm>

namespace plut::core {

Board::Board(std::initializer_list<Reel> reels)
    : m_Reels{ reels },
      m_CurrentState(std::ranges::max_element(reels,
                                              [](auto&& r1, auto&& r2) {
                                                return r1.getSpanSize() <
                                                       r2.getSpanSize();
                                              })
                         ->getSpanSize(),
                     reels.size()) {}

auto Board::getReels() const -> const std::vector<Reel>& {
  return m_Reels;
}
auto Board::getCurrentState() const
    -> const ContiguousDynamicMatrix<Symbol>& {
  return m_CurrentState;
}
} // namespace plut::core
