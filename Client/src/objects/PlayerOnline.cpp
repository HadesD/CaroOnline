#include "app/objects/PlayerOnline.hpp"

#include "app/Config.hpp"

namespace app { namespace objects {

  PlayerOnline::PlayerOnline() :
    Player()
    , m_udpSocket("0.0.0.0", 0)
    , m_udpServerEndpoint(
      asio::ip::address::from_string(app::config::serverIp),
        app::config::serverPort
      )
  {
    m_udpSocket.send(
      "FFF", m_udpServerEndpoint,
      [](const std::error_code &, const std::size_t &){}
      );
  }

  void PlayerOnline::update(const float &dt)
  {
    Player::update(dt);

  }

} }
