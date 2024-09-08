#pragma once
#include <utility>

namespace plut::benchmark::utils {

template <typename F>
class LazyPRValue {
public:
  explicit LazyPRValue(F&& func)
      : m_Func{ std::move(func) } {
  }

  constexpr operator std::invoke_result_t<F>() { // NOLINT
    return std::move(m_Func)();
  }

private:
  F m_Func{};
};

} // namespace plut::benchmark::utils
