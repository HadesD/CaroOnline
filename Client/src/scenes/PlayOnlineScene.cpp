#include "app/scenes/PlayOnlineScene.hpp"

#include "app/Config.hpp"
#include "app/objects/Player.hpp"
#include "app/core/Game.hpp"

#include "../Common/Logger.hpp"
#include "../Common/MessageStruct.hpp"
#include "../Common/Util.hpp"

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
      [](const std::error_code &, const std::size_t &){
      }
      );
    m_seqNo = 0;
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
    auto me = std::make_shared<app::objects::Player>(
      app::objects::Player::Type::SELF
      );
    this->addPlayer(me);

    m_serviceThread = std::thread(&PlayOnlineScene::run_service, this);
  }

  void PlayOnlineScene::draw()
  {
    PlayScene::draw();

    std::string pName = std::to_string(m_turn);
    if (m_turn == m_listPlayer.front()->getId())
    {
      pName = "You";
    }
    std::cout << "Current player: " << pName << std::endl;
    std::cout << "Sequence: " << m_seqNo << std::endl;
  }

  void PlayOnlineScene::receive()
  {
    m_udpSocket.receive(
      m_buffers, m_udpCurrentEndpoint,
      [this](const std::error_code &e, const std::size_t &bytes)
      {
        if (e)
        {
          Log::error(e.message());
        }
        else
        {
          // std::cout
          //   << m_udpCurrentEndpoint.address().to_string() << ":"
          //   << m_udpCurrentEndpoint.port();
          // std::string s;
          // if (
          //   (m_udpCurrentEndpoint.address() == m_udpServerEndpoint.address())
          //   &&
          //   (m_udpCurrentEndpoint.port() == m_udpServerEndpoint.port())
          //   )
          {
            std::string recv = std::string(m_buffers.data(), m_buffers.data() + bytes);
            Log::info(recv);
            this->onReceiveHandle(recv);
          }

        }
        this->receive();
      }
      );
  }

  void PlayOnlineScene::run_service()
  {
    try
    {
      this->receive();
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

  void PlayOnlineScene::onReceiveHandle(const std::string &data)
  {
    try
    {
      common::MessageStruct ms(data);

      if (ms.isValidSum() == false)
      {
        return;
      }

      switch (ms.msgType)
      {
        case common::MessageType::LOGIN:
          {
            Log::info("PlayOnlineScene :: onReceiveHandle() :: RECV_ID");
            auto id = std::stoi(ms.msg);
            if (id)
            {
              m_listPlayer.front()->setId(id);
              m_listPlayer.front()->setMark(id);
            }
            else
            {
              std::cout << "Error set ID" << std::endl;
              m_pGame->quit();
            }
          }
          break;
        case common::MessageType::UPDATE_GAME:
          {
            Log::info("PlayOnlineScene :: onReceiveHandle() :: SET_MOVE");

            std::vector<std::string> game_data = Util::str_split(ms.msg, '|');

            if (game_data.size() != 3)
            {
              return;
            }

            int seqNo = std::stoi(game_data.at(0));

            if (m_seqNo >= seqNo)
            {
              return;
            }

            std::vector<std::string> board = Util::str_split(game_data.at(2), ':');

            if (
              board.size() !=
              (common::config::gameBoardCols*common::config::gameBoardRows)
              )
            {
              return;
            }

            m_seqNo = seqNo;
            m_turn = std::stoi(game_data.at(1));

            this->m_gameBoard.setBoard(game_data.at(2));

            if (m_turn == m_listPlayer.front()->getId())
            {
              this->setNextPlayer(m_listPlayer.front());
            }
          }
          break;
        default:
          {
            Log::info("Server :: onReceiveHandle() :: NOTHING");
          }
          break;
      }
    }
    catch(...)
    {
      Log::error("PlayOnlineScene :: onReceiveHandle() :: ERROR");
    }
  }

  bool PlayOnlineScene::quit()
  {
    if (PlayScene::quit())
    {
      char cmd = static_cast<char>(common::MessageType::QUIT_GAME);

      std::string msg = std::string(sizeof(cmd), cmd);

      m_udpSocket.send(
        msg, m_udpServerEndpoint,
        [](const std::error_code &, const std::size_t &){
        }
        );
      return true;
    }

    return false;
  }

  void PlayOnlineScene::onSetGameBoardMove(const common::Point2D &p)
  {
    char cmd = static_cast<char>(common::MessageType::SET_MOVE);

    std::string msg = std::string(sizeof(cmd), cmd)
      + std::to_string(p.x)
      + ":"
      + std::to_string(p.y)
      ;

    m_udpSocket.send(
      msg, m_udpServerEndpoint,
      [](const std::error_code &, const std::size_t &){
      }
      );
  }

} }
