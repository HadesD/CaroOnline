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

    xMaxSize = std::min(
      xP + common::config::maxCoupleCount + 1,
      static_cast<int>(m_board.size())
      );
    yMaxSize = std::min(
      yP + common::config::maxCoupleCount + 1,
      static_cast<int>(m_board.at(xMaxSize-1).size())
      );

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
    int count;

    // Check Hoz line
    count = 0;
    for (int y = y0; y < yMaxSize - 1; y++)
    {
      if (
        (m_board.at(xP).at(y) == mark) &&
        (m_board.at(xP).at(y + 1) == mark)
        )
      {
        count++;
      }
      else
      {
        count = 0;
      }

      if (count >= common::config::maxCoupleCount)
      {
        return true;
      }
    }

    // Check vert
    count = 0;
    for (int x = x0; x < xMaxSize - 1; x++)
    {
      if (
        (m_board.at(x).at(yP) == mark) &&
        (m_board.at(x + 1).at(yP) == mark)
        )
      {
        count++;
      }
      else
      {
        count = 0;
      }

      if (count >= common::config::maxCoupleCount)
      {
        return true;
      }
    }

    // Check diagonal L->R
    count = 0;
    for (int x = x0, y = y0; x < xMaxSize - 1; x++, y++)
    {
      if (y >= yMaxSize - 1)
      {
        break;
      }
      if (
        (m_board.at(x).at(y) == mark) &&
        (m_board.at(x + 1).at(y + 1) == mark)
        )
      {
        count++;
      }
      else
      {
        count = 0;
      }

      if (count >= common::config::maxCoupleCount)
      {
        return true;
      }
    }

    // Check diagonal R->L
    count = 0;
    for (int x = x0, y = yMaxSize - 1; x < xMaxSize - 1; x++, y--)
    {
      if (y <= y0)
      {
        break;
      }
      if (
        (m_board.at(x).at(y) == mark) &&
        (m_board.at(x + 1).at(y - 1) == mark)
        )
      {
        count++;
      }
      else
      {
        count = 0;
      }

      if (count >= common::config::maxCoupleCount)
      {
        return true;
      }
    }

    return false;
  }

}

