#include "core/Board.hpp"
#include "core/ContiguousMatrix.hpp"
#include "core/PassPresets.hpp"
#include "core/Reel.hpp"
#include "core/SlotBase.hpp"
#include <gtest/gtest.h>
#include <mutex>

using namespace plut::core;

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

TEST(GenerationPassPreset, UniformRandomizeBoardPass) {
  struct TestSlot : SlotBase {
    TestSlot()
        : SlotBase{ 5, 5 } {
      SlotBase::registerGenerationPass(
          PassPresets::Generation::Manager::
              getUniformRandomizeBoardPass());
    }
  };
  TestSlot s;
  s.setSymbols({
      Symbol{ '1' },
      Symbol{ '2' },
      Symbol{ '3' },
      Symbol{ '4' },
      Symbol{ '5' },
      Symbol{ '6' },
  });

  s.spin();

  for (int i{ 0 }; i < s.board.getSize().rows; i++) {
    for (int j{ 0 }; j < s.board.getSize().columns; j++) {
      bool match{ false };
      for (auto symbol : s.getSymbols()) {
        if (symbol.getTag() == s.board[i][j].getTag()) {
          match = true;
          break;
        }
      }
      EXPECT_TRUE(match);
    }
  }
}
