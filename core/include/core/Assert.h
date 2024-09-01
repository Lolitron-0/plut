#pragma once

#ifndef NDEBUG
#define CORE_ASSERT(condition, message)                                  \
  do { /* NOLINT */                                                      \
    if (!(condition)) {                                                  \
      CoreLogger().critical("Assertion failed at {}:{}, with message:",  \
                            __FILE__, __LINE__);                         \
      CoreLogger().critical((message));                                  \
      std::abort();                                                      \
    }                                                                    \
  } while (0);
#else
#define CORE_ASSERT(expr, message)
#endif
