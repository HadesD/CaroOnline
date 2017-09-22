#ifndef COMMON_CONFIG_HPP
#define COMMON_CONFIG_HPP
#include <cstddef>

namespace common { namespace config {

  extern const std::size_t gameBoardRows;
  extern const std::size_t gameBoardCols;

  // Count To Win = maxCoupleCount + 1
  extern const int maxCoupleCount;

  const std::size_t maxNetworkBufferSize = 4096;

} }

#endif
