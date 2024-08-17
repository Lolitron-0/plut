#include "core/SlotBase.hpp"

namespace plut::core {

SlotBase::SlotBase(size_t rows, size_t columns)
    : m_Field{rows, columns} {}

} // namespace plut::core
