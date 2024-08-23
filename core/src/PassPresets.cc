#include "core/PassPresets.hpp"
#include "core/SlotBase.hpp"

namespace plut::core::PassPresets {

namespace Generation {

auto randomizeBoardImpl(SlotBase& slot, const RandEngineRef& randEngine)
    -> GenerationPassResult {
  for (int i{ 0 }; i < slot.getBoardState().getSize().first; i++) {
  }

  return GenerationPassResult{};
}

const GenerationPass RandomizeBoard = randomizeBoardImpl;

} // namespace Generation

} // namespace plut::core::PassPresets
