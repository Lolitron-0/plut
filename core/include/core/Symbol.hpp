#pragma once

namespace plut::core {

class Symbol {
public:
  Symbol();
  explicit Symbol(char tag);

  [[nodiscard]] auto getTag() const -> char;
  [[nodiscard]] auto isEmpty() const -> bool;
  [[nodiscard]] auto isDisabled() const -> bool;
  void disable();
  void enable();

  [[nodiscard]] auto operator== (const Symbol& symbol) const -> bool;
  [[nodiscard]] auto operator< (const Symbol& symbol) const -> bool;

private:
  char m_Tag;
  bool m_Empty;
	bool m_Disabled;
};

} // namespace plut::core
