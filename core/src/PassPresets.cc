#include "core/PassPresets.hpp"
#include "core/Assert.h"
#include "core/SlotBase.hpp"

namespace plut::core::PassPresets {

namespace Generation {

auto uniformRandomizeBoardPassImpl(SlotBase& slot,
                                   const RandEngineRef& randEngineRef)
    -> GenerationPassResult {
  CORE_ASSERT(slot.getSymbols().size() > 0,
              "No symbols to generate from");

  auto [rows, cols]{ slot.board.getSize() };
  std::uniform_int_distribution<std::size_t> distrib{
    0, slot.getSymbols().size() - 1
  };
  for (int i{ 0 }; i < rows; i++) {
    for (int j{ 0 }; j < cols; j++) {
      auto rnd{ distrib(*randEngineRef) };
      slot.board[i][j] = slot.getSymbols()[rnd];
    }
  }

  return GenerationPassResult{};
}

const GenerationPass UniformRandomizeBoardPass =
    uniformRandomizeBoardPassImpl;

} // namespace Generation

} // namespace plut::core::PassPresets
