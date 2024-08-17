#include <spdlog/spdlog.h>

namespace plut::core {

class LoggerBase {
public:
  virtual ~LoggerBase() = default;

  template <typename... Args>
  void debug(spdlog::format_string_t<Args...> msg, Args &&...args) {
    m_Handle->debug(std::move(msg), std::forward<Args>(args)...);
  }
  template <typename... Args>
  void info(spdlog::format_string_t<Args...> msg, Args &&...args) {
    m_Handle->info(std::move(msg), std::forward<Args>(args)...);
  }
  template <typename... Args>
  void warn(spdlog::format_string_t<Args...> msg, Args &&...args) {
    m_Handle->warn(std::move(msg), std::forward<Args>(args)...);
  }
  template <typename... Args>
  void error(spdlog::format_string_t<Args...> msg, Args &&...args) {
    m_Handle->error(std::move(msg), std::forward<Args>(args)...);
  }
  template <typename... Args>
  void critical(spdlog::format_string_t<Args...> msg, Args &&...args) {
    m_Handle->critical(std::move(msg), std::forward<Args>(args)...);
  }

protected:
  explicit LoggerBase(std::string_view name);

private:
  static auto _registerSource(std::string_view name)
      -> std::shared_ptr<spdlog::logger>;

private:
  static bool s_Initialized;
  static std::vector<spdlog::sink_ptr> s_Sinks;

  std::shared_ptr<spdlog::logger> m_Handle;
};

class CoreLogger final : public LoggerBase {
public:
  CoreLogger();
};

} // namespace plut::core
