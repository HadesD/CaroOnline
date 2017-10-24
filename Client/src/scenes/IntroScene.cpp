#include <iostream>

#include "app/scenes/IntroScene.hpp"

#include "app/core/Game.hpp"
#include "app/scenes/PlayScene.hpp"

namespace app { namespace scenes {

  IntroScene::IntroScene(const std::shared_ptr<app::core::Game> &game) :
    app::Scene(game)
  {
    m_cursor = 0;
  }

  IntroScene::~IntroScene()
  {
  }

  void IntroScene::init()
  {
    m_selection.emplace_back("Play Online",
                             std::bind(&IntroScene::goToPlayOnline, this)
                            );
    m_selection.emplace_back("Play With Computer",
                             std::bind(&IntroScene::goToPlayOffline, this)
                            );
    m_selection.emplace_back("Quit", std::bind(&IntroScene::quit, this));
  }

  void IntroScene::update(const float /* dt */)
  {
    this->waitKeyboardEvent();
  }

  void IntroScene::draw()
  {
    for (std::size_t i = 0; i < m_selection.size(); i++)
    {
      std::cout << "[" << ((m_cursor == i) ? "x" : " ") << "]" << " ";
      std::cout << m_selection.at(i).name << std::endl;
    }
  }

  void IntroScene::waitKeyboardEvent()
  {
    if (m_kbhit.kbhit())
    {
      this->onKeyboardEvent();
    }
  }

  void IntroScene::onKeyboardEvent()
  {
    switch(m_kbhit.getch())
    {
      case 'o':
      case 13:
        {
          m_selection.at(m_cursor).call();
        }
        break;
      case 'q':
        {
          this->quit();
        }
        break;
      case 'h':
        {
        }
        break;
      case 's':
      case 'B':
      case 'j':
        {
          if (m_cursor >= (m_selection.size() - 1))
          {
            return;
          }
          m_cursor++;
        }
        break;
      case 'w':
      case 'A':
      case 'k':
        {
          if (m_cursor <= 0)
          {
            return;
          }
          m_cursor--;
        }
        break;
      case 'l':
        {
        }
        break;
    }
  }

  void IntroScene::goToPlayOffline()
  {
    m_pGame->setScene(
      std::shared_ptr<app::scenes::PlayScene>(
        new app::scenes::PlayScene(m_pGame)
        )
      );
  }

  void IntroScene::goToPlayOnline()
  {
    // m_pGame->setScene(
    //   std::shared_ptr<app::scenes::PlayerOnlineScene>(
    //     new app::scenes::PlayScene(m_pGame)
    //     )
    //   );
  }

  void IntroScene::quit()
  {
    m_pGame->quit();
  }

} }
