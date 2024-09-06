#include "plut.hpp"
#include <gtest/gtest.h>
#include <mutex>

using namespace plut::core;

class InitEnv : public ::testing::Environment {
protected:
  void SetUp() override { LoggerBase::mute(); }
};

auto main(int argc, char** argv) -> int {
  testing::InitGoogleTest(&argc, argv);
  testing::AddGlobalTestEnvironment(new InitEnv()); // NOLINT
  return RUN_ALL_TESTS();
}

const std::vector<Symbol> testSymbols{
  Symbol{ '1' }, Symbol{ '2' },       Symbol{ '3' },
  Symbol{ '4' }, Symbol{ '5', 0.2F }, Symbol{ '6', 0.1F },
};

TEST(Matrix, Types) {
  ContiguousDynamicMatrix<int> m1{ 1, 1 };
  ContiguousDynamicMatrix<std::string> m2{ 1, 1 };
  ContiguousDynamicMatrix<std::shared_ptr<
      std::vector<std::pair<std::string, std::tuple<int, std::mutex>>>>>
      m3{ 1, 1 };
}

TEST(Matrix, BigAlloc) {
  ContiguousDynamicMatrix<double> mat{ 1000, 1001 };
  EXPECT_EQ(mat.getSize().rows, 1000);
  EXPECT_EQ(mat.getSize().columns, 1001);
}

TEST(Matrix, IndexOperatorTypes) {
  ContiguousDynamicMatrix<int> mat{ 5, 5 };

  mat[(signed char)0][(unsigned char)0] = 0; // non-const
  mat[(unsigned char)0][(signed char)0] = 0; // non-const
  mat[(short)0][(unsigned short)0];
  mat[(unsigned short)0][(short)0];
  mat[(int)0][(unsigned int)0];
  mat[(unsigned int)0][(int)0];
  mat[(long)0][(unsigned long)0];
  mat[(unsigned long)0][(long)0];
  mat[(long long)0][(unsigned long long)0];
  mat[(unsigned long long)0][(long long)0];

  const ContiguousDynamicMatrix<int> cmat{ 5, 5 };
  cmat[0][0]; // const
}

TEST(Matrix, IndexOperator) {
  ContiguousDynamicMatrix<int> mat{ 5, 5 };

  auto [rows, cols]{ mat.getSize() };
  for (int i{ 0 }; i < rows; i++) {
    for (int j{ 0 }; j < cols; j++) {
      mat[i][j] = i * cols + j;
    }
  }

  EXPECT_EQ(mat[0][0], 0);
  EXPECT_EQ(mat[0][1], 1);
  EXPECT_EQ(mat[0][2], 2);
  EXPECT_EQ(mat[0][3], 3);
  EXPECT_EQ(mat[0][4], 4);

  EXPECT_EQ(mat[1][0], 5);
  EXPECT_EQ(mat[1][1], 6);
  EXPECT_EQ(mat[1][2], 7);
  EXPECT_EQ(mat[1][3], 8);
  EXPECT_EQ(mat[1][4], 9);

  EXPECT_EQ(mat[2][0], 10);
  EXPECT_EQ(mat[2][1], 11);
  EXPECT_EQ(mat[2][2], 12);
  EXPECT_EQ(mat[2][3], 13);
  EXPECT_EQ(mat[2][4], 14);

  EXPECT_EQ(mat[3][0], 15);
  EXPECT_EQ(mat[3][1], 16);
  EXPECT_EQ(mat[3][2], 17);
  EXPECT_EQ(mat[3][3], 18);
  EXPECT_EQ(mat[3][4], 19);

  EXPECT_EQ(mat[4][0], 20);
  EXPECT_EQ(mat[4][1], 21);
  EXPECT_EQ(mat[4][2], 22);
  EXPECT_EQ(mat[4][3], 23);
  EXPECT_EQ(mat[4][4], 24);
}

TEST(Logger, Methods) {
  struct TestLogger : LoggerBase {
    TestLogger()
        : LoggerBase{ "TEST" } {}
  };

  EXPECT_NO_THROW(TestLogger().trace("msg {}", 0));
  EXPECT_NO_THROW(TestLogger().debug("msg {}", 1));
  EXPECT_NO_THROW(TestLogger().info("msg {}", 2));
  EXPECT_NO_THROW(TestLogger().warn("msg {}", 3));
  EXPECT_NO_THROW(TestLogger().error("msg {}", 4));
  EXPECT_NO_THROW(TestLogger().critical("msg {}", 5));
  EXPECT_NO_THROW(TestLogger().syserror("msg {}", 6));
  EXPECT_NO_THROW(TestLogger().syscritical("msg {}", 7));
}

