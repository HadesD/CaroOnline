#include "app/Point2D.hpp"

namespace app {

  Point2D::Point2D()
  {
  }

  Point2D::~Point2D()
  {
  }

  Point2D::Point2D(int x, int y) : x(x), y(y)
  {
  }

  bool Point2D::operator==(const Point2D &c)
  {
    return (x == c.x) && (y == c.y);
  }

}
