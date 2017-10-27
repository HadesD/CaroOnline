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
    int port = 8889;

    if (argc > 1)
    {
      std::string s = argv[1];
      port = std::stoi(s);
    }

    app::Server server("0.0.0.0", port);

    server.run();
  }
  catch(const std::exception &e)
  {
    std::cerr << "Exeption: " << e.what() << std::endl;
  }

  std::cout << "Server shutdown" << std::endl;

  return 0;
}
