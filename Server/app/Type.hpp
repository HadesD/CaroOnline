#ifndef APP_TYPE_HPP
#define APP_TYPE_HPP
#include <map>

#include "../Common/Config.hpp"
#include "../Common/net/socket/Udp.hpp"

namespace app {

  typedef std::map<unsigned int, common::net::socket::Udp::EndPoint> ListClient;
  typedef ListClient::value_type Client;

}

#endif
