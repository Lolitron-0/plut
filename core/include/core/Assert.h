#pragma once
#include "core/Logger.hpp"
#include <cstdlib>

#ifndef NDEBUG
#define CORE_ASSERT(condition, message, ...)                             \
  do {                  /* NOLINT */                                     \
    if (!(condition)) { /* NOLINT */                                     \
      CoreLogger().critical("Assertion failed at {}:{}, with message:",  \
                            __FILE__, __LINE__);                         \
      CoreLogger().critical((message), ##__VA_ARGS__);                   \
      std::abort();                                                      \
    }                                                                    \
  } while (false);
#else
#define CORE_ASSERT(expr, message)
#endif
