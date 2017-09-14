#ifndef COMMON_NET_SOCKET
#define COMMON_NET_SOCKET
#include "../Network.hpp"

namespace common { namespace net {

  struct ResponseStruct
  {
    std::string unique_id;
  };

  class Socket : public std::enable_shared_from_this<Socket>
  {
    public:
      typedef asio::ip::tcp::socket SocketType;

    public:
      Socket(asio::io_service &/* s */);
      ~Socket();

    public:
      void send(const ResponseStruct &/* res */);
      void onSend();

    public:
      SocketType &getSocket();

    private:
      SocketType m_socket;
  };

} }

#endif
