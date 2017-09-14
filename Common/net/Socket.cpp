#include "Socket.hpp"

namespace common { namespace net {

  Socket::Socket(asio::io_service &s) : m_socket(s)
  {
  }

  Socket::~Socket()
  {
  }

  void Socket::send(const ResponseStruct &res)
  {
  }

  Socket::SocketType &Socket::getSocket()
  {
    return m_socket;
  }

} }
