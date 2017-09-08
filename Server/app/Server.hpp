#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP
#include <iostream>
#include <memory>

#include "../Common/Network.hpp"
#include "../Common/Config.hpp"

namespace app {

  class Server
  {
    public:
      Server(const asio::io_service &s);
      ~Server();

    public:
      void run();
      void init();
  };

}

#endif
