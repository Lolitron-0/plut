#include "TUIRenderer.hpp"
#include "BenchmarkLogger.hpp"
#include "Measurer.hpp"
#include "Utils.hpp"
#include <csignal>
#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/terminal.hpp>
#include <spdlog/fmt/chrono.h>
#include <spdlog/fmt/fmt.h>

namespace plut::benchmark {

TUIRenderer::TUIRenderer(SessionOptions opts, Measurer* parent)
    : m_SessionOpts{ std::move(opts) },
      m_ExecsPerSecHistory(500, 0.F),
      m_Parent{ parent } {
}

TUIRenderer::~TUIRenderer() {
  if (m_Running) {
    stop();
  }
}

void TUIRenderer::startUIThread() {
  m_UIThread = std::make_unique<std::thread>([this] {
    _startScreenLoop();
  });
}

void TUIRenderer::sendStats(const ExperimentStats& stats) {
  std::lock_guard lock{ m_DataMutex };
  m_GotFirstStats = stats.valid;
  if (!stats.valid) {
    return;
  }
  m_ExecsPerSecHistory.push_front(stats.spinsPerSec);
  m_TrialProgress =
      static_cast<float>(stats.trialSpins) / m_SessionOpts.spinsPerTrial;
  std::cout << stats.trialSpins;
}

void TUIRenderer::_startScreenLoop() {
  using namespace ui;
  m_Running = true;

  m_Screen = std::make_shared<ui::ScreenInteractive>(
      plut::benchmark::utils::LazyPRValue{ [] {
        return ui::ScreenInteractive::Fullscreen();
      } });

  auto mainRenderer{ ui::Renderer([&, spinnerFrame = 0]() mutable {
    if (m_GotFirstStats) {
      auto now{ std::chrono::system_clock::now() };
      auto timeStr{ fmt::format("{:%H:%M}", now) };
      return vbox({ hbox({ filler(),
                           text("PLUT BENCHMARK") | hcenter |
                               color(Color::Purple),
                           filler(),
                           text(timeStr) | color(Color::Violet) }) |
                        xflex | yflex_shrink,
                    separator(),
                    hbox({ _getExecsPerSecGraph() | flex }) | yflex |
                        size(HEIGHT, Constraint::LESS_THAN, 20),
                    separator(),
                    hbox({ text("Trial progress: ") | vcenter,
                           gaugeRight(m_TrialProgress) | flex | border |
                               color(Color::LightSteelBlue),
                           text(core::utils::prettyPostfix(
                               m_SessionOpts.spinsPerTrial *
                               m_TrialProgress)) |
                               vcenter }) |
                        xflex,
                    separator() }) |
             flex_grow | border;
    }

    return vbox({ filler(),
                  vbox({ text("Waiting for first stats...") | hcenter,
                         spinner(20, spinnerFrame++) | hcenter }) |
                      center | border,
                  filler() }) |
           flex;
  }) };

  m_ScreenRefreshThread = std::make_unique<std::thread>([this] {
    while (m_Running) {
      std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
      m_Screen->Post(ui::Event::Custom);
    }
  });

  m_Screen->Loop(mainRenderer);
  // exited from UI loop
  m_Parent->notifyUIExit();
}

void TUIRenderer::stop() {
  m_Running = false;
  m_ScreenRefreshThread->join();
  m_UIThread->join();
};

auto TUIRenderer::_getExecsPerSecGraph() -> ui::Element {
  using namespace ui;

  auto execsGraphFn{ [this](int width, int height) {
    std::lock_guard lock{ m_DataMutex };
    std::vector<int> result(width, 0);
    m_ExecsPerSecBounds.first =
        *std::min_element(m_ExecsPerSecHistory.begin(),
                          m_ExecsPerSecHistory.begin() + width + 1);
    m_ExecsPerSecBounds.second =
        *std::max_element(m_ExecsPerSecHistory.begin(),
                          m_ExecsPerSecHistory.begin() + width + 1);
    for (int i{ 0 }; i < width; i++) {
      result[i] = static_cast<int>(
          static_cast<float>(height) *
          ((m_ExecsPerSecHistory.at(i) - m_ExecsPerSecBounds.first) /
           (m_ExecsPerSecBounds.second - m_ExecsPerSecBounds.first)));
    }
    std::ranges::reverse(result);
    return result;
  } };

  auto execsGraph{
    vbox({
        text("Execs per sec") | hcenter,
        hbox({
            vbox({
                text(plut::core::utils::prettyPostfix(
                    static_cast<std::size_t>(
                        m_ExecsPerSecBounds.second))),
                filler(),
                text(plut::core::utils::prettyPostfix(
                    static_cast<std::size_t>(m_ExecsPerSecBounds.first))),
            }),
            separator(),
            graph(execsGraphFn) | flex,
        }) | flex |
            border,
    }) |
    flex
  };
  return execsGraph;
}
} // namespace plut::benchmark