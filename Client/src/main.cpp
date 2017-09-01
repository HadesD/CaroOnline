#include <iostream>

#include "app/Game.hpp"

// void myStartupFun (void) __attribute__ ((constructor));
// void myCleanupFun (void) __attribute__ ((destructor));
// void myStartupFun (void)
// {
//   std::cout << "Before Main" << std::endl;
// }
// void myCleanupFun (void)
// {
//   std::cout << "After Main" << std::endl;
// }

int main(int /* argc */, char * /* argv */[])
{
  std::shared_ptr<app::Game>(new app::Game)->run();

  return 0;
}
