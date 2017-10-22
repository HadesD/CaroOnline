#include <vector>

#include "Config.hpp"

namespace common {

  class GameBoard
  {
    public:
      typedef std::vector< std::vector< int > > Board;

    public:
      GameBoard();
      GameBoard(const std::size_t rows, const std::size_t cols);
      Board getBoard() const;
      void setBoard(const Board &board);

    private:
      Board m_board;
  };

}
