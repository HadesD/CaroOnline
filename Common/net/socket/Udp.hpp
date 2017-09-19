#ifndef COMMON_NET_SOCKET_UDP_HPP
#define COMMON_NET_SOCKET_UDP_HPP

#include "../Socket.hpp"

namespace common { namespace net { namespace socket {

  class Udp : public common::net::Socket
  {
    public:
      typedef asio::ip::udp::endpoint Endpoint;

    public:
      Udp(const std::string &/* ip */, const short &/* port */);
      ~Udp();

    public:
      void send(const std::string &/* s */, const Endpoint &/* endpoint */);

    private:
      asio::ip::udp::socket m_socket;

  };

} } }

#endif
