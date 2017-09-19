#ifndef COMMON_NET_SOCKET_HPP
#define COMMON_NET_SOCKET_HPP
#include <array>

#include "../Network.hpp"

namespace common { namespace net {

  class Socket
  {
    public:
      Socket();
      ~Socket();

    protected:
      asio::io_service m_ioService;
      std::array<char, common::config::maxNetworkBufferSize> m_recvBuffer;

  };

} }

#endif
