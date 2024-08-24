#pragma once
#include <memory>

namespace plut::core {

#define BUILD_SLOT_FUNC_NAME buildSlot
#define INTERNAL_STR(x) #x
#define INTERNAL_FUNC_NAME_STR_IMPL(name) INTERNAL_STR(name) 
#define BUILD_SLOT_FUNC_NAME_STR INTERNAL_FUNC_NAME_STR_IMPL(BUILD_SLOT_FUNC_NAME)

#define DEFINE_SLOT_BUILDER(className)                                   \
  extern "C" {                                                           \
  auto BUILD_SLOT_FUNC_NAME() -> plut::core::SlotBase* {                 \
    return new className();                                              \
  }                                                                      \
  }

} // namespace plut::core
