#pragma once
#include <spdlog/spdlog.h>

namespace plut::core {

class LoggerBase {
public:
  virtual ~LoggerBase() = default;

  template <typename... Args>
  void trace(spdlog::format_string_t<Args...> msg, Args&&... args) {
    m_Handle->trace(std::move(msg), std::forward<Args>(args)...);
  }
  template <typename... Args>
  void debug(spdlog::format_string_t<Args...> msg, Args&&... args) {
    m_Handle->debug(std::move(msg), std::forward<Args>(args)...);
  }
  template <typename... Args>
  void info(spdlog::format_string_t<Args...> msg, Args&&... args) {
    m_Handle->info(std::move(msg), std::forward<Args>(args)...);
  }
  template <typename... Args>
  void warn(spdlog::format_string_t<Args...> msg, Args&&... args) {
    m_Handle->warn(std::move(msg), std::forward<Args>(args)...);
  }
  template <typename... Args>
  void error(spdlog::format_string_t<Args...> msg, Args&&... args) {
    m_Handle->error(std::move(msg), std::forward<Args>(args)...);
  }
  template <typename... Args>
  void syserror(spdlog::format_string_t<Args...> msg, Args&&... args) {
    std::string_view osErrorStr{ strerror(errno) };
    m_Handle->error(std::move(msg), std::forward<Args>(args)...);
    m_Handle->error("OS message: {}", osErrorStr);
  }
  template <typename... Args>
  void critical(spdlog::format_string_t<Args...> msg, Args&&... args) {
    m_Handle->critical(std::move(msg), std::forward<Args>(args)...);
  }
  template <typename... Args>
  void syscritical(spdlog::format_string_t<Args...> msg, Args&&... args) {
    std::string_view osErrorStr{ strerror(errno) };
    m_Handle->critical(std::move(msg), std::forward<Args>(args)...);
    m_Handle->critical("OS message: {}", osErrorStr);
  }

  static void mute();
  static void unmute();

protected:
  explicit LoggerBase(std::string_view name);

private:
  static auto _registerSource(std::string_view name)
      -> std::shared_ptr<spdlog::logger>;

private:
	static bool s_Muted;
  static bool s_Initialized;
  static std::vector<spdlog::sink_ptr> s_Sinks;

  std::shared_ptr<spdlog::logger> m_Handle;
};

class CoreLogger final : public LoggerBase {
public:
  CoreLogger();
};

} // namespace plut::core
