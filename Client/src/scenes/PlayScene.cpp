#include <iostream>
#include <cassert>

#include "app/scenes/PlayScene.hpp"
#include "app/scenes/IntroScene.hpp"

#include "app/core/Game.hpp"
#include "app/Config.hpp"
#include "app/objects/Player.hpp"
#include "app/objects/PlayerOnline.hpp"
#include "../Common/Config.hpp"

namespace app { namespace scenes {

  PlayScene::PlayScene(const std::shared_ptr<app::core::Game> &game) :
    app::Scene(game)
  {
    m_gameBoard = common::GameBoard(
      common::config::gameBoardRows,
      common::config::gameBoardCols
      );
    m_isFinish = false;

    m_gameBoardOneObjSize = 3;
  }

  PlayScene::~PlayScene()
  {
  }

  void PlayScene::init()
  {
    // auto me = std::make_shared<app::objects::PlayerOnline>();
    auto me = std::make_shared<app::objects::Player>();
    me->setIsTurn(true);
    // me->setMark(1);
    this->addPlayer(me);

    auto g1 = std::make_shared<app::objects::Player>();
    // g1->setMark(2);
    this->addPlayer(g1);
  }

  void PlayScene::draw()
  {
    this->drawGameBoard();
  }

  void PlayScene::quit()
  {
    // m_pGame->setScene(std::make_shared<app::scenes::IntroScene>(m_pGame));
    m_pGame->quit();
  }

  void PlayScene::update(const float dt)
  {
    if (m_isFinish == true)
    {
      std::cout << "Winner: " << m_currentPlayer << std::endl;
      this->quit();
      return;
    }

    if (m_listPlayer.size() > 0)
    {
      this->m_cursor = m_listPlayer.at(m_currentPlayer)->getCursor();

      std::weak_ptr<app::objects::Player> p = m_listPlayer.at(m_currentPlayer);
      if (auto pP = p.lock())
      {
        pP->update(dt);
      }
    }
  }

  void PlayScene::drawGameBoard()
  {
    assert((m_gameBoardOneObjSize % 2) != 0);
    // Barrier
    std::cout << "Current Player: " << m_currentPlayer << std::endl;
    auto drawBarrier = [](const int len){
      for (std::size_t i = 0; i < common::config::gameBoardCols; i++)
      {
        std::cout << '+';
        std::cout << std::string(len, '-');
      }
      std::cout << '+';
      std::cout << std::endl;
    };

    // Body
    auto drawLine = [=](const std::string &s){
      std::cout << '|';
      std::cout << std::string(m_gameBoardOneObjSize / 2, ' ');
      std::cout << s;
      std::cout << std::string(m_gameBoardOneObjSize / 2, ' ');
    };

    for (size_t x = 0; x < m_gameBoard.getBoard().size(); x++)
    {
      drawBarrier(m_gameBoardOneObjSize);
      // for (size_t y = 0; y < m_gameBoard.at(x).size(); y++)
      // {
      //   drawBody(" ");
      // }
      // std::cout << '|';
      // std::cout << std::endl;
      for (size_t y = 0; y < m_gameBoard.getBoard().at(x).size(); y++)
      {
        std::string curr;
        std::string color;

        switch (m_gameBoard.getBoard().at(x).at(y))
        {
          default:
          case 0:
            {
              color.clear();
              curr = " ";
            }
            break;
          case 1:
            {
              color = "\e[38;5;196m";
              curr = "x";
            }
            break;
          case 2:
            {
              color = "\e[38;5;37m";
              curr = "o";
            }
            break;
          case 3:
            {
              color = "\e[38;5;50m";
              curr = "z";
            }
            break;

        }
        if (m_cursor == common::Point2D(x, y))
        {
          color = "\e[48;5;255m";
        }
        curr += "\e[0m";

        drawLine(color + curr);
      }
      std::cout << '|';
      std::cout << std::endl;
      // for (size_t y = 0; y < m_gameBoard.at(x).size(); y++)
      // {
      //   drawBody(" ");
      // }
      // std::cout << '|';
      // std::cout << std::endl;
    }
    drawBarrier(m_gameBoardOneObjSize);
  }


  void PlayScene::checkFinish()
  {
    // if (this->m_gameBoard.isWinPoint(m_cursor, ))
  }

  common::GameBoard PlayScene::getGameBoard() const
  {
    return this->m_gameBoard;
  }

  void PlayScene::setGameBoard(const common::GameBoard &gb)
  {
    this->m_gameBoard = gb;
  }

  PlayScene::GameState PlayScene::checkMoveState(const common::Point2D &/* p */)
  {
    return PlayScene::GameState::WIN;
  }

  common::Point2D PlayScene::getCursor() const
  {
    return m_cursor;
  }

  void PlayScene::setCursor(const common::Point2D &c)
  {
    m_cursor = c;
  }

  void PlayScene::addPlayer(
    const std::shared_ptr<app::objects::Player> &player
    )
  {
    for (auto &p : m_listPlayer)
    {
      if (player == p)
      {
        return;
      }
    }
    player->setMark(m_listPlayer.size()+1);
    m_listPlayer.emplace_back(player);
    player->setScene(this);
    player->setCursor(
      common::Point2D(
        m_gameBoard.getBoard().size()/2,
        m_gameBoard.getBoard().at(m_gameBoard.getBoard().size()/2).size()/2
        )
      );
  }

  void PlayScene::removePlayer(
    const std::shared_ptr<app::objects::Player> &player
    )
  {
    for (auto &p : m_listPlayer)
    {
      if (player == p)
      {
        // m_listPlayer.erase(m_listPlayer.begin() + i);
        break;
      }
    }

  }

  PlayScene::ListPlayer PlayScene::getListPlayer() const
  {
    return m_listPlayer;
  }

  void PlayScene::setNextPlayer(const int nextPlayer)
  {
    if (nextPlayer >= static_cast<int>(m_listPlayer.size()))
    {
      this->m_currentPlayer = 0;
    }
    else
    {
      this->m_currentPlayer = nextPlayer;
    }

    m_listPlayer.at(m_currentPlayer)->setIsTurn(true);
  }

  int PlayScene::getCurrentPlayer() const
  {
    return m_currentPlayer;
  }

} }
