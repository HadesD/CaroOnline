#include "app/Server.hpp"

#include "../Common/Util.hpp"
#include "../Common/MessageStruct.hpp"
#include "../Common/Logger.hpp"

namespace app {

  Server::Server(const std::string &ip, const short &port) :
    m_udpSocket(ip, port)
  {
  }

  Server::~Server()
  {
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
    m_seqNo = 0;

    try
    {
      auto tnow = std::chrono::steady_clock::now();

      this->receive();

      // while (true)
      {
        std::chrono::duration<float> dt = std::chrono::steady_clock::now() -
          tnow;

        // this->sendToAllClients("FFF");

        this->update(static_cast<float>(dt.count()));

        tnow = std::chrono::steady_clock::now();
      }

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

  void Server::update(const float dt)
  {
  }

  void Server::sendGameDataToAllClients()
  {
    Log::info("Start send to " + std::to_string(m_clients.size()) + " clients");



    std::string msg = "";

    for (const auto &client : m_clients)
    {
      m_udpSocket.send(
        msg, client.second,
        [&](const std::error_code &e, const std::size_t &bytes){
          Log::info("Send to ID: "
                    + std::to_string(client.first)
                    + " " + std::to_string(bytes)
                    +"Bytes"
                   );
        }
        );
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
      m_currentClient.second,
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
            + this->m_currentClient.second.address().to_string()
            + ":"
            + std::to_string(this->m_currentClient.second.port())
            );
        }
        this->receive();
      }
      );

    this->sendGameDataToAllClients();
  }

  void Server::onReceiveHandle(const std::string &data)
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

          auto from_client = this->getOrCreateClientId(m_currentClient.second);

        }
        break;
      case common::MessageType::SET_MOVE:
        {
          Log::info("Server :: onReceiveHandle() :: SET_MOVE");

          std::vector<std::string> xy = Util::str_split(ms.msg, ':');
          if (xy.size() != 2)
          {
            return;
          }

          if (auto cliId = this->getClientId(this->m_currentClient.second))
          {
            Log::info("X:" + xy.at(0) + " - Y:" + xy.at(1));
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

  Server::ListClient::key_type Server::getOrCreateClientId(
    const ListClient::mapped_type &endpoint
    )
  {
    if (auto id = this->getClientId(endpoint))
    {
      return id;
    }

    auto id = this->m_clients.cend()->first + 1;
    m_clients.insert(Client(id, endpoint));

    return id;
  }

  Server::ListClient::key_type Server::getClientId(
    const ListClient::mapped_type &endpoint
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

  bool Server::removeClientId(
    const ListClient::key_type id
    )
  {
    this->m_clients.erase(id);

    return true;
  }

}
