#ifndef COMMON_NET_SOCKET_HPP
#define COMMON_NET_SOCKET_HPP
#include <chrono>
#define ASIO_STANDALONE
#define ASIO_HAS_STD_CHRONO
#if defined(_WIN32) || defined(_WIN64)
#define _WIN32_WINDOWS
#endif
#include "../Common/third_party/asio/asio/include/asio.hpp"
#include <array>

#include "../Config.hpp"

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
