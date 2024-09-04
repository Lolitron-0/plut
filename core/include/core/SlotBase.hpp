#pragma once
#include "core/Board.hpp"
#include "core/Symbol.hpp"
#include "core/Types.hpp"

#include <random>

namespace plut::core {

class SlotBase {
public:
  using FillPassBuffer          = std::vector<FillPass>;
  using WinCollectionPassBuffer = std::vector<WinCollectionPass>;

  SlotBase(std::size_t maxRows, std::size_t maxCols);

  [[nodiscard]] auto getSymbols() const -> std::vector<Symbol>;
  [[nodiscard]] auto getTraversalPath() const -> TraversalPath;
  [[nodiscard]] auto getCurrentPayoutBetMultiplier() const -> float;
  void setTraversalPath(const TraversalPath& traversalPath);
  void setSymbols(const std::vector<Symbol>& symbols);
  void addSymbol(const Symbol& symbol);
  void addToPayoutMultiplier(float value);

  void spin();

public:
  Board board;

protected:
  void registerFillPass(const FillPass& newPass);
  void registerWinCollectionPass(const WinCollectionPass& newPass);


private:
  void _resetState();
  void _fillBoard();

private:
  std::vector<Symbol> m_Symbols;
  std::shared_ptr<std::mt19937_64> m_RandEngine;
  FillPassBuffer m_FillPasses;
  WinCollectionPassBuffer m_WinCollectionPasses;
  TraversalPath m_TraversalPath;

  float m_CurrentPayoutBetMultiplier{ 0 };
};

} // namespace plut::core
