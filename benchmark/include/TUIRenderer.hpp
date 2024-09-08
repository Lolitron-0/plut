#pragma once
#include <boost/circular_buffer.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <thread>

namespace plut::benchmark {
struct ExperimentStats;

namespace ui = ftxui;

class TUIRenderer {
public:
  TUIRenderer();
  ~TUIRenderer();

  void startTUIThread();

  void sendStats(const ExperimentStats& stats);

  void stop();

private:
  void _startScreenLoop();

private:
	ui::ScreenInteractive m_Screen;
  boost::circular_buffer<float> m_ExecsPerSecHistory;
  std::unique_ptr<std::thread> m_UIThread;
  std::unique_ptr<std::thread> m_ScreenRefreshThread;
  std::atomic<bool> m_Running;
};

} // namespace plut::benchmark
