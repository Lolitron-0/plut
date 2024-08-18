#pragma once
#include "Symbol.hpp"
#include <stdexcept>
#include <vector>

namespace plut::core {

struct ReelTooSmallException : public std::runtime_error {
  ReelTooSmallException()
      : std::runtime_error{ "Reel length is too small" } {}
};

class Reel {
public:
  using ReelBuffer = std::vector<Symbol>;

  Reel() = default;
  Reel(int spanSize, std::initializer_list<Symbol> symbols);

  [[nodiscard]] auto getSymbols() const -> const ReelBuffer&;
  [[nodiscard]] auto getSpanSize() const -> int;

private:
  int m_SpanSize{ 0 };
  std::vector<Symbol> m_Symbols;
};

} // namespace plut::core
