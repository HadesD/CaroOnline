#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP
#include <iostream>
#include <memory>
#include <map>

#include "../Common/Config.hpp"
#include "../Common/net/socket/Udp.hpp"
#include "../Common/GameBoard.hpp"

namespace app {

  // class Room;

  class Server
  {
    public:
      typedef std::map<std::uint32_t, common::net::socket::Udp::EndPoint>
        ListClient;
      typedef ListClient::value_type Client;
      typedef common::GameBoard GameBoard;

    public:
      Server(const std::string &/* ip */, const short &/* port */);
      ~Server();

    public:
      void run();

    private:
      void init();
      void run_service();
      void receive();
      void update(const float /* dt */);
      void onReceiveHandle(const std::string &/* data */);
      void sendGameDataToAllClients();
      ListClient::key_type getClientId(
        const ListClient::mapped_type &/* client */
        ) const;
      ListClient::key_type getOrCreateClientId(
        const ListClient::mapped_type &/* client */
        );
      bool removeClientId(const ListClient::key_type /* id */);
      GameBoard getGameBoard() const;

    private:
      common::net::socket::Udp m_udpSocket;
      ListClient m_clients;
      Client m_currentClient;
      common::net::Socket::Buffer m_buffers;
      int m_seqNo;
      GameBoard m_gameBoard;
      std::thread m_serviceThread;

  };

}

#endif
