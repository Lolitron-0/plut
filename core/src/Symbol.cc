#include "core/Symbol.hpp"

namespace plut::core {

Symbol::Symbol()
    : Symbol{ ' ' } {
  m_Empty = false;
}

Symbol::Symbol(char tag)
    : m_Tag{ tag },
      m_Empty{ true } {}

auto Symbol::getUnicodeTag() const -> char { return m_Tag; }

auto Symbol::isEmpty() const -> bool { return m_Empty; }
} // namespace plut::core
