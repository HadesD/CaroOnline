#include <iostream>

#include "app/Game.hpp"

int main(int /* argc */, char * /* argv */[])
{
  // (new app::Game())->run();

  std::shared_ptr<app::Game>(new app::Game)->run();

  return 0;
}
