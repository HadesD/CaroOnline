#ifndef COMMON_NET_CONNECTION_HPP
#define COMMON_NET_CONNECTION_HPP
#include "../Network.hpp"

namespace common { namespace net {

  struct ResponseStruct
  {
    std::string unique_id;
  };

  class Connection
  {
    public:
      typedef asio::ip::tcp::socket SocketType;

    public:
      Connection(asio::io_service &/* s */);
      // ~Connection();

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
