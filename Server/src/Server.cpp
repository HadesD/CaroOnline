#include "app/Server.hpp"

#include "../Common/net/Socket.hpp"
#include "../Common/Logger.hpp"

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
    Log->info("Server Init");
  }

  void Server::accept()
  {
    m_pSocket = std::make_shared<common::net::Socket>(m_pIoService);

    m_acceptor.async_accept(
      m_pSocket->getSocket(), std::bind(
        &Server::onAcceptConnection,
        this,
        std::placeholders::_1
        )
      );
  }

  void Server::onAcceptConnection(
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
        m_pSocket->getSocket(),
        asio::buffer(m_buffer, m_bytes),
        std::bind(
          &Server::onReadHeader,
          this,
          std::placeholders::_1,
          std::placeholders::_2
          )
        );
    }

    // Reset accept new client
    this->accept();
  }

  void Server::onReadHeader(
    const std::error_code &e, const std::size_t &bytes
    )
  {
    if (e)
    {
      std::cerr << "Error: " << e.message() << std::endl;
    }
    else
    {
      std::string m = "Size: " + std::to_string(bytes) + " Buffer: " + m_buffer;
      Log->info(m);

      // Do Response
      asio::async_write(
        m_pSocket->getSocket(),
        asio::buffer("HEHEHE", 4),
        std::bind(
          &Server::onResponse,
          this,
          std::placeholders::_1,
          std::placeholders::_2
          )
        );

    }
  }

  void Server::onResponse(
    const std::error_code &e,
    const std::size_t &bytes
    )
  {
    if (e)
    {
      std::cerr << "Error: " << e.message() << std::endl;
    }
    else
    {
      Log->info("Responsed" + std::to_string(bytes));
    }
  }

}
