#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include "../Common/GameBoard.hpp"
#include "../Common/Type.hpp"

class Minimax
{
  public:
    Minimax();

  public:
    common::Point2D getBestMove(
        const common::GameBoard gb,
        const common::PlayerMark m
        ) const;

  private:
    double evaluate() const;
    common::Point2D getRandPointAround(const common::Point2D& p) const;

};

#endif // MINIMAX_HPP
