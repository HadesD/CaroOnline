#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP
#include <iostream>
#include <memory>

namespace app {

  class Server
  {
    public:
      Server();
      ~Server();

    public:
      void run();
      void init();
  };

}

#endif
