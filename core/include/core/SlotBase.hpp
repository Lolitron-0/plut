#pragma once
#include "core/Board.hpp"
#include "core/ContiguousMatrix.hpp"
#include "core/Symbol.hpp"
#include "core/Types.hpp"
#include <random>

namespace plut::core {

class SlotBase {
public:
  using GenerationPassBuffer    = std::vector<GenerationPass>;
  using WinCollectionPassBuffer = std::vector<WinCollectionPass>;

  SlotBase(std::size_t maxRows, std::size_t maxCols);

  [[nodiscard]] auto getBoardState() const
      -> const ContiguousDynamicMatrix<Symbol>&;
  [[nodiscard]] auto getTraversalPath() const -> TraversalPath;
  void setTraversalPath(const TraversalPath& traversalPath);
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
  TraversalPath m_TraversalPath;
};

} // namespace plut::core
