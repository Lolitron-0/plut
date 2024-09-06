#pragma once
#include "core/Assert.h"
#include "core/SlotBase.hpp"
#include "core/Types.hpp"
#include "core/WinLine.hpp"
#include <algorithm>

namespace plut::core::PassPresets {

namespace Fill {

class Manager {
public:
  static auto getWeightedRandomizeBoardPass() -> FillPass;
};

} // namespace Fill

namespace WinCollection {

class Manager {
public:
  static auto getWinLinesPass(const std::vector<WinLine>& winLines)
      -> WinCollectionPass;

private:
};

} // namespace WinCollection

} // namespace plut::core::PassPresets
