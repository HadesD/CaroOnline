#ifndef APP_SCENES_PLAY_SCENE_HPP
#define APP_SCENES_PLAY_SCENE_HPP
#include <vector>

#include "app/Scene.hpp"
#include "../Common/Point2D.hpp"
#include "../Common/GameBoard.hpp"

namespace app
{
  namespace core
  {
    class Game;
  }
  namespace objects {
    class Player;
  }
}

namespace app { namespace scenes {

  class PlayScene : public app::Scene
  {
    public:
      // typedef common::GameBoard GameBoard;
      typedef std::vector< std::shared_ptr< app::objects::Player > > ListPlayer;
      enum class GameState
      {
        WIN,
        LOSE,
        DRAW
      };

    public:
      PlayScene(const std::shared_ptr<app::core::Game> &game);
      ~PlayScene();

    public:
      virtual void init();
      void update(const float dt);
      void draw();

    public:
      void drawGameBoard();
      GameState checkMoveState(const common::Point2D &p);
      void checkFinish();
      void quit();

    public:
      void addPlayer(const std::shared_ptr<app::objects::Player> &player);
      void removePlayer(const std::shared_ptr<app::objects::Player> &player);

    public:
      common::GameBoard getGameBoard() const;
      void setGameBoard(const common::GameBoard &/* gb */);
      ListPlayer getListPlayer() const;
      void setNextPlayer(const unsigned int nextPlayer);
      void setNextPlayer(const std::shared_ptr<app::objects::Player> &player);
      int getCurrentPlayer() const;
      // void onSetGameBoardMove();

    protected:
      common::GameBoard m_gameBoard;
      ListPlayer m_listPlayer;
      unsigned int m_currentPlayer;
      bool m_isFinish;

    private:
      std::size_t m_gameBoardOneObjSize;

  };

} }

#endif
