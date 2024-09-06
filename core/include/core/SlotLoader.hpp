#pragma once
#include <memory>

namespace plut::core {

class SlotBase;

class SlotLoader {
public:
  static auto buildCustomSlot(std::string_view pathToSlotLib)
      -> std::unique_ptr<core::SlotBase>;
};

} // namespace plut::core
