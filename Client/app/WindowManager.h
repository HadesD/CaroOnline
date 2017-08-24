#ifndef APP_WINDOW_MANAGER_H
#define APP_WINDOW_MANAGER_H

namespace app {

  class WindowManager
  {
    public:
      WindowManager();
      ~WindowManager();

    public:
      int getHeight() const;
      int getWidth() const;
  };

}

#endif
