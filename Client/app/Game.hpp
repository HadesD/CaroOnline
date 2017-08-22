#ifndef APP_GAME_HPP
#define APP_GAME_HPP
#include <vector>

namespace app {

  class Game
  {
    public:
      struct Cursor
      {
        bool operator==(Cursor &c);
        Cursor();
        Cursor(int x, int y);
        ~Cursor();
        int x;
        int y;
      };
      typedef std::vector< std::vector< int > > GameBoard;

    public:
      Game();
      ~Game();

    public:
      void init();
      void run();
      void drawGameBoard();
      void update();

    public:
      Cursor getCursor() const;
      void setKeyPushed(const int key);
      int getKeyPushed() const;

    protected:
      GameBoard m_gameBoard;
      Cursor m_cursor;
      int m_keyPushed;

  };

}

#endif
