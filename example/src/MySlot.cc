#include "MySlot.hpp"

constexpr int slotRows{ 5 };
constexpr int slotCols{ 5 };

MySlot::MySlot()
    : pc::SlotBase{ slotRows, slotCols } {
  pc::SlotBase::registerFillPass(
      pc::PassPresets::Fill::Manager::getWeightedRandomizeBoardPass());

  using namespace pc::WinLineShapePresets;
  std::vector<pc::WinLine> winLines{
    pc::WinLine{ { 0, 0 }, CheckersDownShape4, 3 },
    pc::WinLine{ { 1, 0 }, CheckersDownShape4, 3 },
    pc::WinLine{ { 2, 0 }, CheckersDownShape4, 3 },
    pc::WinLine{ { 3, 0 }, CheckersDownShape4, 3 },

    pc::WinLine{ { 1, 0 }, CheckersUpShape4, 3 },
    pc::WinLine{ { 2, 0 }, CheckersUpShape4, 3 },
    pc::WinLine{ { 3, 0 }, CheckersUpShape4, 3 },
    pc::WinLine{ { 4, 0 }, CheckersUpShape4, 3 },

    pc::WinLine{ { 0, 0 }, Steps::StepRight * (slotCols - 1), 3 },
    pc::WinLine{ { 1, 0 }, Steps::StepRight * (slotCols - 1), 3 },
    pc::WinLine{ { 2, 0 }, Steps::StepRight * (slotCols - 1), 3 },
    pc::WinLine{ { 3, 0 }, Steps::StepRight * (slotCols - 1), 3 },
    pc::WinLine{ { 4, 0 }, Steps::StepRight * (slotCols - 1), 3 },
  };
  pc::SlotBase::registerWinCollectionPass(
      pc::PassPresets::WinCollection::Manager::getWinLinesPass(winLines));

  pc::Symbol symK{ 'K', 0.3 };
  pc::Symbol symQ{ 'Q' };
  pc::Symbol symJ{ 'J' };
  pc::Symbol symA{ 'A', 0.2 };
  pc::Symbol symW{ 'W', 0.1 };
  pc::Symbol symB{ 'B', 0.1 };
  pc::SlotBase::getSymbolManager()->setCurrentSetSymbols(
      { symK, symQ, symJ, symA, symW, symB });
}

DEFINE_SLOT_BUILDER(MySlot)
