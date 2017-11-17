#include "Minimax.hpp"

#include <QtGlobal>

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

  return pos;
}
