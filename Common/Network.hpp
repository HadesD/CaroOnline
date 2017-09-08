#ifndef COMMON_NETWORK_HPP
#define COMMON_NETWORK_HPP
#define ASIO_STANDALONE
// define this or Asio will use system's default time API instead of C++11 chrono
#define ASIO_HAS_STD_CHRONO
#include <chrono>
#include <asio.hpp>
// #include "third_party/asio/asio/include/asio.hpp"

#endif
