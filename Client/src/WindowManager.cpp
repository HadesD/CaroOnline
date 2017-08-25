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
    int h = 0;
#ifdef __linux
    winsize consoleSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &consoleSize);
    h = consoleSize.ws_row;
#endif

    return h;
  }

  int WindowManager::getWidth() const
  {
    int w = 0;
#ifdef __linux
    winsize consoleSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &consoleSize);
    w = consoleSize.ws_col;
#endif

    return w;
  }

}
