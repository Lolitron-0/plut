#pragma once
#include "core/ContiguousMatrix.hpp"
#include "core/Reel.hpp"

namespace plut::core {

class Board {
public:
  Board(std::initializer_list<Reel> reels);

  [[nodiscard]] auto getReels() const -> const std::vector<Reel>&;
  [[nodiscard]] auto
  getCurrentState() const -> const ContiguousDynamicMatrix<Symbol>&;

  void resetState() { std::ranges::fill(m_CurrentState, Symbol{}); }
  void setReelPos(int reelNum, int reelPos) {
    for (int i{ 0 }; i < m_Reels[reelNum].getSpanSize(); i++) {
      m_CurrentState[i][reelNum] =
          m_Reels[reelNum].getSymbols()[reelPos + i];
    }
  }

private:
  std::vector<Reel> m_Reels;
  ContiguousDynamicMatrix<Symbol> m_CurrentState;
};

} // namespace plut::core
