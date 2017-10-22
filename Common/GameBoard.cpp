#include "GameBoard.hpp"

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
  }

}
