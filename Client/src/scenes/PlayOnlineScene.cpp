#include "app/scenes/PlayOnlineScene.hpp"

#include "app/Config.hpp"
#include "../Common/Logger.hpp"
#include "../Common/MessageStruct.hpp"

namespace app { namespace scenes {

  PlayOnlineScene::PlayOnlineScene(
    const std::shared_ptr<app::core::Game> &game
    ) : PlayScene(game),

  m_udpSocket("0.0.0.0", 0),
  m_udpServerEndpoint(
    asio::ip::address::from_string(app::config::serverIp),
    app::config::serverPort
    )
  {
    char cmd = static_cast<char>(common::MessageType::LOGIN);

    std::string msg = std::string(sizeof(cmd), cmd)
      + "Dark.Hades"
      + ":"
      + "password"
      ;

    m_udpSocket.send(
      msg, m_udpServerEndpoint,
      [this](const std::error_code &, const std::size_t &){
        this->receive();
      }
      );

  }

  PlayOnlineScene::~PlayOnlineScene()
  {
    if (m_serviceThread.joinable())
    {
      m_serviceThread.join();
    }
  }

  void PlayOnlineScene::init()
  {
    PlayScene::init();

    m_serviceThread = std::thread(&PlayOnlineScene::run_service, this);
  }

  void PlayOnlineScene::receive()
  {
    common::net::socket::Udp::EndPoint endp;
    // std::string s;
    // m_udpSocket.sync_recv(s, endp);
    // this->onReceiveHandle(s);
    // std::cin >> s;

    m_udpSocket.receive(
      m_buffers, endp,
      [this, endp](const std::error_code &e, const std::size_t &bytes)
      {
        std::string s;
        std::cin >> s;
        if (e)
        {
          Log::error(e.message());
        }
        else
        {
          if (endp == m_udpServerEndpoint)
          {
            std::string recv = std::string(m_buffers.data(), m_buffers.data() + bytes);
            Log::info(recv);
          }

          // this->onReceiveHandle(recv);
        }
        //this->receive();
      }
      );
  }

  void PlayOnlineScene::run_service()
  {
    try
    {
      m_udpSocket.open();
    }
    catch (const std::exception &e)
    {
      Log::error(e.what());
    }
    catch (...)
    {
      Log::error("Server :: run() :: openSocket()");
    }
  }

} }
