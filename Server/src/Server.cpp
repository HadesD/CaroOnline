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
        m_roomList.emplace_back(std::make_shared<Room>(this));
      }

      Log::info(
        "We have "
        + std::to_string(m_roomList.size())
        + " rooms now"
        );

      for (auto &room : m_roomList)
      {
        room->onReceiveHandle(m_workingClient, data);
        return;
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

}
