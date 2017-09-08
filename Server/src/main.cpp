#include <iostream>

#include "app/Server.hpp"

int main(int /* argc */, char * /* argv */[])
{
  try
  {
    asio::io_service s;

    std::make_shared<app::Server>(s)->run();
  }
  catch(const std::runtime_error &e)
  {

  }

  return 0;
}
