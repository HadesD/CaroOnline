#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP
#include <iostream>
#include <memory>
#include <map>

#include "../Common/Config.hpp"
#include "../Common/net/socket/Udp.hpp"

namespace app {

  // class Room;

  class Server
  {
    public:
      typedef std::map<std::uint32_t, common::net::socket::Udp::EndPoint>
        ListClient;
      typedef ListClient::value_type Client;

    public:
      Server(const std::string &ip, const short &port);
      ~Server();

    public:
      void run();

    private:
      void init();
      void receive();
      void update(float dt);
      void onReceiveHandle(const std::string &/* data */);
      ListClient::key_type getOrCreateClientId(
        const ListClient::mapped_type &/* client */
        );

    private:
      common::net::socket::Udp m_udpSocket;
      ListClient m_clients;
      Client m_currentClient;
      common::net::Socket::Buffer m_buffers;

  };

}

#endif
