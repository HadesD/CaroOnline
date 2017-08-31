#ifndef APP_PLAYER_HPP
#define APP_PLAYER_HPP
#include <iostream>
#include <memory>

#include "app/scenes/PlayScene.hpp"

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
      void setScene(std::shared_ptr<scenes::PlayScene> scene);
      int getMark() const;
      void setMark(const int &mark);
      void setIsTurn(const bool &isTurn);
      bool getIsTurn() const;
      Point2D getCursor() const;
      void setCursor(const Point2D &c);
      int getKeyPushed() const;
      void setKeyPushed(const int &key);

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
      std::shared_ptr<scenes::PlayScene> m_pScene;
      int m_keyPushed;

  };

}

#endif
