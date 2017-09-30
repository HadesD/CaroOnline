#include "Socket.hpp"

namespace common { namespace net {

  Socket::Socket() : m_ioService()
  {

  }

  Socket::~Socket()
  {
    m_ioService.stop();
  }

} }
