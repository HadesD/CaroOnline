#include <iostream>

#include "Connection.hpp"

#include "../Logger.hpp"

namespace common { namespace net {

  Connection::Connection(asio::io_service &s, const short &port) :
    m_socket(s, Endpoint(Connection::Protocol::v4(), port))
  {
  }

  Connection::~Connection()
  {
    std::cout << "Disconnected" << std::endl;
  }

  void Connection::receive()
  {
    Log->info("Start receive");

    m_socket.async_receive_from(
      asio::buffer(m_buffer), m_endpoint,
      std::bind(
        &Connection::onReceive, this,
        std::placeholders::_1,
        std::placeholders::_2
        )
      );
  }

  void Connection::onReceive(const std::error_code &e, const std::size_t &bytes)
  {
    Log->info("onReceived");

    if (e)
    {
      throw std::runtime_error(e.message());
    }
    else
    {
      Log->info("Received: " + std::to_string(bytes));
    }

    this->receive();
  }

  void Connection::send(const ResponseStruct &res)
  {
    Log->info("Start send");
  }

  Connection::Socket &Connection::getSocket()
  {
    return m_socket;
  }

} }
