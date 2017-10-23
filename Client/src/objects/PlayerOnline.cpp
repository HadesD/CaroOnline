#include "app/objects/PlayerOnline.hpp"

#include "app/Config.hpp"
#include "../Common/MessageStruct.hpp"

#include "../Common/Logger.hpp"

namespace app { namespace objects {

  PlayerOnline::PlayerOnline() :
    Player()
    , m_udpSocket("0.0.0.0", 0)
    , m_udpServerEndpoint(
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
      [](const std::error_code &, const std::size_t &){}
      );

  }

  void PlayerOnline::update(const float dt)
  {
    Player::update(dt);
  }

  void PlayerOnline::onSetMove()
  {
    char cmd = static_cast<char>(common::MessageType::SET_MOVE);

    std::string msg = std::string(sizeof(cmd), cmd)
      + std::to_string(m_cursor.x)
      + ":"
      + std::to_string(m_cursor.y)
      ;

    m_udpSocket.send(
      msg, m_udpServerEndpoint,
      [this](const std::error_code &, const std::size_t &){
        this->receive();
      }
      );


    return;

    common::GameBoard gb = m_pScene->getGameBoard();

    this->m_isTurn = false;

    gb.getBoard()[m_cursor.x][m_cursor.y] = this->m_mark;

    m_pScene->setGameBoard(gb);

    m_pScene->checkFinish();

    m_pScene->setNextPlayer(m_pScene->getCurrentPlayer() + 1);
  }

  void PlayerOnline::receive()
  {
    // common::net::socket::Udp::EndPoint endp;
    std::string s;
    // m_udpSocket.sync_recv(s, endp);
    // this->onReceiveHandle(s);
    std::cin >> s;

    // m_udpSocket.receive(
    //   m_buffers, endp,
    //   [this](const std::error_code &e, const std::size_t &bytes)
    //   {
    //     std::string s;
    //     std::cin >> s;
    //     if (e)
    //     {
    //       Log::error(e.message());
    //     }
    //     else
    //     {
    //       std::string recv = std::string(m_buffers.data(), m_buffers.data() + bytes);
    //
    //       this->onReceiveHandle(recv);
    //     }
    //     this->receive();
    //   }
    //   );
  }

  void PlayerOnline::onReceiveHandle(const std::string &data)
  {
    try
    {
      Log::info("Server :: onReceiveHandle() :: NOTHING");

      common::MessageStruct ms(data);

      if (ms.isValidSum() == false)
      {
        return;
      }

      std::string s;
      std::cin >> s;

      switch (ms.msgType)
      {
        case common::MessageType::UPDATE_GAME:
          {
            m_pScene->getGameBoard().setBoard(ms.msg);
          }
          break;
        default:
          {
            Log::info("Server :: onReceiveHandle() :: NOTHING");
          }
          break;
      }
    }
    catch (...)
    {
      Log::error("Server :: onReceiveHandle() :: ERROR");
    }
  }

} }
