#ifndef APP_SCENES_PLAY_ONLINE_SCENE_HPP
#define APP_SCENES_PLAY_ONLINE_SCENE_HPP

#include "PlayScene.hpp"
#include "../Common/net/socket/Udp.hpp"

namespace app { namespace scenes {

  class PlayOnlineScene : public app::scenes::PlayScene
  {
    public:
      PlayOnlineScene(const std::shared_ptr<app::core::Game> &game);
      ~PlayOnlineScene();

    public:
      virtual void init() override;
      //   void update(const float dt);
      //   void draw();
      //
      // public:
      //   void drawGameBoard();
      //   GameState checkMoveState(const common::Point2D &p);
      //   void checkFinish();
      //   void quit();

      // public:
      //   void addPlayer(const std::shared_ptr<app::objects::Player> &player);
      //   void removePlayer(const std::shared_ptr<app::objects::Player> &player);

      // public:
      //   common::GameBoard getGameBoard() const;
      //   void setGameBoard(const common::GameBoard &#<{(| gb |)}>#);
      virtual void onSetGameBoardMove(const common::Point2D &p) override;
      virtual void quit() override;

    private:
      void run_service();
      void receive();

    private:
      // Network socket
      common::net::socket::Udp m_udpSocket;
      common::net::Socket::Buffer m_buffers;
      std::thread m_serviceThread;

      // Server
      common::net::socket::Udp::EndPoint m_udpServerEndpoint;

  };

} }

#endif
