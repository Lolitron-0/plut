#include "core/Reel.hpp"

namespace plut::core {

Reel::Reel(int spanSize, std::initializer_list<Symbol> symbols)
    : m_SpanSize{ spanSize },
      m_Symbols{ symbols } {
  if (m_SpanSize > m_Symbols.size()) {
    throw ReelTooSmallException{};
  }
}

auto Reel::getSymbols() const -> const ReelBuffer& { return m_Symbols; }
auto Reel::getSpanSize() const -> int { return m_SpanSize; }

} // namespace plut::core
