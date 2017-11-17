#ifndef COMMON_GAME_BOARD_HPP
#define COMMON_GAME_BOARD_HPP
#include <vector>

#include "Config.hpp"
#include "Type.hpp"
#include "Point2D.hpp"

namespace common {

  class GameBoard
  {
    public:
      typedef std::vector< std::vector< common::PlayerMark > > Board;
      struct Rect
      {
          common::Point2D p0;
          common::Point2D pM;
          Rect(
              const common::Point2D &pMin,
              const common::Point2D &pMax
              ) : p0(pMin), pM(pMax){}
      };

    public:
      GameBoard();
      GameBoard(const std::size_t /* rows */, const std::size_t /* cols */);
      Board getBoard() const;
      void setBoard(const Board &/* board */);
      void setBoard(const std::string &/* board */);
      std::string toString() const;
      bool isWinPoint(const Point2D &p, const common::PlayerMark mark) const;
      std::vector< common::Point2D > getAvailablePoints() const;
      std::vector< common::Point2D > getSelectedPoints() const;

    public:
      std::size_t getHorizontalCount(
          const common::Point2D &p,
          const common::PlayerMark m,
          const GameBoard::Rect &r
          ) const;
      std::size_t getVerticalCount(
          const common::Point2D &p,
          const common::PlayerMark m,
          const GameBoard::Rect &r
          ) const;
      std::size_t getLeftDiagonalCount(
          const common::Point2D &p,
          const common::PlayerMark m,
          const GameBoard::Rect &r
          ) const;
      std::size_t getRightDiagonalCount(
          const common::Point2D &p,
          const common::PlayerMark m,
          const GameBoard::Rect &r
          ) const;

      private:
        Board m_board;
  };

}

#endif
