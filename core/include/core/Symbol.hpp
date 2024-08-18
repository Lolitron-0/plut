#pragma once

namespace plut::core {

class Symbol {
public:
  Symbol();
  explicit Symbol(char tag);

  [[nodiscard]] auto getUnicodeTag() const -> char;
  [[nodiscard]] auto isEmpty() const -> bool;

private:
  char m_Tag;
  bool m_Empty;
};

} // namespace plut::core
