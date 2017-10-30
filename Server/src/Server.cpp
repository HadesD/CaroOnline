#include "app/Server.hpp"

#include "../Common/Util.hpp"
#include "../Common/MessageStruct.hpp"
#include "../Common/Logger.hpp"

namespace app {

  Server::Server(const std::string &ip, const short &port) :
    m_udpSocket(ip, port),
    m_turn(-1)
  {
    this->m_gameBoard = common::GameBoard(
      common::config::gameBoardRows,
      common::config::gameBoardCols
      );

    m_seqNo = 0;
  }

  Server::~Server()
  {
    if (m_serviceThread.joinable())
    {
      m_serviceThread.join();
    }
  }

  void Server::init()
  {
    Log::info("Server :: init()");
  }

  void Server::run()
  {
    this->init();

    Log::info("Server :: run()");

    // http://giderosmobile.com/forum/discussion/2766/online-multiplayer-turn-based-game-with-udp/p1
    m_serviceThread = std::thread(&Server::run_service, this);
  }

  void Server::run_service()
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

  void Server::sendGameDataToAllClients()
  {
    try
    {
      if (m_clients.size() <= 0)
      {
        return;
      }

      Log::info("Turn of: " + std::to_string(m_turn));
      Log::info("Sequence: " + std::to_string(m_seqNo));
      Log::info("Start send to " + std::to_string(m_clients.size()) + " clients");

      char cmd = static_cast<char>(common::MessageType::UPDATE_GAME);

      std::string msg = std::string(sizeof(cmd), cmd)
        + std::to_string(m_seqNo) + "|"
        + std::to_string(m_turn) + "|"
        + m_gameBoard.toString()
        ;

      for (const auto &client : m_clients)
      {
        m_udpSocket.send(
          msg, client.second,
          [&](const std::error_code &e, const std::size_t &bytes){
            if (e)
            {
              Log::error(e.message());
            }
            else
            {
              Log::info(
                "Send to ID: "
                + std::to_string(client.first)
                + " " + std::to_string(bytes)
                +" Bytes"
                );
            }
          }
          );
      }
    }
    catch (...)
    {
      Log::error("Server :: sendGameDataToAllClients() :: Error");
    }
  }

  Server::GameBoard Server::getGameBoard() const
  {
    return this->m_gameBoard;
  }

  void Server::receive()
  {
    m_udpSocket.receive(
      m_buffers,
      m_workingClient.second,
      [this](const std::error_code &e, const std::size_t &bytes){
        if (e)
        {
          Log::error(e.message());
        }
        else
        {
          std::string data(
            this->m_buffers.data(),
            this->m_buffers.data() + bytes
            );

          this->onReceiveHandle(data);

          Log::info(
            data
            + " From: "
            + this->m_workingClient.second.address().to_string()
            + ":"
            + std::to_string(this->m_workingClient.second.port())
            );
        }
        this->receive();
      }
      );

    this->sendGameDataToAllClients();
  }

  void Server::onReceiveHandle(const std::string &data)
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
            Log::info("Server :: onReceiveHandle() :: LOGIN");
            std::vector<std::string> acc = Util::str_split(ms.msg, ':');

            if (acc.size() != 2)
            {
              return;
            }

            Log::info("Username:" + acc.at(0) + " - Pass:" + acc.at(1));

            auto from_client = this->getOrCreateClientIndex(
              m_workingClient.second
              );

            char cmd = static_cast<char>(common::MessageType::LOGIN);

            std::string msg = std::string(sizeof(cmd), cmd)
              + std::to_string(from_client)
              ;

            m_udpSocket.send(
              msg, m_workingClient.second,
              [=](const std::error_code &e, const std::size_t &/* bytes */){
                if (e)
                {
                  Log::error(e.message());
                }
                else
                {
                  Log::info(
                    "Send ID to: "
                    + std::to_string(from_client)
                    );
                }
              }
              );

            if (m_clients.size() == 1)
            {
              m_turn = from_client;
            }
            m_seqNo++;

          }
          break;
        case common::MessageType::QUIT_GAME:
          {
            Log::info("Server :: onReceiveHandle() :: QUIT_GAME");

            this->m_gameBoard = common::GameBoard(
              common::config::gameBoardRows,
              common::config::gameBoardCols
              );

            this->removeClient(this->getClientIndex(m_workingClient.second));

            m_clients.clear();

            m_seqNo = 0;
          }
          break;
        case common::MessageType::SET_MOVE:
          {
            Log::info("Server :: onReceiveHandle() :: SET_MOVE");

            if (m_clients.size() < 2)
            {
              return;
            }

            auto senderIndex = this->getClientIndex(m_workingClient.second);
            if (senderIndex != m_turn)
            {
              Log::error("Server :: onReceiveHandle() :: ERROR TURN");
              return;
            }

            std::vector<std::string> xy = Util::str_split(ms.msg, ':');

            if (xy.size() != 2)
            {
              return;
            }

            if (auto cliId = this->getClientIndex(this->m_workingClient.second))
            {
              auto x = std::stoi(xy.at(0));
              auto y = std::stoi(xy.at(1));

              if (m_gameBoard.getBoard().at(x).at(y) != 0)
              {
                Log::error(
                  "Had value at x,y:"
                  + std::to_string(x)
                  + ","
                  + std::to_string(y)
                  );

                return;
              }

              Log::info("X:" + std::to_string(x) + " - Y:" + std::to_string(y));

              common::GameBoard::Board board = this->m_gameBoard.getBoard();
              board[x][y] = cliId;

              this->m_gameBoard.setBoard(board);

              m_seqNo++;

              if (m_gameBoard.isWinPoint(common::Point2D(x,y), m_turn))
              {
                this->m_gameBoard = common::GameBoard(
                  common::config::gameBoardRows,
                  common::config::gameBoardCols
                  );
                m_seqNo = 0;
                m_clients.clear();
              }

              if ((++m_turn) > 2 /* m_clients.size() */)
              {
                m_turn = m_clients.cbegin()->first;
              }
            }
          }
          break;
        default:
          {
            Log::info("Server :: onReceiveHandle() :: NOTHING");
          }
          return;
      }
    }
    catch (...)
    {
      Log::error("Server :: onReceiveHandle() :: ERROR");
    }
  }

  Server::Client::first_type Server::getOrCreateClientIndex(
    const ListClient::mapped_type &endpoint
    )
  {
    if (auto id = this->getClientIndex(endpoint))
    {
      return id;
    }

    auto id = this->m_clients.cend()->first + 1;
    m_clients.insert(Client(id, endpoint));

    return id;
  }

  Server::Client::first_type Server::getClientIndex(
    const Client::second_type &endpoint
    ) const
  {
    for (const auto &client : this->m_clients)
    {
      if (client.second == endpoint)
      {
        return client.first;
      }
    }

    return 0;
  }

  bool Server::removeClient(
    const Client::first_type id
    )
  {
    if (m_turn == id)
    {
      m_turn = -1;
    }
    this->m_clients.erase(id);

    return true;
  }

}
