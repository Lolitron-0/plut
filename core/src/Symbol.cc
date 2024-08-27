#include "core/Symbol.hpp"

namespace plut::core {

Symbol::Symbol()
    : Symbol{ ' ' } {
  m_Empty = true;
}

Symbol::Symbol(char tag)
    : m_Tag{ tag },
      m_Empty{ true } {}

auto Symbol::operator==(const Symbol& symbol) const -> bool {
  return (this->m_Tag == symbol.m_Tag);
}

auto Symbol::operator<(const Symbol& symbol) const -> bool {
  return (this->m_Tag < symbol.m_Tag);
}

auto Symbol::getTag() const -> char { return m_Tag; }

auto Symbol::isEmpty() const -> bool { return m_Empty; }
auto Symbol::isDisabled() const -> bool { return m_Disabled; }
void Symbol::disable() { m_Disabled = true; }
void Symbol::enable() { m_Disabled = false; }
} // namespace plut::core
