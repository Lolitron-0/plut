#include "core/Logger.hpp"
#include <concepts>
#include <type_traits>
#include <vector>

template <typename U>
concept IndexType =
    std::is_integral_v<U> && std::convertible_to<U, std::size_t>;

namespace plut::core {
template <typename T> class ContiguousDynamicMatrix {
public:
  using ValueT = std::remove_cvref_t<T>;

  ContiguousDynamicMatrix(std::size_t rows, std::size_t cols)
      : m_Data(rows * cols), m_Size{rows, cols} {
    CoreLogger().debug("{}", m_Data.capacity());
  }

  [[nodiscard]] auto
  getSize() const -> std::pair<std::size_t, std::size_t> {
    return m_Size;
  }

  class RowProxy {
    friend class ContiguousDynamicMatrix<T>;

  public:
    template <IndexType U> auto operator[](U j) -> ValueT& {
      return parent.m_Data[i * parent.m_Size.second + j];
    }

  private:
    RowProxy(ContiguousDynamicMatrix<T>& parent, std::size_t i)
        : parent{parent}, i{i} {}

  private:
    ContiguousDynamicMatrix<T>& parent;
    std::size_t i;
  };

  template <IndexType U> auto operator[](U i) -> RowProxy {
    return RowProxy{*this, static_cast<std::size_t>(i)};
  }

private:
  std::vector<ValueT> m_Data;
  std::pair<std::size_t, std::size_t> m_Size;
};
} // namespace plut::core
