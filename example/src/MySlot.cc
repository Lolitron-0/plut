#include "MySlot.hpp"

MySlot::MySlot()
    : pc::SlotBase{ 5, 5 } {
  pc::SlotBase::registerFillPass(
      pc::PassPresets::Fill::Manager::getUniformRandomizeBoardPass());

  pc::Symbol symK{ 'K' };
  pc::Symbol symQ{ 'Q' };
  pc::Symbol symJ{ 'J' };
  pc::Symbol symA{ 'A' };
  pc::Symbol symW{ 'W' };
  pc::Symbol symB{ 'B' };
  pc::SlotBase::setSymbols({ symK, symQ, symJ, symA, symW, symB });
}

DEFINE_SLOT_BUILDER(MySlot)
