#pragma once
#include "core/Types.hpp"

namespace plut::core::PassPresets {

namespace Fill {

class Manager {
public:
  static auto getUniformRandomizeBoardPass() -> FillPass;
};

} // namespace Fill

namespace WinCollection {} // namespace WinCollection

} // namespace plut::core::PassPresets
