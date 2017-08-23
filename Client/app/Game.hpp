#ifndef APP_GAME_HPP
#define APP_GAME_HPP
#include <vector>

namespace app {

  class Game
  {
    public:
      struct Cursor
      {
        Cursor();
        Cursor(int x, int y);
        ~Cursor();
        bool operator==(const Cursor &c);
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
      void setCursor(const Cursor &c);
      int getKeyPushed() const;
      void setKeyPushed(const int &key);
      GameBoard getGameBoard() const;
      void setGameBoard(const Game::GameBoard &gb);

    protected:
      GameBoard m_gameBoard;
      Cursor m_cursor;
      int m_keyPushed;
  };

}

#endif
