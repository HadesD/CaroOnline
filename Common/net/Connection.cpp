#include "Connection.hpp"

namespace common { namespace net {

  Connection::Connection(asio::io_service &s) : m_socket(s)
  {
  }

  // Connection::~Connection()
  // {
  // }

  void Connection::send(const ResponseStruct &res)
  {
  }

  Connection::SocketType &Connection::getSocket()
  {
    return m_socket;
  }

} }
