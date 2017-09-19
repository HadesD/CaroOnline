#include "app/Server.hpp"

#include "../Common/net/Connection.hpp"
#include "../Common/Logger.hpp"

namespace app {

  Server::Server(asio::io_service &s, const short &port) :
    m_pIoService(s)
  {
    m_pConnection = std::make_shared<common::net::Connection>(
      m_pIoService,
      port
      );
  }

  Server::~Server()
  {
  }

  void Server::init()
  {
    Log::info("Server Init");
  }

  void Server::run()
  {
    this->init();

    try
    {
      Log::info("Server runing");
      m_pConnection->receive();
    }
    catch (const std::exception &e)
    {
      std::cerr << "Exeption: " << e.what() << std::endl;
    }
  }

}
