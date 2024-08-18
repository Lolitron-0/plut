#include "core/ContiguousMatrix.hpp"
#include "core/Symbol.hpp"
#include <random>

namespace plut::core {

class SlotBase {
public:
  SlotBase(size_t rows, size_t columns);

  [[nodiscard]] auto getBoard() const -> const ContiguousDynamicMatrix<Symbol>&;
  void setSymbols(std::vector<Symbol>&& symbols);

  void spin();

private:
  ContiguousDynamicMatrix<Symbol> m_Board;
  std::vector<Symbol> m_Symbols;
  std::mt19937_64 m_RandEngine;
};

} // namespace plut::core
