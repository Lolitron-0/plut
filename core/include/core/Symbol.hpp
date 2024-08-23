#pragma once

namespace plut::core {

class Symbol {
public:
  Symbol();
  explicit Symbol(char tag);

  [[nodiscard]] auto getUnicodeTag() const -> char;
  [[nodiscard]] auto isEmpty() const -> bool;
  [[nodiscard]] auto isDisabled() const -> bool;
  void disable();
  void enable();

private:
  char m_Tag;
  bool m_Empty;
	bool m_Disabled;
};

} // namespace plut::core
