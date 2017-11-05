#ifndef APP_TYPE_HPP
#define APP_TYPE_HPP
#include <map>

#include "../Common/Config.hpp"
#include "../Common/net/socket/Udp.hpp"

namespace app {
  typedef common::net::socket::Udp::EndPoint Client;
}

#endif
