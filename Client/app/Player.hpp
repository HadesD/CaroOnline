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
      int getMark() const;
      void setMark(const int &mark);

    public:
      void onKeyboardEvent();

    protected:
      int id;
      std::string name;
      bool isTurn;
      int mark;

    protected:
      Game::Cursor cursor;
      std::shared_ptr<Game> pGame;

  };

}

#endif
