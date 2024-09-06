#include "core/SlotLoader.hpp"
#include "core/SlotBase.hpp"
#include "core/Logger.hpp"
#include "core/Macros.hpp"
#include <dlfcn.h>
#include <functional>

namespace plut::core {

static auto loadCustomSlotBuilderFn(std::string_view pathToLib)
    -> std::function<core::SlotBase*(void)> {
  void* handle{ dlopen(pathToLib.data(), RTLD_LAZY) };
  if (!handle) {
    CoreLogger().syscritical("Could not open slot shared library: {}",
                             pathToLib);
    std::exit(1); // NOLINT (one thread)
  }

  core::SlotBase* (*buildFunc)(){ nullptr };
  buildFunc = reinterpret_cast<core::SlotBase* (*)()>(
      dlsym(handle, BUILD_SLOT_FUNC_NAME_STR));
  if (!buildFunc) {
    CoreLogger().syscritical("Could not load builder symbol (did you "
                             "forget to add DEFINE_SLOT_BUILDER?): {}",
                             pathToLib);
    std::exit(1); // NOLINT (one thread)
  }

  return buildFunc;
}

auto SlotLoader::buildCustomSlot(std::string_view pathToSlotLib)
    -> std::unique_ptr<core::SlotBase> {
  auto buildFn{ loadCustomSlotBuilderFn(pathToSlotLib) };

  return std::unique_ptr<core::SlotBase>(std::invoke(buildFn));
}

} // namespace plut::core
