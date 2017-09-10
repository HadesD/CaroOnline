#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP
#include <iostream>
#include <memory>

#include "../Common/Network.hpp"
#include "../Common/Config.hpp"

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
      void onAcceptConnection(const std::error_code &e);
      void readHeader();
      void onReadHeader(const std::error_code &e, const std::size_t &bytes);

    private:
      // asio::ip::udp m_acceptor;
      // asio::ip::udp::socket m_socket;

      asio::ip::tcp::acceptor m_acceptor;
      asio::ip::tcp::socket m_socket;
      char m_buffer[];

      // Room m_room;
  };

}

#endif
