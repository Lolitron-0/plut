#include "BenchmarkLogger.hpp"
#include "Measurer.hpp"
#include "SessionOptions.hpp"
#include "plut.hpp"
#include <csignal>
#include <cxxopts.hpp>
#include <iostream>

namespace plut::benchmark {

auto parseCliArgs(int argc, char** argv) -> SessionOptions {
  plut::benchmark::SessionOptions opts{};
  cxxopts::Options cliOptions{ "plut_benchmark",
                               "Tool for empirical slot statistics" };
  // clang-format off
  cliOptions.add_options()
		("help,h", "Display help")
		("slot-file", "path/to/slot.so", 
		 cxxopts::value<std::string>(opts.pathToSlot))
		("parallel,j", "Number of jobs to use", 
		 cxxopts::value<std::size_t>(opts.numJobs)
		 ->default_value(std::to_string(opts.numJobs)))
		("spins-per-trial", "Number of spins to use for each trial", 
		 cxxopts::value<int>(opts.spinsPerTrial)
		 ->default_value(std::to_string(opts.spinsPerTrial)))
		("max-trials", "Max number of trials to run (-1 for indefinite)", 
		 cxxopts::value<int>(opts.maxTrials)
		 ->default_value(std::to_string(opts.maxTrials)));
  // clang-format on

  cliOptions.parse_positional("slot-file");
  cliOptions.positional_help("/path/to/slot.so");
  auto cliMap{ cliOptions.parse(argc, argv) };

  if (cliMap.count("help") || cliMap.count("slot-file") == 0) {
    std::cout << cliOptions.help() << std::endl;
    std::exit(1); // NOLINT
  }

  if (cliMap.as_optional<std::size_t>("parallel").value_or(1) == 0) {
    std::cerr << "Bad parallel value" << std::endl;
    std::exit(1); // NOLINT
  }

  BenchmarkLogger().trace("Parsed command args");
  return opts;
}

} // namespace plut::benchmark

static std::function<void(int)> signalHandler{ [](int) {
} };

void signalHandlerWrapper(int sig) {
  std::cout << sig << std::endl;
  signalHandler(sig);
}

auto main(int argc, char* argv[]) -> int {
  auto sessionOptions{ plut::benchmark::parseCliArgs(argc, argv) };
  plut::benchmark::BenchmarkLogger().debug(
      "Trying to build load and build cusom slot from {}",
      sessionOptions.pathToSlot);
  std::shared_ptr<plut::core::SlotBase> slotInstance{
    plut::core::SlotLoader::buildCustomSlot(sessionOptions.pathToSlot)
  };
  plut::benchmark::BenchmarkLogger().debug(
      "Custom slot successfully loaded");

  plut::benchmark::Measurer measurer{ std::move(sessionOptions) };

  signalHandler = [&measurer](int sig) {
    std::string signalStr{ strsignal(sig) };
    plut::benchmark::BenchmarkLogger().warn("Got {} signal", signalStr);
    measurer.stop();
  };

  std::signal(SIGINT, signalHandlerWrapper);  // NOLINT
  std::signal(SIGTERM, signalHandlerWrapper); // NOLINT

  measurer.startExperiment(slotInstance);

  plut::benchmark::BenchmarkLogger().info("Exiting gracefully. Bye!");
}
