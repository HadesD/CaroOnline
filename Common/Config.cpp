#include "Config.hpp"
#include <cstddef>

namespace common { namespace config {

  const std::size_t gameBoardRows = 20;
  const std::size_t gameBoardCols = 20;

  const int maxCoupleCount = 4;

  // const std::size_t maxNetworkBufferSize;

  // const char networkCheckSum[] = "CARO";

  const std::string serverAddr = "0.0.0.0";
  const short serverPort = 8889;
  const short maxWaitTime = 30; // Second

} }