TEST(Reel, BoundValues) {
  EXPECT_THROW(([] {
                 Reel r{ 10, { Symbol{ '1' }, Symbol{ '2' } } };
               }()),
               ReelTooSmallException);
  EXPECT_THROW(([] {
                 Reel r{ 1, {} };
               }()),
               ReelTooSmallException);
  EXPECT_NO_THROW(([] {
    Reel r{ 2, { Symbol{ '1' }, Symbol{ '2' }, Symbol{ '3' } } };
  }()));
  EXPECT_NO_THROW(([] {
    Reel r{ 2, { Symbol{ '1' }, Symbol{ '2' } } };
  }()));
}

TEST(Board, Operators) {
  Board board{ 5, 5 };
  board[0][0];
  const Board cboard{ 5, 5 };
  cboard[0][0];
}

TEST(SymbolManager, Assertions) {
  SlotBase sb{ 5, 5 };

  // set current set
  EXPECT_NO_FATAL_FAILURE(sb.getSymbolManager()->setCurrentSetSymbols(
      { Symbol{ '1' }, Symbol{ '2' }, Symbol{ '3' } }));
  EXPECT_DEBUG_DEATH(sb.getSymbolManager()->setCurrentSetSymbols(
                         { Symbol{ '1' }, Symbol{ '1' }, Symbol{ '3' } }),
                     ".*");

  // add to current set
  EXPECT_NO_FATAL_FAILURE(
      sb.getSymbolManager()->addSymbolToCurrentSet(Symbol{ '4' }));
  EXPECT_DEBUG_DEATH(
      sb.getSymbolManager()->addSymbolToCurrentSet(Symbol{ '1' }), ".*");

  // add set
  EXPECT_NO_FATAL_FAILURE(
      sb.getSymbolManager()->addSymbolSet("new1", { Symbol{ '1' } }));
  EXPECT_DEBUG_DEATH(sb.getSymbolManager()->addSymbolSet(
                         "new2", { Symbol{ '1' }, Symbol{ '1' } }),
                     ".*");
  EXPECT_DEBUG_DEATH(
      sb.getSymbolManager()->addSymbolSet("default", { Symbol{ '1' } }),
      ".*");

  // switch set
  EXPECT_NO_FATAL_FAILURE(
      sb.getSymbolManager()->switchCurrentSymbolSet("new1"));
  EXPECT_DEBUG_DEATH(
      sb.getSymbolManager()->switchCurrentSymbolSet("nonexistent"), ".*");

  // remove set
  EXPECT_NO_FATAL_FAILURE(
      sb.getSymbolManager()->removeSymbolSet("default"));
  EXPECT_DEBUG_DEATH(sb.getSymbolManager()->removeSymbolSet("default"),
                     ".*");
}

TEST(FillPassPreset, UniformRandomizeBoard) {
  struct TestSlot : SlotBase {
    TestSlot()
        : SlotBase{ 5, 5 } {
      SlotBase::registerFillPass(
          PassPresets::Fill::Manager::getWeightedRandomizeBoardPass());
    }
  };
  TestSlot s;
  s.getSymbolManager()->setCurrentSetSymbols(testSymbols);

  s.spin();

  for (int i{ 0 }; i < s.board.getSize().rows; i++) {
    for (int j{ 0 }; j < s.board.getSize().columns; j++) {
      bool match{ false };
      for (auto symbol : s.getSymbolManager()->getCurrentSetSymbols()) {
        if (symbol.getTag() == s.board[i][j].value().getTag()) {
          match = true;
          break;
        }
      }
      EXPECT_TRUE(match);
    }
  }
}

TEST(WinCollectionPassPreset, WinLineWinLinePath) {
  using namespace WinLineShapePresets::Steps;
  auto opTest{ StepDown * 4 + StepRight * 2 + 1 * StepUpLeft };
  WinLinePath customTest{ Offset2D{ 1, 1 }, { 2, -4 }, { -1, 0 } };
}

