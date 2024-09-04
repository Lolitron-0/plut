#pragma once
#include "core/Board.hpp"
#include "core/Types.hpp"

namespace plut::core {

class SlotBase {
public:
  using FillPassBuffer          = std::vector<FillPass>;
  using WinCollectionPassBuffer = std::vector<WinCollectionPass>;

  SlotBase(std::size_t maxRows, std::size_t maxCols);

  [[nodiscard]] auto getSymbolManager() const -> SymbolManagerRef;
  [[nodiscard]] auto getTraversalPath() const -> TraversalPath;
  [[nodiscard]] auto getCurrentPayoutBetMultiplier() const -> float;
  void setTraversalPath(const TraversalPath& traversalPath);
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
	SymbolManagerRef m_SymbolManager;
  FillPassBuffer m_FillPasses;
  WinCollectionPassBuffer m_WinCollectionPasses;
  TraversalPath m_TraversalPath;

  float m_CurrentPayoutBetMultiplier{ 0 };
};

} // namespace plut::core
