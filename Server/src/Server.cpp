#include "app/Server.hpp"

namespace app {

  Server::Server(asio::io_service &s) :
    m_acceptor(s, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8889))
    , m_socket(s)
  {
  }

  Server::~Server()
  {
  }

  void Server::init()
  {
    std::cout << "Server initialized" << std::endl;
  }

  void Server::accept()
  {
    m_acceptor.async_accept(m_socket, std::bind(&Server::onAcceptConnection, this,
                                                std::placeholders::_1));
  }

  void Server::onAcceptConnection(const std::error_code &e)
  {
    std::cout << "Connected" << std::endl;
  }

}
