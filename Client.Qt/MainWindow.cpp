#include <QMessageBox>
#include <functional>
#include <QDebug>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "../Common/MessageStruct.hpp"
#include "../Common/Logger.hpp"
#include "../Common/Util.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_udpSocket("0.0.0.0", 0)
{
  ui->setupUi(this);

  // Actions
  QObject::connect(ui->actionNew_Game, &QAction::triggered, [this](){
    this->init();
  });

  auto sendLogout = [this](){
    char cmd = static_cast<char>(common::MessageType::QUIT_GAME);

    std::string msg = std::string(sizeof(cmd), cmd);

    m_udpSocket.send(
          msg, m_udpServerEndpoint,
          [](const std::error_code &, const std::size_t &){
    });
  };
  QObject::connect(ui->actionQuit, &QAction::triggered, [this, sendLogout](){
    if (ui->logoutButton->isEnabled())
    {
      auto reply = QMessageBox::question(ui->loginButton, "Logout", "Do you want to logout?");
      if (reply == QMessageBox::No)
      {
        return;
      }
      sendLogout();
    }
    this->close();
  });

  ui->serverAddrEdit->setText(common::config::serverAddr.c_str());
  ui->serverPortEdit->setText(std::to_string(common::config::serverPort).c_str());

  // Login
  QObject::connect(ui->loginButton, &QPushButton::clicked, [this](){
    if (ui->userNameInput->text().isEmpty())
    {
      QMessageBox::warning(ui->userNameInput, "Error", "User Name is empty");
      return;
    }
    if (ui->passwordInput->text().isEmpty())
    {
      QMessageBox::warning(ui->passwordInput, "Error", "Password is empty");
      return;
    }

    std::string serverAddr;
    short serverPort;
    if (ui->serverAddrEdit->text().isEmpty())
    {
      serverAddr = common::config::serverAddr;
    }
    else
    {
      serverAddr = ui->serverAddrEdit->text().toStdString();
    }
    if (ui->serverPortEdit->text().isEmpty())
    {
      serverPort = common::config::serverPort;
    }
    else
    {
      serverPort = ui->serverPortEdit->text().toShort();
    }
    m_udpServerEndpoint = common::net::socket::Udp::EndPoint(
          asio::ip::address::from_string(serverAddr),
          serverPort
          );
    // Game Board
    for (auto &b : m_gameBoardButtonList)
    {
      b->setDisabled(false);
    }

    // Login form
    this->disableLoginForm(true);
    char cmd = static_cast<char>(common::MessageType::LOGIN);

    std::string msg = std::string(sizeof(cmd), cmd)
        + ui->userNameInput->text().toStdString()
        + ":"
        + ui->passwordInput->text().toStdString()
        ;

    m_udpSocket.send(
          msg, m_udpServerEndpoint,
          [this](const std::error_code &, const std::size_t &){
      //      QDebug() << "F";
      //      qDebug() << "Sent Login data";

      //      QMessageBox::warning(ui->passwordInput, "Error", "Password is empty");
    });
  });

  // Logout
  QObject::connect(ui->logoutButton, &QPushButton::clicked, [this, sendLogout](){
    auto reply = QMessageBox::question(ui->loginButton, "Logout", "Do you want to logout?");
    if (reply == QMessageBox::No)
    {
      return;
    }

    sendLogout();

    this->disableLoginForm(false);
    this->init();
  });

  //
  this->init();

  m_serviceThread = std::thread(&MainWindow::run_service, this);
}

MainWindow::~MainWindow()
{
  for (auto &b : m_gameBoardButtonList)
  {
    delete b;
  }

  if (m_serviceThread.joinable())
  {
    m_serviceThread.join();
  }

  delete ui;
}

void MainWindow::init()
{
  m_seqNo = 0;
  m_gameBoard = common::GameBoard();

  m_gameBoardButtonList.clear();

  for (std::size_t x = 0; x < m_gameBoard.getBoard().size(); x++)
  {
    for (std::size_t y = 0; y < m_gameBoard.getBoard().at(x).size(); y++)
    {
      GbButton *btn = new GbButton(this);
      btn->setDisabled(true);
      //      btn->setBackgroundRole(QPalette::Dark);
      btn->setPoint(common::Point2D(x, y));
      QObject::connect(btn, &QPushButton::clicked, [this,btn](){
        this->onGbBtnClicked(btn);
      });

      m_gameBoardButtonList.emplace_back(btn);
      ui->gameBoardLayout->addWidget(btn, x, y);
    }
  }

  this->drawGameBoard();
}

