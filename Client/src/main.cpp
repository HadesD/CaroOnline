#include <iostream>

#include "app/core/Game.hpp"

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
  try
  {
    std::shared_ptr<app::core::Game>(new app::core::Game)->run();
  }
  catch(const std::runtime_error &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
