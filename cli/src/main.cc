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

auto loadCustomSlotBuilderFn(std::string_view pathToLib)
    -> std::function<core::SlotBase*(void)> {
  void* handle{ dlopen(pathToLib.data(), RTLD_LAZY) };
  if (!handle) {
    CliLogger().syscritical("Could not open slot shared library: {}",
                            pathToLib);
    std::exit(1); // NOLINT (one thread)
  }

  core::SlotBase* (*buildFunc)(){ nullptr };
  buildFunc = reinterpret_cast<core::SlotBase* (*)()>(
      dlsym(handle, BUILD_SLOT_FUNC_NAME_STR));
  if (!buildFunc) {
    CliLogger().syscritical("Could not load builder symbol (did you "
                            "forget to add DEFINE_SLOT_BUILDER?): {}",
                            pathToLib);
    std::exit(1); // NOLINT (one thread)
  }

  return buildFunc;
}

auto buildCustomSlot(std::string_view pathToSlotLib)
    -> std::unique_ptr<core::SlotBase> {
  auto buildFn{ loadCustomSlotBuilderFn(pathToSlotLib) };

  return std::unique_ptr<core::SlotBase>(std::invoke(buildFn));
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
  auto slot{ plut::cli::buildCustomSlot(pathToSlotLib) };

  slot->spin();

  auto [rows, cols]{ slot->board.getSize() };
  for (int i{ 0 }; i < rows; i++) {
    for (int j{ 0 }; j < cols; j++) {
      std::cout << slot->board[i][j].getTag() << ' ';
    }
    std::cout << std::endl;
  }

  std::cout << slot->getCurrentPayoutBetMultiplier() << std::endl;
  return 0;
}
