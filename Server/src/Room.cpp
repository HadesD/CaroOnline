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
        case common::MessageType::QUIT_GAME:
          {
            Log::info("Room :: onReceiveHandle() :: QUIT_GAME");

            std::size_t pIndex = this->getPlayer(cli);
            auto player = m_playerList.at(pIndex);

            int id = player->mark;

            if ((id > 0) && id <= 2)
            {
              this->onGameOver();
            }
            else
            {
              this->removePlayer(pIndex);
            }
          }
          break;
        case common::MessageType::SET_MOVE:
          {
            Log::info("Room :: onReceiveHandle() :: SET_MOVE");

            if (m_playerList.size() < 2)
            {
              return;
            }

            std::size_t pIndex = this->getPlayer(cli);

            if ((pIndex != m_turn) || (pIndex == m_playerList.size()))
            {
              Log::error("Room :: onReceiveHandle() :: ERROR TURN");
              return;
            }

            std::vector<std::string> xy = Util::split(ms.msg, ':');

            if (xy.size() != 2)
            {
              return;
            }

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
              board[x][y] = m_playerList.at(pIndex)->mark;

              this->m_gameBoard.setBoard(board);

              m_seqNo++;

              if (m_gameBoard.isWinPoint(common::Point2D(x,y), m_turn))
              {
                m_isGameOver = true;
              }
              else
              {
                if ((++m_turn) > 2 /* m_clients.size() */)
                {
                  m_turn = m_playerList.cbegin()->get()->mark;
                }
              }
            }
          }
          break;
        default:
          {
            Log::info("Room :: onReceiveHandle() :: NOTHING");
          }
          break;
      }
    }
    catch (...)
    {
      Log::error("Room :: onReceiveHandle() :: ERROR");
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
        + std::to_string(m_turn + 1) + "|"
        + std::to_string(m_playerList.size()) + "|"
        + m_gameBoard.toString()
        ;

      for (const auto &player : m_playerList)
      {
        m_pServer->send(player->client, common::MessageStruct(msg));
      }

      if (m_isGameOver)
      {
        this->onGameOver();
      }

    }
    catch (...)
    {
      Log::error("Room :: sendGameDataToAllClients() :: Error");
    }
  }

  Room::GameBoard Room::getGameBoard() const
  {
    return this->m_gameBoard;
  }

  void Room::onGameOver()
  {
    // m_turn = 0;
    // m_seqNo = 0;
    // m_isGameOver = false;

    if (m_playerList.size() < 2)
    {
      return;
    }

    char cmd = static_cast<char>(common::MessageType::GAME_OVER);

    std::string msg = std::string(sizeof(cmd), cmd) + std::to_string(m_turn);

    for (const auto &c : m_playerList)
    {
      m_pServer->send(c->client, msg);
    }

    // Reset game
    // m_turn = 0;
    // m_seqNo = 0;
    // m_playerList.clear();
    // m_gameBoard = common::GameBoard();

    m_playerList.clear();

    m_pServer->removeRoom(this->shared_from_this());
  }

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
        "Player Name",
        m_playerList.size() + 1
        );

    m_playerList.emplace_back(p);

    Log::info(
      "Room "
      + std::to_string(m_id)
      + " has " + std::to_string(m_playerList.size()) + " players"
      );

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

  void Room::setTurn(const std::size_t turn)
  {
    m_turn = turn;
  }

  std::size_t Room::getTurn() const
  {
    return m_turn;
  }

  void Room::setSeqNo(const int seqNo)
  {
    m_seqNo = seqNo;
  }

  int Room::getSeqNo() const
  {
    return m_seqNo;
  }

  void Room::onPlayerLogin(const Client &cli, const common::MessageStruct &ms)
  {
    Log::info("Room :: onPlayerLogin()");

    common::MessageStruct recv(ms);

    if (!recv.isValidSum())
    {
      return;
    }

    std::vector<std::string> acc = Util::split(recv.msg, ':');

    if (acc.size() != 2)
    {
      Log::error("Account invalid");
      return;
    }

    Log::info("Username:" + acc.at(0) + " - Pass:" + acc.at(1));

    std::size_t from_player = this->getOrCreatePlayer(cli);
    if (from_player == m_playerList.size())
    {
      Log::error("Error add Player");
    }

    char cmd = static_cast<char>(common::MessageType::LOGIN);

    std::string msg = std::string(sizeof(cmd), cmd)
      + std::to_string(from_player)
      + "|"
      + std::to_string(this->getPlayerList().at(from_player)->mark)
      ;

    m_pServer->send(cli, msg);

    m_seqNo++;

    if (this->getPlayerList().size() == 1)
    {
      m_turn = from_player;
    }
  }

  int Room::getId() const
  {
    return m_id;
  }

  void Room::setId(const int id)
  {
    this->m_id = id;
  }

}
