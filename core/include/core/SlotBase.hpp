#pragma once
#include "core/Board.hpp"
#include "core/ContiguousMatrix.hpp"
#include "core/Symbol.hpp"
#include <random>

namespace plut::core {

// TODO: event driven
struct GenerationPassResult {
  bool rerunGeneration{ false };
};

struct WinCollectionPassResult {
  bool rerunGeneration{ false };
  bool endWinCollection{ false };
};

class SlotBase {
public:
  using GenerationPass = std::function<GenerationPassResult(Board&)>;
  using GenerationPassBuffer = std::vector<GenerationPass>;
  using WinCollectionPass =
      std::function<WinCollectionPassResult(Board&)>;
  using WinCollectionPassBuffer = std::vector<WinCollectionPass>;

  SlotBase(std::size_t maxRows, std::size_t maxCols);

  [[nodiscard]] auto getBoardState() const
      -> const ContiguousDynamicMatrix<Symbol>&;
  void addSymbols(std::vector<Symbol>&& symbols);

  void spin();

protected:
  void registerGenerationPass(const GenerationPass& newPass);
  void registerWinCollectionPass(const WinCollectionPass& newPass);

private:
  void _resetState();

private:
  Board m_Board;
  std::vector<Symbol> m_Symbols;
  std::shared_ptr<std::mt19937_64> m_RandEngine;
  GenerationPassBuffer m_GenerationPasses;
  WinCollectionPassBuffer m_WinCollectionPasses;
};

} // namespace plut::core
