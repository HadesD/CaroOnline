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
    app::Server server("0.0.0.0", 8889);

    server.run();

    std::cout << "Server shutdown" << std::endl;
  }
  catch(const std::exception &e)
  {
    std::cerr << "Exeption: " << e.what() << std::endl;
  }

  return 0;
}
