#ifndef APP_GAME_HPP
#define APP_GAME_HPP
#include <memory>
#include <vector>

namespace app {

  class Player;
  class Game : public std::enable_shared_from_this<Game>
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
      typedef std::vector< std::shared_ptr< Player > > ListPlayer;

    public:
      Game();
      ~Game();

    public:
      void init();
      void run();
      void drawGameBoard();
      void update();
      void waitKeyboardEvent();
      void checkFinish();

    public:
      void addPlayer(std::shared_ptr<Player> player);

    public:
      Cursor getCursor() const;
      void setCursor(const Cursor &c);
      int getKeyPushed() const;
      void setKeyPushed(const int &key);
      GameBoard getGameBoard() const;
      void setGameBoard(const Game::GameBoard &gb);
      ListPlayer getListPlayer() const;

    protected:
      GameBoard m_gameBoard;
      Cursor m_cursor;
      int m_keyPushed;
      ListPlayer m_listPlayer;
      bool isFinish;
  };

}

#endif
