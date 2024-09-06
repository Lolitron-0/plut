#include "core/SymbolManager.hpp"
#include "core/Assert.h"
#include <algorithm>
#include <set>

namespace plut::core {

SymbolManager::SymbolManager() {
  std::random_device rd;
  m_RandEngine = std::make_shared<std::mt19937_64>(rd());
  addSymbolSet("default", {});
}

auto SymbolManager::selectRandomSymbol() const -> Symbol {
  CORE_ASSERT(!m_SymbolSets.at(m_CurrentSetName).empty(),
              "No symbols to choose from");

  float weightSum{ 0 };
  for (const auto& symbol : m_SymbolSets.at(m_CurrentSetName)) {
    weightSum += symbol.getWeight();
  }
  std::uniform_real_distribution<float> distrib{ 0, weightSum };
  float targetWeight{ distrib(*m_RandEngine) };
  for (const auto& symbol : m_SymbolSets.at(m_CurrentSetName)) {
    if (targetWeight < symbol.getWeight()) {
      return symbol;
    }
    targetWeight -= symbol.getWeight();
  }

  CORE_ASSERT(false, "Unreachable: weight generation failed");
}

auto SymbolManager::getCurrentSetSymbols() const -> std::vector<Symbol> {
  return m_SymbolSets.at(m_CurrentSetName);
}

void SymbolManager::removeSymbolSet(std::string_view setName) {
  CORE_ASSERT(m_SymbolSets.contains(setName), "No such symbol set: {}",
              setName);
  m_SymbolSets.erase(setName);
}

void SymbolManager::addSymbolSet(std::string_view setName,
                                 std::vector<Symbol> symbols) {
  CORE_ASSERT(!m_SymbolSets.contains(setName), "{} set already exists",
              setName);
  CORE_ASSERT(std::set(symbols.begin(), symbols.end()).size() ==
                  symbols.size(),
              "Set contains repeating symbols");
  m_SymbolSets[setName] = std::move(symbols);
}

void SymbolManager::addSymbolToCurrentSet(Symbol symbol) {
  CORE_ASSERT(std::ranges::find(m_SymbolSets[m_CurrentSetName], symbol) ==
                  m_SymbolSets[m_CurrentSetName].end(),
              "Slot contains repeating symbols");
  m_SymbolSets[m_CurrentSetName].push_back(symbol);
}

void SymbolManager::setCurrentSetSymbols(std::vector<Symbol> symbols) {
  CORE_ASSERT(std::set(symbols.begin(), symbols.end()).size() ==
                  symbols.size(),
              "Set contains repeating symbols");
  m_SymbolSets[m_CurrentSetName] = std::move(symbols);
}

void SymbolManager::switchCurrentSymbolSet(std::string_view setName) {
  CORE_ASSERT(m_SymbolSets.contains(setName), "No such symbol set: {}",
              setName);
  m_CurrentSetName = setName;
}

} // namespace plut::core
