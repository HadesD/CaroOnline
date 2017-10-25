#ifndef APP_OBJECTS_PLAYER_HPP
#define APP_OBJECTS_PLAYER_HPP
#include <iostream>
#include <memory>

#include "app/scenes/PlayScene.hpp"

#include "app/input/Kbhit.hpp"

namespace app { namespace objects {

  class Player
  {
    public:
      enum class Type
      {
        SELF,
        COMPUTER,
        PARTNER,
      };

    public:
      Player(const Type type);
      ~Player();

    public:
      virtual void update(const float /* dt */);

    private:
      void waitKeyboardEvent();
      void onKeyboardEvent();

    public:
      void setId(const int id);
      int getId() const;
      void setName(const std::string &name);
      std::string getName() const;
      // [[deprecated("Not compatible with smart pointer")]]
      void setScene(scenes::PlayScene *scene);
      void setScene(std::shared_ptr<scenes::PlayScene> scene);
      common::PlayerMark getMark() const;
      void setMark(const int mark);
      void setIsTurn(const bool isTurn);
      bool getIsTurn() const;
      common::Point2D getCursor() const;
      void setCursor(const common::Point2D &c);
      void onConnect(const std::error_code &e);
      Type getType() const;

    protected:
      virtual void onSetMove();

    protected:
      int m_id;
      std::string m_name;
      bool m_isTurn;
      common::PlayerMark m_mark;
      bool m_isReady;
      Type m_type;

    protected:
      common::Point2D m_cursor;
      std::shared_ptr<scenes::PlayScene> m_pScene;
      app::input::Kbhit m_kbhit;

  };

} }

#endif
