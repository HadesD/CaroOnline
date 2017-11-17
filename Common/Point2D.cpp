#include "Point2D.hpp"

namespace common {

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

  bool Point2D::operator>(const Point2D &c)
  {
    return (x > c.x) && (y > c.y);
  }

  bool Point2D::operator<(const Point2D &c)
  {
    return (x < c.x) && (y < c.y);
  }

}
