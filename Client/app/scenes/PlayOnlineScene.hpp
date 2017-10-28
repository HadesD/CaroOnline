#ifndef APP_SCENES_PLAY_ONLINE_SCENE_HPP
#define APP_SCENES_PLAY_ONLINE_SCENE_HPP

#include "PlayScene.hpp"
#include "../Common/net/socket/Udp.hpp"

namespace app { namespace scenes {

  class PlayOnlineScene : public app::scenes::PlayScene
  {
    public:
      PlayOnlineScene(std::shared_ptr<app::core::Game> game);
      ~PlayOnlineScene();

    public:
      virtual void init() override;
      virtual void onSetGameBoardMove(const common::Point2D &p) override;
      virtual bool quit() override;
      virtual void draw() override;

    private:
      void run_service();
      void receive();
      void onReceiveHandle(const std::string &data);

    private:
      // Network socket
      common::net::socket::Udp m_udpSocket;
      common::net::Socket::Buffer m_buffers;
      std::thread m_serviceThread;

      // Server
      common::net::socket::Udp::EndPoint m_udpServerEndpoint;
      common::net::socket::Udp::EndPoint m_udpCurrentEndpoint;
      unsigned int m_turn;
      int m_seqNo;

  };

} }

#endif