TEST(WinCollectionPassPreset, WinLineWinLineBounds) {
  using namespace WinLineShapePresets::Steps;
  struct TestSlot : SlotBase {
    TestSlot()
        : SlotBase{ 3, 3 } {
      SlotBase::registerFillPass(
          PassPresets::Fill::Manager::getWeightedRandomizeBoardPass());
      SlotBase::getSymbolManager()->setCurrentSetSymbols(testSymbols);

      WinLine outOfBoundsLine1{ { 0, 0 }, StepRight * 3, 2 };
      WinLine outOfBoundsLine2{ { 0, 0 }, StepLeft * 3, 2 };
      WinLine outOfBoundsLine3{ { 2, 2 }, StepRight, 2 };
      WinLine outOfBoundsLine4{ { 2, 2 }, StepDown, 2 };

      SlotBase::registerWinCollectionPass(
          PassPresets::WinCollection::Manager::getWinLinesPass(
              { outOfBoundsLine1 }));
      EXPECT_DEBUG_DEATH(spin(), ".*");
      SlotBase::clearWinCollectionPasses();

      SlotBase::registerWinCollectionPass(
          PassPresets::WinCollection::Manager::getWinLinesPass(
              { outOfBoundsLine2 }));
      EXPECT_DEBUG_DEATH(spin(), ".*");
      SlotBase::clearWinCollectionPasses();

      SlotBase::registerWinCollectionPass(
          PassPresets::WinCollection::Manager::getWinLinesPass(
              { outOfBoundsLine3 }));
      EXPECT_DEBUG_DEATH(spin(), ".*");
      SlotBase::clearWinCollectionPasses();

      SlotBase::registerWinCollectionPass(
          PassPresets::WinCollection::Manager::getWinLinesPass(
              { outOfBoundsLine4 }));
      EXPECT_DEBUG_DEATH(spin(), ".*");
      SlotBase::clearWinCollectionPasses();

      WinLine noStartLine{ StepRight + StepDown + StepLeft + StepUp, 4 };
      SlotBase::registerWinCollectionPass(
          PassPresets::WinCollection::Manager::getWinLinesPass(
              { noStartLine }));
      EXPECT_NO_FATAL_FAILURE(spin());
      SlotBase::clearWinCollectionPasses();

      //    WinLine goodLine{ { 0, 0 },
      //                      WinLinePath{ { 1, 1 }, { 1, 1 }, { -1, 0 }
      //                      }, 3 };
      //    SlotBase::registerWinCollectionPass(
      //        PassPresets::WinCollection::Manager::getWinLinesPass(
      //            { goodLine }));
      //    EXPECT_NO_FATAL_FAILURE(spin());
      // SlotBase::clearWinCollectionPasses();
    }
  };

  TestSlot slot;
}

TEST(WinCollectionPassPreset, WinLineStartPoint) {
  using namespace WinLineShapePresets::Steps;
  struct TestSlot : SlotBase {
    TestSlot()
        : SlotBase{ 5, 5 } {
      SlotBase::getSymbolManager()->setCurrentSetSymbols(testSymbols);
      SlotBase::registerFillPass(
          PassPresets::Fill::Manager::getWeightedRandomizeBoardPass());
      SlotBase::registerWinCollectionPass(
          PassPresets::WinCollection::Manager::getWinLinesPass({
              WinLine{ { 0, 0 }, StepRight * 4, 2 },
              WinLine{ { 1, 0 }, StepRight * 4, 2 },
              WinLine{ { 2, 0 }, StepRight * 4, 2 },
              WinLine{ { 3, 0 }, StepRight * 4, 2 },
              WinLine{ { 4, 0 }, StepRight * 4, 2 },
          }));
    }
  };

  TestSlot s;
  while (s.getCurrentPayoutBetMultiplier() == 0) {
    s.spin();
  }
}

TEST(WinCollectionPassPreset, WinLineNoStartPointFull) {
  using namespace WinLineShapePresets::Steps;
  struct TestSlot : SlotBase {
    TestSlot()
        : SlotBase{ 5, 5 } {
      SlotBase::getSymbolManager()->setCurrentSetSymbols(testSymbols);
      SlotBase::registerFillPass(
          PassPresets::Fill::Manager::getWeightedRandomizeBoardPass());
      SlotBase::registerWinCollectionPass(
          PassPresets::WinCollection::Manager::getWinLinesPass({
              WinLine{ StepDown * 4, 5 },
          }));
    }
  };

  TestSlot s;
  while (s.getCurrentPayoutBetMultiplier() == 0) {
    s.spin();
  }
}
