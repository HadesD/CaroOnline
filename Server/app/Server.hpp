#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP
#include <iostream>
#include <memory>

#include "../Common/Network.hpp"
#include "../Common/Config.hpp"

namespace app {

  class Room;

  class Server
  {
    public:
      Server(asio::io_service &s);
      ~Server();

    public:
      // void run();
      void init();
      void accept();

    private:
      void onAcceptConnection(const std::error_code &e);

    private:
      asio::ip::tcp::acceptor m_acceptor;
      asio::ip::tcp::socket m_socket;

      // Room m_room;
  };

}

#endif
