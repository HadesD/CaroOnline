#include "app/Server.hpp"

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

    this->receive();

    while (m_udpSocket.isOpening() == true)
    {
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

          Log::info(std::to_string(getOrCreateClientId(m_currentClient.second)));
        }

        this->receive();
      }
      );
  }

  void Server::onReceiveHandle(const std::string &data)
  {
    // common::MessageStruct ms(data);
    m_udpSocket.send(
      "FFF",
      m_currentClient.second,
      [](const std::error_code &e, const std::size_t &bytes)
      {
        Log::info(std::to_string(bytes));
      }
      );

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
