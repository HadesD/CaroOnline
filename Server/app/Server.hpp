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
      Server(asio::io_service &s);
      ~Server();

    public:
      // void run();
      void init();
      void accept();

    private:
      // First Accept
      void onAcceptConnection(const std::error_code &/* e */);

      // Second Read recived data
      void onReadHeader(
        const std::error_code &/* e */,
        const std::size_t &/* bytes */
        );

      // Last Response
      void onResponse(
        const std::error_code &/* e */,
        const std::size_t &/* bytes */
        );

    private:
      asio::io_service &m_pIoService;
      asio::ip::tcp::acceptor m_acceptor;
      std::shared_ptr<common::net::Connection> m_pConnection;
      char m_buffer[];

      // Room m_room;
  };

}

#endif
