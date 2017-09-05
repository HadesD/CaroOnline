#ifndef APP_SCENES_PLAY_SCENE_HPP
#define APP_SCENES_PLAY_SCENE_HPP
#include <vector>

#include "app/Scene.hpp"
#include "app/Point2D.hpp"

namespace app {
  namespace core {
    class Game;
  }
  class Player;
}

namespace app { namespace scenes {

  class PlayScene : public app::Scene
  {
    public:
      typedef std::vector< std::vector< int > > GameBoard;
      typedef std::vector< std::shared_ptr< app::Player > > ListPlayer;

    public:
      PlayScene(std::shared_ptr<app::core::Game> game);
      ~PlayScene();

    public:
      void init();
      void update(float dt);
      void draw();

    public:
      void drawGameBoard();
      void checkFinish();
      void quit();

    public:
      void addPlayer(const std::shared_ptr<Player> &player);
      void removePlayer(const std::shared_ptr<Player> &player);

    public:
      GameBoard getGameBoard() const;
      void setGameBoard(const GameBoard &gb);
      ListPlayer getListPlayer() const;
      void setNextPlayer(const int &nextPlayer);
      int getCurrentPlayer() const;
      Point2D getCursor() const;
      void setCursor(const Point2D &c);

    protected:
      GameBoard m_gameBoard;
      ListPlayer m_listPlayer;
      int m_currentPlayer;
      Point2D m_cursor;
      bool m_isFinish;

    private:
      std::size_t m_gameBoardOneObjSize;

  };

} }

#endif
