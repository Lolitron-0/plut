#include "core/SlotBase.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

auto main() -> int {
  using plut::core::Reel;
  using plut::core::Symbol;

  Symbol symK{ 'K' };
  Symbol symQ{ 'Q' };
  Symbol symJ{ 'J' };
  Symbol symA{ 'A' };
  Symbol symW{ 'W' };
  Symbol symB{ 'B' };

  plut::core::SlotBase sb{
    Reel{ 3, { symA, symB, symJ, symJ, symW, symB } },
    Reel{ 3, { symB, symA, symA, symK, symQ, symJ } },
    Reel{ 3, { symJ, symJ, symK, symQ, symJ, symB } },
    Reel{ 3, { symQ, symK, symQ, symK, symJ, symW } },
    Reel{ 3, { symW, symW, symB, symJ, symQ, symW } },
  };

  sb.spin();

  auto [rows, cols]{ sb.getBoardState().getSize() };
  for (int i{ 0 }; i < rows; i++) {
    for (int j{ 0 }; j < cols; j++) {
      std::cout << sb.getBoardState()[i][j].getUnicodeTag() << ' ';
    }
    std::cout << std::endl;
  }
  return 0;
}
