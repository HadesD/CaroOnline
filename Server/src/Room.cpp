#include "app/Room.hpp"
#include "app/Server.hpp"

#include "../Common/Logger.hpp"
#include "../Common/Util.hpp"
#include "../Common/MessageStruct.hpp"

namespace app {

  Room::Room(Server *sv) :
    m_pServer(sv)
  {
    m_turn = 0;
    this->m_gameBoard = common::GameBoard(
      common::config::gameBoardRows,
      common::config::gameBoardCols
      );
    m_seqNo = 0;
    m_isGameOver = false;
  }

  // Room::Room(const std::shared_ptr<Server> &sv) :
  //   m_pServer(sv)
  // {
  //   m_turn = 0;
  //   this->m_gameBoard = common::GameBoard(
  //     common::config::gameBoardRows,
  //     common::config::gameBoardCols
  //     );
  //   m_seqNo = 0;
  //   m_isGameOver = false;
  // }

  Room::~Room()
  {
  }

  void Room::onReceiveHandle(const Client &cli, const std::string &data)
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
            std::vector<std::string> acc = Util::split(ms.msg, ':');

            if (acc.size() != 2)
            {
              return;
            }

            Log::info("Username:" + acc.at(0) + " - Pass:" + acc.at(1));

            auto from_player = this->getOrCreatePlayer(cli);
            char cmd = static_cast<char>(common::MessageType::LOGIN);

            std::string msg = std::string(sizeof(cmd), cmd)
              + std::to_string(from_player)
              ;

            m_pServer->send(cli, msg);

            m_seqNo++;

