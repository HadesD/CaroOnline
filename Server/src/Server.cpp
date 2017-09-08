#include "app/Server.hpp"

namespace app {

  Server::Server()
  {
  }

  Server::~Server()
  {
  }

  void Server::init()
  {
    std::cout << "Server initialized" << std::endl;
  }

  void Server::run()
  {
    this->init();

    std::cout << "Server shutdown" << std::endl;
  }

}
