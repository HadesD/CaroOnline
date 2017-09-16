#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP
#include <iostream>
#include <memory>

#include "../Common/Config.hpp"
#include "../Common/Network.hpp"

namespace common {
  namespace net {
    class Connection;
  }
}

namespace app {

  // class Room;

  class Server
  {
    public:
      Server(asio::io_service &s, const short &port);
      ~Server();

    public:
      void run();

    private:
      void init();

    private:
      asio::io_service &m_pIoService;
      std::shared_ptr<common::net::Connection> m_pConnection;

      char m_buffer[];

      // Room m_room;
  };

}

#endif
