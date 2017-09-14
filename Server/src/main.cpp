#include <iostream>

#include "app/Server.hpp"

int main(int argc, char *argv[])
{
  /*
   * if (argc < 2)
   * {
   *   std::cerr << "Usage: ./server <port>" << std::endl;

   *   return 1;
   * }
   */

  try
  {
    asio::io_service service;

    app::Server server(service);

    server.init();

    server.accept();

    service.run();

    std::cout << "Server shutdown" << std::endl;
  }
  catch(const std::exception &e)
  {
    std::cerr << "Exeption: " << e.what() << std::endl;
  }

  return 0;
}
