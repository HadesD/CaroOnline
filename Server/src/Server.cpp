#include "app/Server.hpp"
#include "../Common/net/Socket.hpp"

namespace app {

  Server::Server(asio::io_service &s) :
    m_pIoService(s)
    , m_acceptor(s, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8889))
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
    auto socket = std::make_shared<common::net::Socket>(m_pIoService);

    m_acceptor.async_accept(
      socket->getSocket(), std::bind(
        &Server::onAcceptConnection,
        this,
        socket->shared_from_this(),
        std::placeholders::_1
        )
      );
  }

  void Server::onAcceptConnection(
    const std::shared_ptr<common::net::Socket> &socket,
    const std::error_code &e
    )
  {
    if (e)
    {
      std::cerr << "Error: " << e.message() << std::endl;
    }
    else
    {
      const std::size_t m_bytes = 4;

      // Bind to Read
      asio::async_read(
        socket->getSocket(),
        asio::buffer(m_buffer, m_bytes),
        std::bind(
          &Server::onReadHeader,
          this,
          socket->shared_from_this(),
          std::placeholders::_1,
          std::placeholders::_2
          )
        );
    }

    // Reset accept new client
    this->accept();
  }

  void Server::onReadHeader(
    const std::shared_ptr<common::net::Socket> &socket,
    const std::error_code &e, const std::size_t &bytes
    )
  {
    if (e)
    {
      std::cerr << "Error: " << e.message() << std::endl;
    }
    else
    {
      std::cout << "Size: " << bytes << std::endl;
      std::cout << "Buffer: " << m_buffer << std::endl;

      // Do Response
      asio::async_write(
        socket->getSocket(),
        asio::buffer("HEHEHE", 4),
        std::bind(
          &Server::onResponse,
          this,
          socket->shared_from_this(),
          std::placeholders::_1,
          std::placeholders::_2
          )
        );

    }
  }

  void Server::onResponse(
    const std::shared_ptr<common::net::Socket> &/* socket */,
    const std::error_code &e, const std::size_t &bytes
    )
  {
    if (e)
    {
      std::cerr << "Error: " << e.message() << std::endl;
    }
    else
    {
      std::cout << "Responded: " << bytes << std::endl;
    }
  }

}
