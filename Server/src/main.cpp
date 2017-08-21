#include <iostream>

#include "app/Server.hpp"


int main(int /* argc */, char * /* argv */[])
{
  (new Server())->run();

  return 0;
}
