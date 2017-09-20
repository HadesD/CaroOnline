#ifndef COMMON_NET_SOCKET_UDP_HPP
#define COMMON_NET_SOCKET_UDP_HPP

#include "../Socket.hpp"

namespace common { namespace net { namespace socket {

  class Udp : public common::net::Socket
  {
    public:
      typedef asio::ip::udp::endpoint EndPoint;

    public:
      Udp(const std::string &/* ip */, const short &/* port */);
      ~Udp();

    public:
      void open();
      void send(const std::string &/* data */, const EndPoint &/* endpoint */);
      void receive(Buffer &/* buffer */, EndPoint &/* endpoint */);

    private:
      asio::ip::udp::socket m_socket;
      // Endpoint m_endpoint;

  };

} } }

#endif
