#include "core/SlotBase.hpp"

namespace plut::core {

SlotBase::SlotBase(std::initializer_list<Reel> reels)
    : m_Board{ reels } {
  std::random_device rd;
  m_RandEngine.seed(rd());
}

void SlotBase::addSymbols(std::vector<Symbol>&& symbols) {
  m_Symbols = std::move(symbols);
}

void SlotBase::spin() {
  m_Board.resetState();
  for (int i{ 0 }; i < m_Board.getReels().size(); i++) {
    std::uniform_int_distribution<int> rnd{
      0, static_cast<int>(m_Board.getReels()[i].getSymbols().size() -
                          m_Board.getReels()[i].getSpanSize() - 1)
    };
    m_Board.setReelPos(i, rnd(m_RandEngine));
  }
}

auto SlotBase::getBoardState() const
    -> const ContiguousDynamicMatrix<Symbol>& {
  return m_Board.getCurrentState();
}
} // namespace plut::core
