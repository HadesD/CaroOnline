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

int main(/* int argc, char *argv[] */)
{
  try
  {
    std::make_shared<app::core::Game>()->run();
  }
  catch(const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
