#include "core/ContiguousMatrix.hpp"
namespace plut::core {

class SlotBase {
public:
  SlotBase(size_t rows, size_t columns);

private:
  ContiguousDynamicMatrix<int> m_Field;
};

} // namespace plut::core
