#include <iostream>

#include "GameBoard.hpp"

#include "../Common/Util.hpp"

namespace common {

  GameBoard::GameBoard()
  {
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
    std::cout << toString() << std::endl;
  }

  void GameBoard::setBoard(const std::string &board)
  {
    // GameBoard::Board b;

    std::vector< std::string > matBoard = Util::str_split(board, ':');

    for (std::size_t x = 0; x < m_board.size(); x++)
    {
      for (std::size_t y = 0; y < m_board.at(x).size(); y++)
      {
        m_board[x][y] = std::stoi(matBoard.at(
            x * common::config::gameBoardRows + y
            ));
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
        gb += std::to_string(m_board.at(x).at(y));

        gb += ":";
      }
    }

    if (!gb.empty())
    {
      gb.pop_back();
    }

    return gb;
  }

}
