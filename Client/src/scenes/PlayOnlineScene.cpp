#include "app/scenes/PlayOnlineScene.hpp"

#include "app/Config.hpp"
#include "app/objects/Player.hpp"
#include "app/core/Game.hpp"

#include "../Common/Logger.hpp"
#include "../Common/MessageStruct.hpp"
#include "../Common/Util.hpp"

namespace app { namespace scenes {

  PlayOnlineScene::PlayOnlineScene(
    std::shared_ptr<app::core::Game> game
    ) : PlayScene(game),
  m_udpSocket("0.0.0.0", 0)
  {
    // Server resolver
    m_udpServerEndpoint = m_udpSocket.resolver(
      common::config::serverAddr,
      common::config::serverPort
      );


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
    m_peopleCount = 0;
    m_isGameOver = false;
    auto me = std::make_shared<app::objects::Player>(
      app::objects::Player::Type::SELF
      );
    this->addPlayer(me);

    m_serviceThread = std::thread(&PlayOnlineScene::run_service, this);
  }

  void PlayOnlineScene::update(const float dt)
  {
    PlayScene::update(dt);

    while (m_taskQueue.size())
    {
      auto do_task = m_taskQueue.front();
      do_task();
      m_taskQueue.pop();
    }
  }

  void PlayOnlineScene::draw()
  {
    PlayScene::draw();

    std::string pName = std::to_string(m_turn);
    if (m_listPlayer.front()->getIsTurn())
    {
      pName = "You";
    }
    else
    {
      pName = "Player " + pName;
    }
    std::cout << "Turn: " << pName << std::endl;
    std::cout << "Sequence: " << m_seqNo << std::endl;

    if (m_isGameOver)
    {
      std::cout << "Found winner: " << pName << std::endl;
      std::cout << "Press [q] to quit game" << std::endl;
    }
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
            Log::info("Player ID: "
                      + std::to_string(m_listPlayer.front()->getId())
                      + " :: receive :: started"
                     );
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
      Log::info("Current Seq: " + std::to_string(m_seqNo));

      if (ms.isValidSum() == false)
      {
        return;
      }

      switch (ms.msgType)
      {
        case common::MessageType::LOGIN:
          {
            Log::info("PlayOnlineScene :: onReceiveHandle() :: RECV_ID");
            std::vector< std::string > recv = Util::split(ms.msg, '|');
            if (recv.size() != 2)
            {
              Log::error("Error size when login");
              m_pGame->quit();
              return;
            }

            m_listPlayer.front()->setId(std::stoi(recv.at(0)));
            m_listPlayer.front()->setMark(std::stoi(recv.at(1)));
          }
          break;
        case common::MessageType::UPDATE_GAME:
          {
            Log::info("PlayOnlineScene :: onReceiveHandle() :: UPDATE_GAME");

            std::vector<std::string> game_data = Util::split(ms.msg, '|');

            Log::info("game_data size: " + std::to_string(game_data.size()));

            if (game_data.size() != 4)
            {
              return;
            }

            int seqNo = std::stoi(game_data.at(0));

            Log::info("Received Seq: " + std::to_string(seqNo));

            if (m_seqNo >= seqNo)
            {
              return;
            }

            m_seqNo = seqNo;

            std::vector<std::string> board = Util::split(game_data.at(3), ':');

            if (
              board.size() !=
              (common::config::gameBoardCols*common::config::gameBoardRows)
              )
            {
              return;
            }

            Log::info("Current Turn: " + std::to_string(m_turn));
            m_turn = std::stoi(game_data.at(1));

            Log::info("Received turn: " + std::to_string(m_turn));

            this->m_gameBoard.setBoard(game_data.at(3));

            this->setNextPlayer(m_turn);

            m_peopleCount = std::stoi(game_data.at(2));
          }
          break;
        case common::MessageType::GAME_OVER:
          {
            Log::info("Server :: onReceiveHandle() :: GAME_OVER");
            m_isGameOver = true;
            m_peopleCount = 0;
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
    if (m_peopleCount < 2)
    {
      return;
    }

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
