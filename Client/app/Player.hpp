#ifndef APP_PLAYER_HPP
#define APP_PLAYER_HPP
#include <iostream>
#include <memory>

#include "app/scenes/PlayScene.hpp"

#include "app/input/Kbhit.h"

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
      // [[deprecated("Not compatible with smart pointer")]]
      void setScene(scenes::PlayScene *scene);
      void setScene(std::shared_ptr<scenes::PlayScene> scene);
      int getMark() const;
      void setMark(const int &mark);
      void setIsTurn(const bool &isTurn);
      bool getIsTurn() const;
      Point2D getCursor() const;
      void setCursor(const Point2D &c);

    public:
      void waitKeyboardEvent();
      void onKeyboardEvent();

    protected:
      int id;
      std::string name;
      bool isTurn;
      int mark;

    protected:
      Point2D m_cursor;
      // std::shared_ptr<scenes::PlayScene> m_pScene;
      std::shared_ptr<scenes::PlayScene> m_pScene;
      app::input::Kbhit m_kbhit;

  };

}

#endif
