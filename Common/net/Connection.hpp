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
      using Protocol = asio::ip::udp;
      typedef Protocol::socket Socket;
      typedef Protocol::endpoint Endpoint;

    public:
      Connection(asio::io_service &/* s */, const short &/* port */);
      ~Connection();

    public:
      void receive();
      void send(const ResponseStruct &/* res */);

    private:
      void onReceive(
        const std::error_code &/* e */,
        const std::size_t &/* bytes */
        );
      void onSend();

    public:
      Socket &getSocket();

    private:
      Socket m_socket;
      Endpoint m_endpoint;
      std::array< char, 512 > m_buffer;
  };

} }

#endif
