#ifndef APP_ROOM_HPP
#define APP_ROOM_HPP
#include <set>

#include "Type.hpp"
#include "../Common/Type.hpp"

namespace app {

  class Room
  {
    public:
      struct Player
      {
        Client client;

        std::string userName;
        // std::string password;

        common::PlayerMark mark;
      };

    public:
      Room(const int id);

    private:
      std::set<Player> m_players;

  };

}

#endif
