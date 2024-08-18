#include "core/SlotBase.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

auto main() -> int {
  plut::core::SlotBase sb{3, 5};
  sb.setSymbols({
      plut::core::Symbol{L'K'},
      plut::core::Symbol{L'Q'},
      plut::core::Symbol{L'J'},
      plut::core::Symbol{L'W'},
      plut::core::Symbol{L'B'},
  });

  sb.spin();

  auto [rows, cols]{sb.getBoard().getSize()};
  for (int i{0}; i < rows; i++) {
    for (int j{0}; j < cols; j++) {
       std::cout << sb.getBoard()[i][j].getUnicodeTag() << ' ';
    }
		std::cout << std::endl;
  }
  return 0;
}
