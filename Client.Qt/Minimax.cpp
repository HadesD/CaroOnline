#include "Minimax.hpp"

#include <QtGlobal>
#include <QDebug>

Minimax::Minimax()
{
}

common::Point2D Minimax::getBestMove(
    const common::GameBoard gb,
    const common::PlayerMark m
    ) const
{
  common::Point2D pos(
        qrand() % common::config::gameBoardRows,
        qrand() % common::config::gameBoardCols
        );
  auto selected =  gb.getSelectedPoints();

  if (selected.size() <= 2)
  {
    for (const auto& p : selected)
    {
      if (gb.getBoard().at(p.x).at(p.y) != m)
      {
        pos = this->getRandPointAround(p);
        break;
      }
    }
  }
  else
  {
    auto unselected = gb.getAvailablePoints();
    for (const auto& p : unselected)
    {
      int xP, yP, x0, y0, xMaxSize, yMaxSize;

      xP = p.x;
      yP = p.y;

      x0 = std::max(xP - 2, 0);
      y0 = std::max(yP - 2, 0);
      common::Point2D p0(x0, y0);

      xMaxSize = std::min(
            xP + 2 + 1,
            static_cast<int>(gb.getBoard().size())
            );
      yMaxSize = std::min(
            yP + 2 + 1,
            static_cast<int>(gb.getBoard().at(xMaxSize - 1).size())
            );
      common::Point2D pM(xMaxSize, yMaxSize);
      common::GameBoard::Rect r(p0, pM);

      common::PlayerMark mark = 1;
      bool ret = gb.getHorizontalCount(p, mark, r) >= 1 ||
          gb.getRightDiagonalCount(p, mark, r) >= 1 ||
          gb.getLeftDiagonalCount(p, mark, r) >= 1 ||
          gb.getVerticalCount(p, mark, r) >= 1
          ;

      qDebug() << gb.getHorizontalCount(p, 1, r);
      qDebug() << gb.getVerticalCount(p, 1, r);
      qDebug() << gb.getRightDiagonalCount(p, 1, r);
      qDebug() << gb.getLeftDiagonalCount(p, 1, r);

      qDebug() << ret;

      if (ret)
      {
        pos = common::Point2D(p.x,p.y);
        break;
      }
    }
  }

  return pos;
}

common::Point2D Minimax::getRandPointAround(const common::Point2D& p) const
{
  common::Point2D pos;

  while (true)
  {
    int r = qrand() % 4;
    switch (r)
    {
      case 0:
      {
        pos.x = p.x;
        pos.y = p.y + 1;
      }
        break;
      case 1:
      {
        pos.x = p.x + 1;
        pos.y = p.y;
      }
        break;
      case 2:
      {
        pos.x = p.x;
        pos.y = p.y - 1;
      }
        break;
      case 3:
      {
        pos.x = p.x - 1;
        pos.y = p.y;
      }
        break;
      default:
        break;
    }

    if (!(pos == p))
    {
      break;
    }
  }

  return pos;
}