            if (m_playerList.size() == 1)
            {
              m_turn = from_player;
            }
          }
          break;
        case common::MessageType::QUIT_GAME:
          {
            Log::info("Server :: onReceiveHandle() :: QUIT_GAME");

            std::size_t pid = this->getPlayer(cli);
            auto player = m_playerList.at(pid);

            int id = player->mark;

            if ((id > 0) && id <= 2)
            {
              this->onGameOver();
            }
            else
            {
              this->removePlayer(pid);
            }
          }
          break;
        case common::MessageType::SET_MOVE:
          {
            Log::info("Server :: onReceiveHandle() :: SET_MOVE");

            if (m_playerList.size() < 2)
            {
              return;
            }

            std::size_t pid = this->getPlayer(cli);

            // auto senderIndex = this->getClientIndex(m_workingClient.second);
            // if ((senderIndex != m_turn) || (senderIndex == 0))
            // {
            //   Log::error("Server :: onReceiveHandle() :: ERROR TURN");
            //   return;
            // }
            //
            // std::vector<std::string> xy = Util::split(ms.msg, ':');
            //
            // if (xy.size() != 2)
            // {
            //   return;
            // }
            //
            // {
            //   auto x = std::stoi(xy.at(0));
            //   auto y = std::stoi(xy.at(1));
            //
            //   if (m_gameBoard.getBoard().at(x).at(y) != 0)
            //   {
            //     Log::error(
            //       "Had value at x,y:"
            //       + std::to_string(x)
            //       + ","
            //       + std::to_string(y)
            //       );
            //
            //     return;
            //   }
            //
            //   Log::info("X:" + std::to_string(x) + " - Y:" + std::to_string(y));
            //
            //   common::GameBoard::Board board = this->m_gameBoard.getBoard();
            //   board[x][y] = senderIndex;
            //
            //   this->m_gameBoard.setBoard(board);
            //
            //   m_seqNo++;
            //
            //   if (m_gameBoard.isWinPoint(common::Point2D(x,y), m_turn))
            //   {
            //     m_isGameOver = true;
            //   }
            //   else
            //   {
            //     if ((++m_turn) > 2 #<{(| m_clients.size() |)}>#)
            //     {
            //       m_turn = m_clients.cbegin()->first;
            //     }
            //   }
            //
            // }
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

  void Room::sendGameDataToAllPlayers()
  {
    try
    {
      if (m_playerList.size() <= 0)
      {
        return;
      }

      Log::info("Turn of: " + std::to_string(m_turn));
      Log::info("Sequence: " + std::to_string(m_seqNo));
      Log::info("Start send to " + std::to_string(m_playerList.size()) + " clients");

      char cmd = static_cast<char>(common::MessageType::UPDATE_GAME);

      std::string msg = std::string(sizeof(cmd), cmd)
        + std::to_string(m_seqNo) + "|"
        + std::to_string(m_turn) + "|"
        + std::to_string(m_playerList.size()) + "|"
        + m_gameBoard.toString()
        ;

      for (const auto &player : m_playerList)
      {
        m_pServer->send(player->client, common::MessageStruct(msg));
        // m_udpSocket.send(
        //   msg, player,
        //   [&](const std::error_code &e, const std::size_t &bytes){
        //     if (e)
        //     {
        //       Log::error(e.message());
        //     }
        //     else
        //     {
        //       Log::info(
        //         "Send to Player: "
        //         + player->userName
        //         + " " + std::to_string(bytes)
        //         +" Bytes"
        //         );
        //     }
        //   }
        //   );
      }

      if (m_isGameOver)
      {
        this->onGameOver();
      }

    }
    catch (...)
    {
      Log::error("Server :: sendGameDataToAllClients() :: Error");
    }
  }

  Room::GameBoard Room::getGameBoard() const
  {
    return this->m_gameBoard;
  }

  void Room::onGameOver()
  {
    m_turn = 0;
    m_seqNo = 0;
    m_isGameOver = false;

    if (m_playerList.size() < 2)
    {
      return;
    }

    char cmd = static_cast<char>(common::MessageType::GAME_OVER);

    std::string msg = std::string(sizeof(cmd), cmd) + std::to_string(m_turn);

    for (const auto &c : m_playerList)
    {
      m_pServer->send(c->client, msg);
      // m_udpSocket.send(
      //   msg, c,
      //   [=](const std::error_code &e, const std::size_t &#<{(| bytes |)}>#){
      //     if (e)
      //     {
      //       Log::error(e.message());
      //     }
      //     else
      //     {
      //       Log::info("Sent GAME_OVER message to: " + c->userName);
      //     }
      //   }
      //   );
    }

    // Reset game
    m_turn = 0;
    m_seqNo = 0;
    m_playerList.clear();
    m_gameBoard = common::GameBoard();
  }

  // Client::first_type Room::getOrCreateClientIndex(
  //   const ListClient::mapped_type &endpoint
  //   )
  // {
  //   if (auto id = this->getClientIndex(endpoint))
  //   {
  //     return id;
  //   }
  //
  //   auto id = (--this->m_clients.cend())->first + 1;
  //   m_clients.insert(Client(id, endpoint));
  //
  //   return id;
  // }
  //
  // Client::first_type Server::getClientIndex(
  //   const Client::second_type &endpoint
  //   ) const
  // {
  //   for (const auto &client : this->m_clients)
  //   {
  //     if (client.second == endpoint)
  //     {
  //       return client.first;
  //     }
  //   }
  //
  //   return 0;
  // }

  std::vector< std::shared_ptr<Room::Player> > Room::getPlayerList() const
  {
    return m_playerList;
  }

  std::size_t Room::getOrCreatePlayer(const app::Client &client)
  {
    {
      std::size_t id = this->getPlayer(client);
      if (id != m_playerList.size())
      {
        return id;
      }
    }
    auto p = std::make_shared<Player>(
        client,
        "fsdfsdf",
        (m_playerList.size() > 0) ? (m_playerList.back()->mark + 1) : 1
        );

    m_playerList.emplace_back(p);

    return m_playerList.size() - 1;
  }

  std::size_t Room::getPlayer(const app::Client &client) const
  {
    std::size_t i = 0;

    for (const auto &c : m_playerList)
    {
      if (c->client == client)
      {
        return i;
      }
      i++;
    }
    return m_playerList.size();
  }

  void Room::removePlayer(const std::shared_ptr<Player> &player)
  {
  }

  void Room::removePlayer(const std::size_t player)
  {
    m_playerList.erase(m_playerList.cbegin() + player);
  }

}
