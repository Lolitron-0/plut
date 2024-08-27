#pragma once
#include "core/Types.hpp"

namespace plut::core::PassPresets {

namespace Generation {

class Manager {
public:
  static auto getUniformRandomizeBoardPass() -> GenerationPass;
};

} // namespace Generation

namespace WinCollection {} // namespace WinCollection

} // namespace plut::core::PassPresets
