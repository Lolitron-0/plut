#pragma once

namespace plut::core {

class Symbol {
public:
  Symbol() = default;
  explicit Symbol(char tag);
  Symbol(char tag, float probabilityWeight);

  [[nodiscard]] auto getTag() const -> char;
  [[nodiscard]] auto getWeight() const -> float;

  [[nodiscard]] auto operator==(const Symbol& symbol) const -> bool;
  [[nodiscard]] auto operator<(const Symbol& symbol) const -> bool;

private:
  char m_Tag{ ' ' };
  float m_Weight{ 0.5F };
  bool m_Empty{ true };
  bool m_Disabled{ false };
};

} // namespace plut::core
