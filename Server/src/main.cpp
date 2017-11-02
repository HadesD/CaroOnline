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
    short port = common::config::serverPort;

    if (argc > 1)
    {
      std::string s = argv[1];
      port = std::stoi(s);
    }
    std::cout << "Choosen port: " <<  port << std::endl;

    app::Server server(common::config::serverAddr, port);

    server.run();
  }
  catch(const std::exception &e)
  {
    std::cerr << "Exeption: " << e.what() << std::endl;
  }

  std::cout << "Server shutdown" << std::endl;

  return 0;
}
