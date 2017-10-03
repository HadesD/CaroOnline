#include "app/objects/PlayerOnline.hpp"

#include "app/Config.hpp"
#include "../Common/MessageStruct.hpp"

#include "../Common/Logger.hpp"

namespace app { namespace objects {

  PlayerOnline::PlayerOnline() :
    Player()
    , m_udpSocket("0.0.0.0", 0)
    , m_udpServerEndpoint(
      asio::ip::address::from_string(app::config::serverIp),
        app::config::serverPort
      )
  {
    char cmd = static_cast<char>(common::MessageType::LOGIN);

    std::string msg = std::string(1, cmd) + "FF";

    m_udpSocket.send(
      msg, m_udpServerEndpoint,
      [](const std::error_code &, const std::size_t &){}
      );

    this->receive();
  }

  void PlayerOnline::update(const float &dt)
  {
    Player::update(dt);
  }

  void PlayerOnline::receive()
  {
    m_udpSocket.receive(
      m_buffers, m_udpServerEndpoint,
      [this](const std::error_code &, const std::size_t &bytes)
      {
        Log::info(std::string(m_buffers.data(), m_buffers.data() + bytes));

        this->receive();
      }
      );
  }

} }
