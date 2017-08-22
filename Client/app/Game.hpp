#ifndef APP_GAME_HPP
#define APP_GAME_HPP
#include <vector>

namespace app {

  class Game
  {
    public:
      typedef std::vector< std::vector< int > > GameBoard;
      struct Cursor
      {
        Cursor(int x, int y);
        Cursor();
        int x;
        int y;
      };

    public:
      Game();
      ~Game();

    public:
      void init();
      void run();
      void drawGameBoard();

    public:
      Cursor getCursor() const;

    protected:
      GameBoard m_gameBoard;
      Cursor m_cursor();

  };

}

#endif
