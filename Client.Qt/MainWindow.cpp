#include <functional>
#include <QMessageBox>
#include <QThread>
#include <QDebug>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "Minimax.hpp"

#include "../Common/MessageStruct.hpp"
#include "../Common/Logger.hpp"
#include "../Common/Util.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_udpSocket("0.0.0.0", 0)
{
  ui->setupUi(this);

  m_timer = new QTimer();
  // Actions
  QObject::connect(ui->actionNew_Game, &QAction::triggered, [this](){
    this->init();
  });

  QObject::connect(ui->actionQuit, &QAction::triggered, [this](){
    this->onLogoutClicked();
    if (!ui->logoutButton->isEnabled())
    {
      this->close();
    }
  });

  ui->serverAddrEdit->setText(common::config::serverAddr.c_str());
  ui->serverPortEdit->setText(std::to_string(common::config::serverPort).c_str());

  // Login
//  ui->userNameInput->setHidden(true);
//  ui->passwordInput->setHidden(true);
//  ui->userNameLabel->setHidden(true);
//  ui->passwordLabel->setHidden(true);
  QObject::connect(ui->loginButton, &QPushButton::clicked, [this](){
//    if (ui->userNameInput->text().isEmpty())
//    {
//      QMessageBox::warning(ui->userNameInput, "Error", "User Name is empty");
//      return;
//    }
//    if (ui->passwordInput->text().isEmpty())
//    {
//      QMessageBox::warning(ui->passwordInput, "Error", "Password is empty");
//      return;
//    }
    this->init();

    std::string serverAddr = common::config::serverAddr;
    short serverPort = common::config::serverPort;
    if (!ui->serverAddrEdit->text().isEmpty())
    {
      serverAddr = ui->serverAddrEdit->text().toStdString();
    }

    if (!ui->serverPortEdit->text().isEmpty())
    {
      serverPort = ui->serverPortEdit->text().toInt();
    }
    m_udpServerEndpoint = m_udpSocket.resolver(serverAddr, serverPort);
    // Game Board
    for (auto &b : m_gameBoardButtonList)
    {
      b->setDisabled(false);
    }

    // Login form
    this->disableLoginForm(true);
    char cmd = static_cast<char>(common::MessageType::LOGIN);

    std::string msg = std::string(sizeof(cmd), cmd)
//        + ui->userNameInput->text().toStdString()
        + "Dark.Hades"
        + ":"
//        + ui->passwordInput->text().toStdString()
        "password"
        ;

    m_udpSocket.send(
          msg, m_udpServerEndpoint,
          [this](const std::error_code &, const std::size_t &){
    });
  });

  // Logout
  QObject::connect(ui->logoutButton, &QPushButton::clicked, [this](){
    this->onLogoutClicked();
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

  delete m_timer;
  delete ui;
}

void MainWindow::init()
{
  m_seqNo = 0;
  m_turn = -1;
  m_playerId = 0;
  m_peopleCount = 0;
  m_gameBoard = common::GameBoard();
  m_isGameOver = false;
  m_isLosed = false;
  ui->gameInfoShowSequence->setText("0");
  ui->gameInfoShowTurn->setText("You must login first");
  ui->gameInfoShowViewerCount->setText("0");
  ui->playerInfoMarkButton->setText("");
  ui->playerInfoShowId->setText("");
  ui->gameInfotimeLeftProgressBar->setValue(0);
  if (m_timer != nullptr)
  {
    m_timer->stop();
  }

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

  if (ui->loginButton->isEnabled())
  {
    m_playerId = 0;
    m_playerMark = 1;
    m_turn = 0;
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
            if (thread() == QThread::currentThread())
            {
              qDebug() << "onReceiveHandle :: IN THREAD";
              this->onReceiveHandle(recv);
            }
            else
            {
              qDebug() << "onReceiveHandle :: NOT IN THREAD";
              qRegisterMetaType<std::string>("std::string");
              QMetaObject::invokeMethod(this, "onReceiveHandle", Qt::QueuedConnection, Q_ARG(std::string, recv));
            }
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
//  ui->userNameInput->setDisabled(disable);
//  ui->passwordInput->setDisabled(disable);
  ui->loginButton->setDisabled(disable);
  ui->logoutButton->setDisabled(!disable);
  ui->newGameButton->setDisabled(disable);
}

void MainWindow::drawGameBoard()
{
  for (std::size_t x = 0; x < m_gameBoard.getBoard().size(); x++)
  {
    for (std::size_t y = 0; y < m_gameBoard.getBoard().at(x).size(); y++)
    {
      std::size_t b_pos = this->getGbBtnIndex(common::Point2D(x, y));

      auto mark_id = m_gameBoard.getBoard().at(x).at(y);

      QPushButton *btn = m_gameBoardButtonList.at(b_pos);

      this->setBtnMark(btn, mark_id);

      if (((m_turn == m_playerId) && (m_turn != -1)) || (mark_id != 0))
      {
        btn->setDisabled(false);
      }
      else
      {
        btn->setDisabled(true);
      }
    }
  }
}

void MainWindow::onGbBtnClicked(GbButton *obj)
{
  if (ui->loginButton->isEnabled())
  {
    common::Point2D pos = this->getGbPointOfGbBtn(obj);
    auto gb = m_gameBoard.getBoard();
    if (gb.at(pos.x).at(pos.y) != 0)
    {
      return;
    }
    gb[pos.x][pos.y] = m_playerMark;
    m_gameBoard.setBoard(gb);
    if (m_gameBoard.isWinPoint(pos, m_playerMark))
    {
      m_isGameOver = true;
    }
    m_turn = 1;
    this->drawGameBoard();
    if (m_isGameOver)
    {
      this->onGameOver();
    }
    else
    {
      this->computerRun();
    }
  }
  else
  {
    if (m_isGameOver)
    {
      QMessageBox::warning(this, "Game Over!", "You must logout from this game to create a new game!");
      return;
    }
    common::Point2D pos = this->getGbPointOfGbBtn(obj);
    if (m_gameBoard.getBoard().at(pos.x).at(pos.y) != 0)
    {
      return;
    }

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
    m_timer->stop();
  }
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
        std::vector< std::string > recv = Util::split(ms.msg, '|');
        if (recv.size() == 2)
        {
          m_playerId = std::stoi(recv.at(0));
          ui->playerInfoShowId->setText(QString::number(m_playerId));
          m_playerMark = std::stoi(recv.at(1));
          this->setBtnMark(ui->playerInfoMarkButton, m_playerMark);
          ui->gameInfoShowTurn->setText("Waiting for player...");
        }
        else
        {
          QMessageBox::warning(nullptr, "Login Error", "Data received from server has an error");
          this->disableLoginForm(false);
        }
      }
        break;
      case common::MessageType::UPDATE_GAME:
      {
        Log::info("PlayOnlineScene :: onReceiveHandle() :: UPDATE_GAME");

        std::vector<std::string> game_data = Util::split(ms.msg, '|');

        Log::info("game_data size: " + std::to_string(game_data.size()));

        if (game_data.size() != 4)
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
        ui->gameInfoShowSequence->setText(QString::number(m_seqNo));

        std::vector<std::string> board = Util::split(game_data.at(3), ':');

        if (
            board.size() !=
            (common::config::gameBoardCols*common::config::gameBoardRows)
            )
        {
          return;
        }

        Log::info("Current Turn: " + std::to_string(m_turn));

        int recv_turn = std::stoi(game_data.at(1));
        Log::info("Received turn: " + std::to_string(recv_turn));

        this->m_gameBoard.setBoard(game_data.at(3));

        m_peopleCount = std::stoi(game_data.at(2));

        this->setNextPlayer(recv_turn);
        this->drawGameBoard();

        Log::info("People Count: " + std::to_string(m_peopleCount));

        ui->gameInfoShowViewerCount->setText(QString::number(m_peopleCount));
      }
        break;
      case common::MessageType::GAME_OVER:
      {
        if (ui->loginButton->isEnabled())
        {
          return;
        }
        this->onGameOver();
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

void MainWindow::onLogoutClicked()
{
  if (!ui->logoutButton->isEnabled())
  {
    return;
  }

  auto reply = QMessageBox::question(ui->loginButton, "Logout", "Do you want to logout?");
  if (reply == QMessageBox::No)
  {
    return;
  }

  this->disableLoginForm(false);
  this->init();

  this->sendQuitGame();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  this->onLogoutClicked();

  if (!ui->loginButton->isEnabled())
  {
    event->ignore();
  }
  else
  {
    event->accept();
    qApp->closeAllWindows();
    qApp->exit();
  }
}

void MainWindow::setBtnMark(QPushButton* btn, const common::PlayerMark mark)
{
  btn->setText(QString(QChar(Util::getMark(mark))));
  QString bcolor;
  switch (mark)
  {
    case 1:
    {
      bcolor = "background-color: #00aaff;color:#fff;font-weight:bold;";
    }
      break;
    case 2:
    {
      bcolor = "background-color: #ff4322;color:#fff;font-weight:bold;";
    }
      break;
    default:
    {
      bcolor = "background-color: #f3f3f4;";
    }
      break;
  }
  btn->setStyleSheet(bcolor);
}

std::size_t MainWindow::getGbBtnIndex(const common::Point2D &p) const
{
  return (p.x * m_gameBoard.getBoard().size() + p.y);
}

common::Point2D MainWindow::getGbPointOfGbBtn(const GbButton *btn) const
{
  return btn->getPoint();
}

void MainWindow::setNextPlayer(const int p)
{
  if (m_peopleCount < 2)
  {
    return;
  }
  if (thread() == QThread::currentThread())
  {
    qDebug() << "IN THREAD";
    QString playerName = "Player " + QString::number(p);

    if (p == m_playerId)
    {
      qDebug() << "Is my turn";
      playerName = "You";

      if (m_playerId != m_turn)
      {
        m_timer = new QTimer();
        QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimerProgressBar()));
        m_timeLeft = common::config::maxWaitTime;
        ui->gameInfotimeLeftProgressBar->setValue(ui->gameInfotimeLeftProgressBar->maximum());
        m_timer->start(1000);
      }
    }
    else
    {
      m_timeLeft = 0;
    }

    m_turn = p;

    ui->gameInfoShowTurn->setText(playerName);
  }
  else
  {
    qDebug() << "NOT IN THREAD";
    //    qRegisterMetaType<std::size_t>();
    QMetaObject::invokeMethod(this, "setNextPlayer", Qt::QueuedConnection, Q_ARG(int, p));
    return;
  }
}

void MainWindow::onGameOver()
{
  if (ui->loginButton->isEnabled())
  {
    QMessageBox::information(nullptr, "Game Over", "Let open new game");
  }
  else
  {
    if (m_isGameOver)
    {
      return;
    }
    if (m_timer != nullptr)
    {
      m_timer->stop();
    }

    this->sendQuitGame();

    QMessageBox::information(nullptr, "Game Over", "Login again to create new game!");
  }
}

void MainWindow::sendQuitGame()
{
  // Send to Server
  char cmd = static_cast<char>(common::MessageType::QUIT_GAME);
  std::string msg = std::string(sizeof(cmd), cmd);
  m_udpSocket.send(
        msg, m_udpServerEndpoint,
        [](const std::error_code &, const std::size_t &) -> void
  {
  }
  );

}

void MainWindow::onTimerProgressBar()
{
  qDebug() << "onTimerProgressBar :: running()";
  int minValue = ui->gameInfotimeLeftProgressBar->minimum();
  int maxValue = ui->gameInfotimeLeftProgressBar->maximum();
  qDebug() << "m_timeLeft: " << m_timeLeft;
  m_timeLeft--;
  qDebug() << "m_timeLeft: " << m_timeLeft;
  float per = static_cast<float>(m_timeLeft) /
      static_cast<float>(common::config::maxWaitTime);
  qDebug() << per;
  int nextValue = (per * maxValue);
  qDebug() << "nextValue: " << nextValue;
  ui->gameInfotimeLeftProgressBar->setValue(nextValue);

  if (nextValue <= minValue)
  {
    this->onGameOver();
  }
}

void MainWindow::computerRun()
{
  Minimax minimax;
  common::Point2D pos = minimax.getBestMove(m_gameBoard, 2);

  auto gb = m_gameBoard.getBoard();
  gb[pos.x][pos.y] = 2;
  m_gameBoard.setBoard(gb);

  m_turn = 0;
  this->drawGameBoard();

  if (m_gameBoard.isWinPoint(pos, 2))
  {
    m_isGameOver = true;
    this->onGameOver();
  }
}
