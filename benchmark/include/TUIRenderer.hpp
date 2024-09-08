#pragma once
#include "SessionOptions.hpp"
#include <boost/circular_buffer.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <thread>

namespace plut::benchmark {
struct ExperimentStats;
class Measurer;

namespace ui = ftxui;

class TUIRenderer {
public:
  explicit TUIRenderer(SessionOptions opts, Measurer* parent);
  ~TUIRenderer();

  void startUIThread();

  void sendStats(const ExperimentStats& stats);

  void stop();

private:
  void _startScreenLoop();
  auto _getExecsPerSecGraph() -> ui::Element;

private:
  bool m_GotFirstStats{ false };
  SessionOptions m_SessionOpts;
	std::shared_ptr<ui::ScreenInteractive> m_Screen;
  std::mutex m_DataMutex;
  boost::circular_buffer<float> m_ExecsPerSecHistory;
  std::pair<float, float> m_ExecsPerSecBounds;
  float m_TrialProgress;
  std::unique_ptr<std::thread> m_UIThread;
  std::unique_ptr<std::thread> m_ScreenRefreshThread;
  std::atomic<bool> m_Running;

  Measurer* m_Parent;
};

} // namespace plut::benchmark
