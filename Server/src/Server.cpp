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
    auto update = [&](float dt) {

    };

    auto sendToAllClients = [&](
      const int &seqNo, const Client &turnOfcli, const std::string &data
      )
    {

    };

    int seqNo = 0;
    while (true)
    {
      update(1.f);
      Client cli;
      sendToAllClients(seqNo, cli, "");
    }

    this->receive();

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

  void Server::receive()
  {
    m_udpSocket.receive(
      m_buffers,
      m_currentClient.second,
      [this](
        const std::error_code &e,
        const std::size_t
        &bytes
        )
      {
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

          auto from_client = getOrCreateClientId(m_currentClient.second);

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

          auto from_client = getOrCreateClientId(m_currentClient.second);

          Log::info("X:" + xy.at(0) + " - Y:" + xy.at(1));

          m_udpSocket.send(
            "FFF",
            m_currentClient.second,
            [](const std::error_code &e, const std::size_t &bytes){

            }
            );

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
    for (const auto &client : m_clients)
    {
      if (client.second == endpoint)
      {
        return client.first;
      }
    }

    auto id = (*m_clients.cend()).first + 1;
    m_clients.insert(Client(id, endpoint));

    return id;
  }

}
