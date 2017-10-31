#include <QMessageBox>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "../Common/MessageStruct.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_gameBoard(),
  m_udpSocket("0.0.0.0", 0),
  m_udpServerEndpoint(
    asio::ip::address::from_string(app::config::serverIp),
    app::config::serverPort
    )
{
  ui->setupUi(this);

  char cmd = static_cast<char>(common::MessageType::LOGIN);

  std::string msg = std::string(sizeof(cmd), cmd)
      + "Dark.Hades"
      + ":"
      + "password"
      ;

  m_udpSocket.send(
        msg, m_udpServerEndpoint,
        [](const std::error_code &, const std::size_t &){
  }
  );
  m_seqNo = 0;


  this->init();
}

MainWindow::~MainWindow()
{
  for (auto &b : m_gameBoardButtonList)
  {
    delete b;
  }

  delete ui;
}

void MainWindow::init()
{
  for (std::size_t x = 0; x < m_gameBoard.getBoard().size(); x++)
  {
    for (std::size_t y = 0; y < m_gameBoard.getBoard().at(x).size(); y++)
    {
      QPushButton *btn = new QPushButton(this);
      QObject::connect(btn, &QPushButton::clicked, [this,btn](){
        this->onGbBtnClicked(btn);
      });

      m_gameBoardButtonList.emplace_back(btn);
    }
  }

  this->drawGameBoard();
}

void MainWindow::drawGameBoard()
{
  for (std::size_t x = 0; x < m_gameBoard.getBoard().size(); x++)
  {
    for (std::size_t y = 0; y < m_gameBoard.getBoard().at(x).size(); y++)
    {
      ui->gameBoardLayout->addWidget(m_gameBoardButtonList.at(
                                       this->getGbBtnIndex(common::Point2D(x, y))
                                       ),x,y);
    }
  }
}

void MainWindow::onGbBtnClicked(QPushButton *obj)
{
  obj->setText("X");
}

std::size_t MainWindow::getGbBtnIndex(const common::Point2D &p) const
{
  return (p.x * m_gameBoard.getBoard().size() + p.y);
}
