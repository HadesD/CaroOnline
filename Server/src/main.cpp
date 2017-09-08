#include <iostream>

#include "app/Server.hpp"


int main(int /* argc */, char * /* argv */[])
{
  try
  {
    std::make_shared<app::Server>()->run();
  }
  catch(const std::runtime_error &e)
  {

  }

  return 0;
}
