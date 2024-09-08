#include "TUIRenderer.hpp"
#include "BenchmarkLogger.hpp"
#include "Measurer.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/terminal.hpp>

namespace plut::benchmark {

TUIRenderer::TUIRenderer()
    : m_Screen{ ui::ScreenInteractive::Fullscreen() },
      m_ExecsPerSecHistory{ 500, 0 } {
}

TUIRenderer::~TUIRenderer() {
  if (m_Running) {
    stop();
  }
}

void TUIRenderer::startTUIThread() {
  m_UIThread = std::make_unique<std::thread>([this] {
    _startScreenLoop();
  });
}

void TUIRenderer::sendStats(const ExperimentStats& stats) {
  m_ExecsPerSecHistory.push_front(stats.spinsPerSec);
}

void TUIRenderer::_startScreenLoop() {
  m_Running = true;

  auto execsGraph{ [this](int width, int height) {
    std::vector<int> result(width, 0);
    auto max{ *std::max_element(m_ExecsPerSecHistory.begin(),
                                m_ExecsPerSecHistory.end()) };
    for (int i{ 0 }; i < width; i++) {
      result[i] = static_cast<int>(static_cast<float>(height) *
                                   (m_ExecsPerSecHistory.at(i) / max));
    }
    std::ranges::reverse(result);
    return result;
  } };

  auto graphsRenderer{ ui::Renderer([execsGraph] {
    using namespace ui;
    return vbox({
        text("Frequency [Mhz]") | hcenter,
        hbox({
            vbox({
                text("2400 "),
                filler(),
                text("1200 "),
                filler(),
                text("0 "),
            }),
            graph(std::ref(execsGraph)) | flex,
        }) | flex,
    });
  }) };

  m_ScreenRefreshThread = std::make_unique<std::thread>([this] {
    while (m_Running) {
      std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
      m_Screen.Post(ui::Event::Custom);
    }
  });

  m_Screen.Loop(graphsRenderer);
  m_Running = false;
  m_ScreenRefreshThread->join();
}

void TUIRenderer::stop() {
  m_Running = false;
  m_ScreenRefreshThread->join();
  m_UIThread->join();
};

} // namespace plut::benchmark
