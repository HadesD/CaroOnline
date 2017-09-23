#ifndef APP_OBJECTS_PLAYER_HPP
#define APP_OBJECTS_PLAYER_HPP
#include <iostream>
#include <memory>

#include "app/scenes/PlayScene.hpp"

#include "app/input/Kbhit.hpp"
#include "../Common/net/socket/Udp.hpp"

namespace app { namespace objects {

  class Player
  {
    public:
      Player();
      ~Player();

    public:
      virtual void update(const float &/* dt */);

    private:
      void waitKeyboardEvent();
      void onKeyboardEvent();

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
      void onConnect(const std::error_code &e);

    protected:
      int m_id;
      std::string m_name;
      bool m_isTurn;
      int m_mark;
      bool m_isReady;

    protected:
      Point2D m_cursor;
      std::shared_ptr<scenes::PlayScene> m_pScene;
      app::input::Kbhit m_kbhit;

  };

} }

#endif
