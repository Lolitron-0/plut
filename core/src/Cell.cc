#include "core/Cell.hpp"
#include "core/Assert.h"
#include <deque>

namespace plut::core {

auto Cell::isEmpty() const -> bool {
  return !m_Content.has_value();
}
auto Cell::isDisabled() const -> bool {
  return m_Disabled;
}
auto Cell::value() const -> Symbol {
  CORE_ASSERT(m_Content.has_value(), "value() called on empty cell");
  return m_Content.value();
}
void Cell::disable() {
  m_Disabled = true;
}
void Cell::enable() {
  m_Disabled = false;
}

auto Cell::shouldFill() const -> bool {
  return isEmpty() && !isDisabled();
}
void Cell::setContent(const std::optional<Symbol>& content) {
  m_Content = content;
}
} // namespace plut::core
