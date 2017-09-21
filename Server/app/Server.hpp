#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP
#include <iostream>
#include <memory>
#include <map>

#include "../Common/Config.hpp"
#include "../Common/Network.hpp"
#include "../Common/net/socket/Udp.hpp"

namespace app {

  // class Room;

  class Server
  {
    public:
      typedef std::map<std::u_int32_t, common::net::socket::Udp::EndPoint> ListClient;
      typedef ListClient::value_type Client;

    public:
      Server(const std::string &ip, const short &port);
      ~Server();

    public:
      void run();

    private:
      void init();
      void receive();
      void onReceive(
        const std::error_code &/* e */,
        const std::size_t &/* data */
        );
      Client::key_type getOrCreateClientId(
        const Client::mapped_type &/* client */
        );

    private:
      std::shared_ptr<common::net::socket::Udp> m_pUdpSocket;
      ListClient m_clients;
      Client m_currentClient;
      common::net::Socket::Buffer m_buffers;

  };

}

#endif
