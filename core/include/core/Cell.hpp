#pragma once
#include "core/Symbol.hpp"
#include <optional>

namespace plut::core {

class Cell {
public:
  [[nodiscard]] auto isDisabled() const -> bool;
  [[nodiscard]] auto shouldFill() const -> bool;
  [[nodiscard]] auto isEmpty() const -> bool;
  [[nodiscard]] auto value() const -> Symbol;
  void setContent(const std::optional<Symbol>& content);
  void disable();
  void enable();

public:
private:
  std::optional<Symbol> m_Content{ std::nullopt };
  bool m_Disabled{ false };
};

} // namespace plut::core
