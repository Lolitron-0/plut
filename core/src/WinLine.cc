#include <utility>

#include "core/WinLine.hpp"

namespace plut::core {

WinLine::WinLine(Offset2D startPoint, WinLinePath path,
                 std::size_t minSymbols)
    : startPoint{ startPoint },
      path{ std::move(path) },
      minSymbols{ minSymbols } {
}
WinLine::WinLine(WinLinePath path, std::size_t minSymbols)
    : path{ std::move(path) },
      minSymbols{ minSymbols } {
}

auto operator+(const WinLinePath& a,
               const WinLinePath& b) noexcept -> WinLinePath {
  std::vector<Offset2D> res{ a.edges.size() + b.edges.size() };
  std::copy(a.edges.begin(), a.edges.end(), res.begin());
  std::copy(b.edges.begin(), b.edges.end(), res.begin() + a.edges.size());
  return { res };
}

namespace WinLineShapePresets {

const WinLinePath VShape({ Offset2D{ 1, 1 }, { -1, 1 } });
const WinLinePath CaretShape({ Offset2D{ -1, 1 }, { 1, 1 } });
const WinLinePath CheckersDownShape4(VShape + VShape);
const WinLinePath CheckersUpShape4(CaretShape + CaretShape);

namespace Steps {

const WinLinePath StepUp({ Offset2D{ -1, 0 } });
const WinLinePath StepDown({ Offset2D{ 1, 0 } });
const WinLinePath StepLeft({ Offset2D{ 0, -1 } });
const WinLinePath StepRight({ Offset2D{ 0, 1 } });

const WinLinePath StepUpLeft({ Offset2D{ -1, -1 } });
const WinLinePath StepDownLeft({ Offset2D{ 1, -1 } });
const WinLinePath StepUpRight({ Offset2D{ -1, 1 } });
const WinLinePath StepDownRight({ Offset2D{ 1, 1 } });

} // namespace Steps

} // namespace WinLineShapePresets

} // namespace plut::core
