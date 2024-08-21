#include "core/Logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace plut::core {

bool LoggerBase::s_Initialized{ false };
std::vector<spdlog::sink_ptr> LoggerBase::s_Sinks{};

LoggerBase::LoggerBase(std::string_view name) {
  if (!s_Initialized) {
    s_Sinks.push_back(
        std::make_shared<spdlog::sinks::stdout_color_sink_st>());
    s_Initialized = true;
  }

  m_Handle = spdlog::get(std::string{ name });
  if (m_Handle == nullptr) {
    m_Handle = _registerSource(name);
    m_Handle->info("\"{}\" logger registered", name);
  }
}

auto LoggerBase::_registerSource(std::string_view name)
    -> std::shared_ptr<spdlog::logger> {
  auto newLogger = std::make_shared<spdlog::logger>(
      std::string{ name }, s_Sinks.begin(), s_Sinks.end());

#ifdef PLUT_NO_LOGS
  newLogger->set_level(spdlog::level::level_enum::off);
#elif defined(NDEBUG)
  newLogger->set_level(spdlog::level::level_enum::info);
#else
  newLogger->set_level(spdlog::level::level_enum::trace);
#endif

  spdlog::register_logger(newLogger);
  spdlog::set_pattern("%H:%M:%S.%e [%n] %^%l%$: %v");
  return newLogger;
}

CoreLogger::CoreLogger()
    : LoggerBase{ "CORE" } {}
} // namespace plut::core
