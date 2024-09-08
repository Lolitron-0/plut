#pragma once
#include <spdlog/fmt/fmt.h>
#include <string>
#include <unordered_map>

namespace plut::core::utils {

inline auto prettyPostfix(std::size_t number) -> std::string {
  static std::unordered_map<std::size_t, char> postfixMap{
    { 1'000'000'000, 'B' }, { 1'000'000, 'M' }, { 1'000, 'k' }
  };

  std::size_t base{};
  if (number >= 1'000'000'000) {
    base = 1'000'000'000;
  } else if (number >= 1'000'000) {
    base = 1'000'000;
  } else if (number >= 1'000) {
    base = 1'000;
  } else {
    return std::to_string(number);
  }
  return fmt::format("{}.{}{}", number / base,
                     (number % base) / (base / 100), postfixMap.at(base));
}

} // namespace plut::core::utils
