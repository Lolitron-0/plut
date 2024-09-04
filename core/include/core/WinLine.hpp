#pragma once
#include <concepts>
#include <optional>
#include <utility>
#include <vector>

namespace plut::core {

struct Offset2D {
  constexpr Offset2D() noexcept = default;
  constexpr Offset2D(int i, int j) noexcept
      : i{ i },
        j{ j } {}

  /* implicit */ constexpr operator std::pair<int, int>() const // NOLINT
  {
    return std::make_pair(i, j);
  }

  int i{};
  int j{};
};
struct WinLinePath {
  /* implicit */ constexpr WinLinePath( // NOLINT
      std::initializer_list<Offset2D> path) noexcept
      : edges{ path } {}
  /* implicit */ WinLinePath( // NOLINT
      std::vector<Offset2D> path) noexcept
      : edges{ std::move(path) } {}

  std::vector<Offset2D> edges;
};

constexpr auto operator+(const WinLinePath& a,
                         const WinLinePath& b) noexcept -> WinLinePath {
  std::vector<Offset2D> res{ a.edges.size() + b.edges.size() };
  std::copy(a.edges.begin(), a.edges.end(), res.begin());
  std::copy(b.edges.begin(), b.edges.end(), res.begin() + a.edges.size());
  return { res };
}

template <std::integral T>
constexpr auto operator*(const WinLinePath& a,
                         T mul) noexcept -> WinLinePath {
  CORE_ASSERT(mul > 0, "Factor must be positive");
  std::vector<Offset2D> res{ a.edges.size() * mul };
  for (int i{ 0 }; i < mul; i++) {
    std::copy(a.edges.begin(), a.edges.end(),
              res.begin() + i * a.edges.size());
  }
  return { res };
}
template <std::integral T>
constexpr auto operator*(T mul,
                         const WinLinePath& a) noexcept -> WinLinePath {
  return a * mul;
}

struct WinLine {
  WinLine(Offset2D startPoint, WinLinePath path, std::size_t minSymbols);
  WinLine(WinLinePath path, std::size_t minSymbols);

  std::optional<Offset2D> startPoint{ std::nullopt };
  WinLinePath path;
  std::size_t minSymbols;
};

namespace WinLineShapePresets {

/// V-line
const extern WinLinePath VShape;

/// ^-line
const extern WinLinePath CaretShape;

/// W-line
const extern WinLinePath CheckersDownShape4;
/// M-line
const extern WinLinePath CheckersUpShape4;

namespace Steps {

const extern WinLinePath StepUp;
const extern WinLinePath StepDown;
const extern WinLinePath StepLeft;
const extern WinLinePath StepRight;

const extern WinLinePath StepUpLeft;
const extern WinLinePath StepDownLeft;
const extern WinLinePath StepUpRight;
const extern WinLinePath StepDownRight;

} // namespace Steps

} // namespace WinLineShapePresets

} // namespace plut::core
