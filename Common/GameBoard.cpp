#include <iostream>

#include "GameBoard.hpp"

#include "../Common/Util.hpp"

namespace common {

  GameBoard::GameBoard()
  {
    this->m_board.assign(
      common::config::gameBoardRows,
      Board::value_type(common::config::gameBoardCols, 0)
      );
  }

  GameBoard::GameBoard(const std::size_t rows, const std::size_t cols)
  {
    this->m_board.assign(
      rows,
      Board::value_type(cols, 0)
      );
  }

  GameBoard::Board GameBoard::getBoard() const
  {
    return this->m_board;
  }

  void GameBoard::setBoard(const GameBoard::Board &board)
  {
    this->m_board = board;
  }

  void GameBoard::setBoard(const std::string &board)
  {
    std::vector< std::string > matBoard = Util::split(board, ':');

    for (std::size_t x = 0; x < m_board.size(); x++)
    {
      for (std::size_t y = 0; y < m_board.at(x).size(); y++)
      {
        std::string val = matBoard.at(x * common::config::gameBoardRows + y);

        m_board[x][y] = std::stoi(val.empty() ? std::string("0") : val);
      }
    }
  }

  std::vector< common::Point2D > GameBoard::getAvailablePoints() const
  {
    std::vector< common::Point2D > points;

    for (std::size_t x = 0; x < m_board.size(); x++)
    {
      for (std::size_t y = 0; y < m_board.at(x).size(); y++)
      {
        if (m_board.at(x).at(y) == 0)
        {
          points.emplace_back(common::Point2D(x, y));
        }
      }
    }

    return points;
  }

  std::vector< common::Point2D > GameBoard::getSelectedPoints() const
  {
    std::vector< common::Point2D > points;

    for (std::size_t x = 0; x < m_board.size(); x++)
    {
      for (std::size_t y = 0; y < m_board.at(x).size(); y++)
      {
        if (m_board.at(x).at(y) != 0)
        {
          points.emplace_back(common::Point2D(x, y));
        }
      }
    }

    return points;
  }

  std::string GameBoard::toString() const
  {
    std::string gb;

    for (std::size_t x = 0; x < m_board.size(); x++)
    {
      for (std::size_t y = 0; y < m_board.at(x).size(); y++)
      {
        if (m_board.at(x).at(y) != 0)
        {
          gb += std::to_string(m_board.at(x).at(y));
        }

        gb += ":";
      }
    }

    if (!gb.empty())
    {
      gb.pop_back();
    }

    return gb;
  }

  bool GameBoard::isWinPoint(const Point2D &p, const common::PlayerMark mark) const
  {
    int xP, yP, x0, y0, xMaxSize, yMaxSize;

    xP = p.x;
    yP = p.y;

    x0 = std::max(xP - common::config::maxCoupleCount, 0);
    y0 = std::max(yP - common::config::maxCoupleCount, 0);
    common::Point2D p0(x0, y0);

    xMaxSize = std::min(
      xP + common::config::maxCoupleCount + 1,
      static_cast<int>(m_board.size())
      );
    yMaxSize = std::min(
      yP + common::config::maxCoupleCount + 1,
      static_cast<int>(m_board.at(xMaxSize - 1).size())
      );
    common::Point2D pM(xMaxSize, yMaxSize);
    GameBoard::Rect r(p0, pM);

    // Game board likes:
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+

    // Check Hoz line
    return this->getHorizontalCount(p, mark, r) >= common::config::maxCoupleCount ||
        this->getVerticalCount(p, mark, r) >= common::config::maxCoupleCount ||
        this->getLeftDiagonalCount(p, mark, r) >= common::config::maxCoupleCount ||
        this->getRightDiagonalCount(p, mark, r) >= common::config::maxCoupleCount
        ;
  }

  std::size_t GameBoard::getHorizontalCount(
      const common::Point2D &p,
      const common::PlayerMark m,
      const GameBoard::Rect &r
      ) const
  {
    int count = 0;
    int max_count = 0;

    for (int y = r.p0.y; y < r.pM.y - 1; y++)
    {
      if (
        (m_board.at(p.x).at(y) == m) &&
        (m_board.at(p.x).at(y + 1) == m)
        )
      {
        count++;

        if (count > max_count)
        {
          max_count = count;
        }

        if (count >= common::config::maxCoupleCount)
        {
          break;
        }
      }
      else
      {
        count = 0;
      }
    }

    return max_count;
  }

  std::size_t GameBoard::getVerticalCount(
      const common::Point2D &p,
      const common::PlayerMark m,
      const GameBoard::Rect &r
      ) const
  {
    int count = 0;
    int max_count = 0;

    for (int x = r.p0.x; x < r.pM.x - 1; x++)
    {
      if (
          (m_board.at(x).at(p.y) == m) &&
          (m_board.at(x + 1).at(p.y) == m)
          )
      {
        count++;

        if (count > max_count)
        {
          max_count = count;
        }

        if (count >= common::config::maxCoupleCount)
        {
          break;
        }
      }
      else
      {
        count = 0;
      }
    }

    return max_count;
  }

  std::size_t GameBoard::getLeftDiagonalCount(
      const common::Point2D &p,
      const common::PlayerMark m,
      const GameBoard::Rect &r
      ) const
  {
    int count = 0;
    int max_count = 0;

    for (int x = r.p0.x, y = r.p0.y; x < r.pM.x - 1; x++, y++)
    {
      if (y >= r.pM.y - 1)
      {
        break;
      }
      if (
          (m_board.at(x).at(y) == m) &&
          (m_board.at(x + 1).at(y + 1) == m)
          )
      {
        count++;

        if (count > max_count)
        {
          max_count = count;
        }

        if (count >= common::config::maxCoupleCount)
        {
          break;
        }
      }
      else
      {
        count = 0;
      }
    }

    return max_count;
  }

  std::size_t GameBoard::getRightDiagonalCount(
      const common::Point2D &p,
      const common::PlayerMark m,
      const GameBoard::Rect &r
      ) const
  {
    int count = 0;
    int max_count = 0;

    for (int x = r.p0.x, y = r.pM.y - 1; x < r.pM.x - 1; x++, y--)
    {
      if (y <= r.p0.y)
      {
        break;
      }
      if (
          (m_board.at(x).at(y) == m) &&
          (m_board.at(x + 1).at(y - 1) == m)
          )
      {
        count++;

        if (count > max_count)
        {
          max_count = count;
        }

        if (count >= common::config::maxCoupleCount)
        {
          break;
        }
      }
      else
      {
        count = 0;
      }
    }
    return max_count;
  }

}
