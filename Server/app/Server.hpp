#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP
#include <iostream>
#include <memory>
#include <map>
#include <set>

#include "../Common/GameBoard.hpp"

#include "Type.hpp"
#include "Room.hpp"

namespace app {

  class Server
  {
    public:
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
      // void update(const float #<{(| dt |)}>#);
      void onReceiveHandle(const std::string &/* data */);
      void sendGameDataToAllClients();
      GameBoard getGameBoard() const;
      void onGameOver();

    private:
      Client::first_type getClientIndex(
        const Client::second_type &/* client */
        ) const;
      Client::first_type getOrCreateClientIndex(
        const Client::second_type &/* client */
        );
      bool removeClient(const Client::first_type /* index */);

    private:
      common::net::socket::Udp m_udpSocket;
      ListClient m_clients;
      Client m_workingClient;
      common::net::Socket::Buffer m_buffers;
      GameBoard m_gameBoard;
      std::thread m_serviceThread;
      int m_seqNo;
      unsigned int m_turn;
      bool m_isGameOver;

      std::set<Room> m_rooms;

  };

}

#endif
