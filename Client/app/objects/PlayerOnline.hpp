#ifndef APP_OBJECTS_PLAYER_ONLINE_HPP
#define APP_OBJECTS_PLAYER_ONLINE_HPP

#include "Player.hpp"

namespace app { namespace objects {

  class PlayerOnline : public Player
  {
    public:
      PlayerOnline();

    public:
      virtual void update(const float &/* dt */);

    private:
      // Network socket
      common::net::socket::Udp m_udpSocket;
      std::string m_sendData;

      // Server
      common::net::socket::Udp::EndPoint m_udpServerEndpoint;

  };

} }

#endif
