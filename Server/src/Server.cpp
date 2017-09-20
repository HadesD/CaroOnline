#include "app/Server.hpp"

// #include "../Common/net/Connection.hpp"
#include "../Common/net/socket/Udp.hpp"
#include "../Common/Logger.hpp"

namespace app {

  Server::Server(const std::string &ip, const short &port)
  {
    m_pUdpSocket = std::make_shared<common::net::socket::Udp>(ip, port);
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

    while (m_pUdpSocket->isOpening() == true)
    {
      try
      {
        m_pUdpSocket->open();
      }
      catch (const std::exception &e)
      {
        Log::error(e.what());
      }
      catch (...)
      {

      }
    }
  }

  void Server::receive()
  {
    m_pUdpSocket->receive(
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

          Log::info(
            data
            + " From: "
            + this->m_currentClient.second.address().to_v4().to_string()
            + ":"
            + std::to_string(this->m_currentClient.second.port())
            );
        }

        this->receive();
      }
      );
  }

}
