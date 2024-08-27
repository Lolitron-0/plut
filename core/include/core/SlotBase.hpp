#pragma once
#include "core/Board.hpp"
#include "core/Symbol.hpp"
#include "core/Types.hpp"

#include <random>

namespace plut::core {

class SlotBase {
public:
  using GenerationPassBuffer    = std::vector<GenerationPass>;
  using WinCollectionPassBuffer = std::vector<WinCollectionPass>;

  SlotBase(std::size_t maxRows, std::size_t maxCols);

  [[nodiscard]] auto getSymbols() const -> std::vector<Symbol>;
  [[nodiscard]] auto getTraversalPath() const -> TraversalPath;
  void setTraversalPath(const TraversalPath& traversalPath);
  void setSymbols(const std::vector<Symbol>& symbols);
  void addSymbol(const Symbol& symbol);

  void spin();

public:
  Board board;

protected:
  void registerGenerationPass(const GenerationPass& newPass);
  void registerWinCollectionPass(const WinCollectionPass& newPass);

private:
  [[nodiscard]] auto symbolsUniqueSet(
      const std::vector<Symbol>& symbols) const -> bool;
  [[nodiscard]] auto symbolsUniqueAdd(const Symbol& symbol) const
      -> bool;
  void _fillBoard();

private:
  std::vector<Symbol> m_Symbols;
  std::shared_ptr<std::mt19937_64> m_RandEngine;
  GenerationPassBuffer m_GenerationPasses;
  WinCollectionPassBuffer m_WinCollectionPasses;
  TraversalPath m_TraversalPath;
};

} // namespace plut::core
