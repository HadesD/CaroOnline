#ifndef APP_POINT_2D_HPP
#define APP_POINT_2D_HPP

namespace app {

  struct Point2D
  {
    Point2D();
    Point2D(int x, int y);
    ~Point2D();
    bool operator==(const Point2D &c);
    int x;
    int y;
  };

}

#endif
