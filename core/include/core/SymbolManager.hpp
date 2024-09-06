#pragma once
#include "core/Symbol.hpp"
#include "core/Types.hpp"
#include <unordered_map>

namespace plut::core {

class SymbolManager {
public:
  SymbolManager();

  [[nodiscard]] auto selectRandomSymbol() const -> Symbol;
  [[nodiscard]] auto getCurrentSetSymbols() const -> std::vector<Symbol>;
  void removeSymbolSet(std::string_view setName);
  void addSymbolSet(std::string_view setName,
                    std::vector<Symbol> symbols);
  void addSymbolToCurrentSet(Symbol symbol);
  void setCurrentSetSymbols(std::vector<Symbol> symbols);
  void switchCurrentSymbolSet(std::string_view setName);

private:
  RandEngineRef m_RandEngine;
  std::unordered_map<std::string_view, std::vector<Symbol>> m_SymbolSets;
  std::string_view m_CurrentSetName{ "default" };
};

} // namespace plut::core
