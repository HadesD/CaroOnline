#ifndef COMMON_NET_SOCKET_UDP_HPP
#define COMMON_NET_SOCKET_UDP_HPP

#include "../Socket.hpp"

namespace common { namespace net { namespace socket {

  class Udp : public common::net::Socket
  {
    public:
      Udp(const std::string ip, const int &port);

    private:
      asio::ip::udp::socket m_socket;
  };

} } }

#endif
