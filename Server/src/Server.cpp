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
    m_acceptor.async_accept(
      m_socket, std::bind(
        &Server::onAcceptConnection,
        this,
        std::placeholders::_1
        )
      );
  }

  void Server::onAcceptConnection(const std::error_code &e)
  {
    if (e)
    {
      std::cerr << "Error: " << e.message() << std::endl;
    }
    else
    {
      this->readHeader();
    }

    // Reset accept new client
    this->accept();
  }

  void Server::readHeader()
  {
    const std::size_t m_header = 4;
    asio::async_read(
      m_socket,
      asio::buffer(m_buffer, m_header),
      std::bind(
        &Server::onReadHeader,
        this,
        std::placeholders::_1,
        std::placeholders::_2
        )
      );
  }

  void Server::onReadHeader(const std::error_code &e, const std::size_t &bytes)
  {
    if (e)
    {
      std::cerr << "Error: " << e.message() << std::endl;
    }
    else
    {
      std::cout << "Size: " << bytes << std::endl;
      std::cout << "Buffer: " << m_buffer << std::endl;
    }
  }

}
