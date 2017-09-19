#ifndef COMMON_CONFIG_HPP
#define COMMON_CONFIG_HPP
#include <cstddef>

namespace common { namespace config {

  extern const std::size_t gameBoardRows;
  extern const std::size_t gameBoardCols;

  extern const int maxCoupleCount; // Count To Win = maxCoupleCount + 1

  static const std::size_t maxNetworkBufferSize = 2;

} }

#endif
