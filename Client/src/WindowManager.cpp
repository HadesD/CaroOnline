#include "app/WindowManager.h"
#ifdef __linux
#  include <sys/ioctl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#elif _WIN32
#endif

namespace app {

  WindowManager::WindowManager()
  {
  }

  WindowManager::~WindowManager()
  {
  }

  int WindowManager::getHeight() const
  {
    winsize consoleSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &consoleSize);

    return consoleSize.ws_row;
  }

  int WindowManager::getWidth() const
  {
    winsize consoleSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &consoleSize);

    return consoleSize.ws_col;
  }

}
