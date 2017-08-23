#ifndef APP_PLAYER_HPP
#define APP_PLAYER_HPP
#include <iostream>
#include <memory>

#include "app/Game.hpp"

namespace app {

  class Player : public std::enable_shared_from_this<Player>
  {
    public:
      Player();
      ~Player();

    public:
      void setId(const int &id);
      int getId() const;
      void setName(const std::string &name);
      std::string getName() const;
      void setGame(std::shared_ptr<Game> game);

      void onKeyboardEvent();

    protected:
      int m_id;
      std::string m_name;
      bool m_isTurn;
      Game::Cursor m_cursor;
      std::shared_ptr<Game> p_game;

  };

}

#endif
