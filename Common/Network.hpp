#ifndef COMMON_NETWORK_HPP
#define COMMON_NETWORK_HPP
#include "Config.hpp"
#include <chrono>
#define ASIO_STANDALONE
// define this or Asio will use system's default time API instead of C++11 chrono
#define ASIO_HAS_STD_CHRONO
#include <asio.hpp>

#endif
