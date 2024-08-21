#include "core/SlotBase.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

auto main() -> int {
  using plut::core::Symbol;

  Symbol symK{ 'K' };
  Symbol symQ{ 'Q' };
  Symbol symJ{ 'J' };
  Symbol symA{ 'A' };
  Symbol symW{ 'W' };
  Symbol symB{ 'B' };

  plut::core::SlotBase sb{ 3, 5 };

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
