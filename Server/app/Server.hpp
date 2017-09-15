#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP
#include <iostream>
#include <memory>

#include "../Common/Network.hpp"
#include "../Common/Config.hpp"

namespace common {
  namespace net {
    class Socket;
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
      void onAcceptConnection(
        // const std::unique_ptr<common::net::Socket> &#<{(| socket |)}>#,
        const std::error_code &/* e */
        );

      // Second Read recived data
      void onReadHeader(
        // const std::unique_ptr<common::net::Socket> &#<{(| socket |)}>#,
        const std::error_code &/* e */,
        const std::size_t &/* bytes */
        );

      // Last Response
      void onResponse(
        // const std::unique_ptr<common::net::Socket> &#<{(| socket |)}>#,
        const std::error_code &/* e */,
        const std::size_t &/* bytes */
        );

    private:
      // asio::ip::udp m_acceptor;

      asio::io_service &m_pIoService;
      asio::ip::tcp::acceptor m_acceptor;
      std::shared_ptr<common::net::Socket> m_pSocket;
      char m_buffer[];

      // Room m_room;
  };

}

#endif
