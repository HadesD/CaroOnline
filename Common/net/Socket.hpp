#ifndef COMMON_NET_SOCKET_HPP
#define COMMON_NET_SOCKET_HPP

#include "../Network.hpp"

namespace common { namespace net {

  class Socket
  {
    public:
      Socket(const std::string ip, const int &port);

    protected:
      asio::io_service m_ioService;

  };

} }

#endif
