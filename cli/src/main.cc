#include "CliLogger.hpp"
#include <dlfcn.h>
#include <iostream>
#include <plut.hpp>

using plut::cli::CliLogger;

namespace plut::cli {

void printUsage() {
  std::cout << "Usage:\n";
  std::cout << " plut_cli <path/to/slot.so>" << std::endl;
}

} // namespace plut::cli

auto main(int argc, char* argv[]) -> int {

  if (argc != 2) {
    CliLogger().error(
        "Invalid number of arguments specified: {}, expected 2", argc);
    plut::cli::printUsage();
    return 1;
  }

  std::string_view pathToSlotLib{ argv[1] };
  auto slot{ plut::core::SlotLoader::buildCustomSlot(pathToSlotLib) };

  slot->spin();

  auto [rows, cols]{ slot->board.getSize() };
  for (int i{ 0 }; i < rows; i++) {
    for (int j{ 0 }; j < cols; j++) {
      if (slot->board[i][j].isDisabled() || slot->board[i][j].isEmpty()) {
        std::cout << "NO_SYM ";
        continue;
      }
      std::cout << slot->board[i][j].value().getTag() << ' ';
    }
    std::cout << std::endl;
  }

  std::cout << slot->getCurrentPayoutBetMultiplier() << std::endl;
  return 0;
}