void MainWindow::run_service()
{
  try
  {
    std::function<void()> receive = [&](){
      Log::info("Socket :: Receive :: start");
      m_udpSocket.receive(
            m_buffers, m_udpCurrentEndpoint,
            [this,receive](const std::error_code &e, const std::size_t &bytes)
      {
        if (e)
        {
          Log::error(e.message());
        }
        else
        {
          {
            std::string recv = std::string(m_buffers.data(), m_buffers.data() + bytes);
            Log::info("Player ID: "
//                      + std::to_string(m_listPlayer.front()->getId())
                       " :: receive :: started"
                      );
            this->onReceiveHandle(recv);
          }
        }
        receive();
      }
      );
    };

    receive();

    m_udpSocket.open();
  }
  catch (const std::exception &e)
  {
    Log::error(e.what());
  }
  catch (...)
  {
    Log::error("Server :: run() :: openSocket()");
  }
}

void MainWindow::disableLoginForm(const bool disable)
{
  ui->serverAddrEdit->setDisabled(disable);
  ui->serverPortEdit->setDisabled(disable);
  ui->userNameInput->setDisabled(disable);
  ui->passwordInput->setDisabled(disable);
  ui->loginButton->setDisabled(disable);
  ui->logoutButton->setDisabled(!disable);
}

void MainWindow::drawGameBoard()
{
  for (std::size_t x = 0; x < m_gameBoard.getBoard().size(); x++)
  {
    for (std::size_t y = 0; y < m_gameBoard.getBoard().at(x).size(); y++)
    {
      std::size_t b_pos = this->getGbBtnIndex(common::Point2D(x, y));
      switch (m_gameBoard.getBoard().at(x).at(y))
      {
        case 0:
          m_gameBoardButtonList.at(b_pos)->setText("");
          break;
        case 1:
          m_gameBoardButtonList.at(b_pos)->setText("x");
          break;
        case 2:
          m_gameBoardButtonList.at(b_pos)->setText("o");
          break;
        default:
          break;
      }
    }
  }
}

void MainWindow::onGbBtnClicked(GbButton *obj)
{
  common::Point2D pos = this->getGbPointOfGbBtn(obj);
  char cmd = static_cast<char>(common::MessageType::SET_MOVE);

  std::string msg = std::string(sizeof(cmd), cmd)
      + std::to_string(pos.x)
      + ":"
      + std::to_string(pos.y)
      ;

  m_udpSocket.send(
        msg, m_udpServerEndpoint,
        [](const std::error_code &, const std::size_t &){
  });
}

void MainWindow::onReceiveHandle(const std::string &data)
{
  try
  {
    common::MessageStruct ms(data);
    Log::info("Current Seq: " + std::to_string(m_seqNo));

    if (ms.isValidSum() == false)
    {
      return;
    }

    switch (ms.msgType)
    {
      case common::MessageType::LOGIN:
        {
          Log::info("PlayOnlineScene :: onReceiveHandle() :: RECV_ID");
          auto id = std::stoi(ms.msg);
          if (id)
          {
//            m_listPlayer.front()->setId(id);
//            m_listPlayer.front()->setMark(id);
            ui->playerInfoShowId->setText(std::to_string(id).c_str());
          }
//          else
//          {
//            std::cout << "Error set ID" << std::endl;
//            m_pGame->quit();
//          }
        }
        break;
      case common::MessageType::UPDATE_GAME:
        {
          Log::info("PlayOnlineScene :: onReceiveHandle() :: UPDATE_GAME");

          std::vector<std::string> game_data = Util::split(ms.msg, '|');

          Log::info("game_data size: " + std::to_string(game_data.size()));

          if (game_data.size() != 3)
          {
            return;
          }

          int seqNo = std::stoi(game_data.at(0));

          Log::info("Received Seq: " + std::to_string(seqNo));

          if (m_seqNo >= seqNo)
          {
            return;
          }

          m_seqNo = seqNo;

          std::vector<std::string> board = Util::split(game_data.at(2), ':');

          if (
            board.size() !=
            (common::config::gameBoardCols*common::config::gameBoardRows)
            )
          {
            return;
          }

          Log::info("Current Turn: " + std::to_string(m_turn));
          m_turn = std::stoi(game_data.at(1));

          Log::info("Received turn: " + std::to_string(m_turn));

          this->m_gameBoard.setBoard(game_data.at(2));

//          this->setNextPlayer(m_turn);
          this->drawGameBoard();
        }
        break;
      default:
        {
          Log::info("Server :: onReceiveHandle() :: NOTHING");
        }
        break;
    }
  }
  catch(...)
  {
    Log::error("PlayOnlineScene :: onReceiveHandle() :: ERROR");
  }
}

std::size_t MainWindow::getGbBtnIndex(const common::Point2D &p) const
{
  return (p.x * m_gameBoard.getBoard().size() + p.y);
}

common::Point2D MainWindow::getGbPointOfGbBtn(const GbButton *btn) const
{
  return btn->getPoint();
}
