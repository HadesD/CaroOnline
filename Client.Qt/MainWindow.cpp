#include <QMessageBox>
#include <functional>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "../Common/MessageStruct.hpp"
#include "../Common/Logger.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_udpSocket("0.0.0.0", 0)
{
  ui->setupUi(this);

  logQTextEdit = ui->logEdit;

  // Login
  m_udpServerEndpoint = common::net::socket::Udp::EndPoint(
        asio::ip::address::from_string(app::config::serverIp),
        app::config::serverPort
        );
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
      ui->logEdit->append("Sent data");

      QMessageBox::warning(ui->passwordInput, "Error", "Password is empty");
    });
  });

  // Logout
  QObject::connect(ui->logoutButton, &QPushButton::clicked, [this](){
    auto reply = QMessageBox::question(ui->loginButton, "Logout", "Do you want to logout?");
    if (reply == QMessageBox::No)
    {
      return;
    }
    char cmd = static_cast<char>(common::MessageType::QUIT_GAME);

    std::string msg = std::string(sizeof(cmd), cmd);

    m_udpSocket.send(
          msg, m_udpServerEndpoint,
          [](const std::error_code &, const std::size_t &){
    });

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
    }
  }

  this->drawGameBoard();
}

void MainWindow::run_service()
{
  try
  {
    std::function<void()> receive = [&](){
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
                      //                      + " :: receive :: started"
                      );
            //            this->onReceiveHandle(recv);
          }
        }
        receive();
      }
      );
    };

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
      GbButton *btn = m_gameBoardButtonList.at(
            this->getGbBtnIndex(common::Point2D(x, y))
            );
      ui->gameBoardLayout->addWidget(btn, x, y);
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

std::size_t MainWindow::getGbBtnIndex(const common::Point2D &p) const
{
  return (p.x * m_gameBoard.getBoard().size() + p.y);
}

common::Point2D MainWindow::getGbPointOfGbBtn(const GbButton *btn) const
{
  return btn->getPoint();
}
