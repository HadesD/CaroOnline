#include <algorithm>

#include "app/Server.hpp"
#include "app/Room.hpp"

#include "../Common/Util.hpp"
#include "../Common/MessageStruct.hpp"
#include "../Common/Logger.hpp"

namespace app {

  Server::Server(const std::string &ip, const int port) :
    m_udpSocket(ip, port)
  {
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

  void Server::receive()
  {
    m_udpSocket.receive(
      m_buffers,
      m_workingClient,
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
            + this->m_workingClient.address().to_string()
            + ":"
            + std::to_string(this->m_workingClient.port())
            );
        }
        this->receive();
      }
      );
  }

  void Server::send(const Client &cli, const common::MessageStruct &msg)
  {
    m_udpSocket.send(
      msg.data, cli,
      [](const std::error_code &, const std::size_t ){

      }
      );
  }

  void Server::onReceiveHandle(const std::string &data)
  {
    try
    {
      if (m_roomList.size() <= 0)
      {
        this->addRoom();
      }

      Log::info(
        "We have "
        + std::to_string(m_roomList.size())
        + " rooms now"
        );

      common::MessageStruct ms(data);

      if (ms.isValidSum() == false)
      {
        return;
      }

      bool processed_player = false;
      for (auto &room : m_roomList)
      {
        if (ms.msgType == common::MessageType::LOGIN)
        {
          if (room->getPlayer(m_workingClient) != room->getPlayerList().size())
          {
            room->removePlayer(room->getPlayer(m_workingClient));
          }
          if (room->getPlayerList().size() < 2)
          {
            room->onPlayerLogin(m_workingClient, ms);
            processed_player = true;
          }
        }
        else
        {
          if (room->getPlayer(m_workingClient) != room->getPlayerList().size())
          {
            room->onReceiveHandle(m_workingClient, data);
            room->sendGameDataToAllPlayers();
            return;
          }
        }
      }

      // On notfound
      if (!processed_player)
      {
        this->addRoom();
        m_roomList.back()->onPlayerLogin(m_workingClient, ms);
      }
    }
    catch(const std::exception &e)
    {
      Log::error(e.what());
    }
    catch(...)
    {
      Log::error("Somethings has been go away without ERROR CODE");
    }
  }

  void Server::removeRoom(const std::shared_ptr<Room> &r)
  {
    auto rIndex = std::find(m_roomList.cbegin(), m_roomList.cend(), r);
    if (rIndex != m_roomList.cend())
    {
      Log::info("Removing Room " + std::to_string(rIndex->get()->getId()));

      m_roomList.erase(rIndex);
    }
    else
    {
      Log::error("Not found Room to Delete");
    }
  }

  void Server::addRoom()
  {
    int lastId = 0;
    if (m_roomList.size())
    {
      lastId = m_roomList.back()->getId();
    }
    m_roomList.emplace_back(std::make_shared<Room>(this));
    m_roomList.back()->setId(lastId + 1);
  }

}
