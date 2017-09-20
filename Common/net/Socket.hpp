#ifndef COMMON_NET_SOCKET_HPP
#define COMMON_NET_SOCKET_HPP
#include <array>

#include "../Network.hpp"

namespace common { namespace net {

  class Socket
  {
    public:
      typedef std::array<char, common::config::maxNetworkBufferSize> Buffer;
      typedef std::function<
        void(const std::error_code &, const std::size_t &)
        > onReceiveHandle;
      typedef std::function<
        void(const std::error_code &, const std::size_t &)
        > onSendHandle;

    public:
      Socket();
      ~Socket();

    protected:
      asio::io_service m_ioService;
      // m_recvBuffer;

  };

} }

#endif
