#include "core/Symbol.hpp"
#include "core/Assert.h"

namespace plut::core {

Symbol::Symbol(char tag)
    : m_Tag{ tag } {}

Symbol::Symbol(char tag, float probabilityWeight)
    : m_Tag{ tag },
      m_Probability{ probabilityWeight } {
  CORE_ASSERT(probabilityWeight >= 0.F && probabilityWeight <= 1.F,
              "Probability must be in [0;1] range");
}

auto Symbol::operator==(const Symbol& symbol) const -> bool {
  return (this->m_Tag == symbol.m_Tag);
}

auto Symbol::operator<(const Symbol& symbol) const -> bool {
  return (this->m_Tag < symbol.m_Tag);
}

auto Symbol::getTag() const -> char { return m_Tag; }

auto Symbol::getProbability() const -> float {
  return m_Probability;
}

} // namespace plut::core
