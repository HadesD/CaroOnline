#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP
#include <iostream>
#include <memory>
#include <list>

// #include "Room.hpp"
#include "Type.hpp"
#include "../Common/net/socket/Udp.hpp"
#include "../Common/MessageStruct.hpp"

namespace app {

  class Room;

  class Server : public std::enable_shared_from_this<Server>
  {
    public:
      Server(const std::string &/* ip */, const int /* port */);
      ~Server();

    public:
      void run();
      void send(const Client &cli, const common::MessageStruct &msg);
      void removeRoom(const std::shared_ptr<Room> &r);

    private:
      void init();
      void run_service();
      void receive();
      // void update(const float #<{(| dt |)}>#);
      void addRoom();

    private:
      // Client::first_type getClientIndex(
      //   const Client::second_type &#<{(| client |)}>#
      //   ) const;
      // Client::first_type getOrCreateClientIndex(
      //   const Client::second_type &#<{(| client |)}>#
      //   );
      void onReceiveHandle(const std::string &data);

    private:
      // Socket
      common::net::socket::Udp m_udpSocket;
      Client m_workingClient;
      common::net::Socket::Buffer m_buffers;
      std::thread m_serviceThread;
      std::vector< std::shared_ptr<Room> > m_roomList;

  };

}

#endif
