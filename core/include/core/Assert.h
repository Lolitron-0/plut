#pragma once

#ifndef NDEBUG
#define CORE_ASSERT(condition, message)                                  \
  do {                                                                   \
    if (!(condition)) {                                                  \
      CoreLogger().critical((message));                                  \
      std::abort();                                                      \
    }                                                                    \
  } while (0);
#else
#define CORE_ASSERT(expr, message)
#endif
