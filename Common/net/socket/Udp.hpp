#ifndef COMMON_NET_SOCKET_UDP_HPP
#define COMMON_NET_SOCKET_UDP_HPP

#include "../Socket.hpp"
#include "../../MessageStruct.hpp"

namespace common { namespace net { namespace socket {

  class Udp : public common::net::Socket
  {
    public:
      typedef asio::ip::udp::endpoint EndPoint;

    public:
      Udp(const std::string &/* ip */, const short &/* port */);
      ~Udp();

    public:
      bool isOpening();
      void open();
      void send(
        const std::string &/* data */,
        const EndPoint &/* endpoint */,
        const onSendHandle &/* handle */
        );
      void send(
        const MessageStruct &/* data */,
        const EndPoint &/* endpoint */,
        const onSendHandle &/* handle */
        );
      void receive(
        Buffer &/* buffer */,
        EndPoint &/* endpoint */,
        const onReceiveHandle &/* handle */
        );
      void sync_recv(
        const std::string &s,
        EndPoint &/* endpoint */
        );

    private:
      asio::ip::udp::socket m_socket;

  };

} } }

#endif
