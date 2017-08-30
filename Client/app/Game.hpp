#ifndef APP_GAME_HPP
#define APP_GAME_HPP
#include <memory>
#include <vector>
#include "app/Point2D.hpp"

namespace app {

  struct Point2D;
  class Player;
  class Game : public std::enable_shared_from_this<Game>
  {
    public:
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
      void addPlayer(const std::shared_ptr<Player> &player);
      void removePlayer(const std::shared_ptr<Player> &player);

    public:
      Point2D getCursor() const;
      void setCursor(const Point2D &c);
      int getKeyPushed() const;
      void setKeyPushed(const int &key);
      GameBoard getGameBoard() const;
      void setGameBoard(const Game::GameBoard &gb);
      ListPlayer getListPlayer() const;
      void setNextPlayer(const int &nextPlayer);
      int getCurrentPlayer() const;

    protected:
      GameBoard m_gameBoard;
      Point2D m_cursor;
      int m_keyPushed;
      ListPlayer m_listPlayer;
      bool isFinish;
      int m_currentPlayer;
  };

}

#endif
