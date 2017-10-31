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
//      btn->setObjectName(QString(std::to_string(this->getGbBtnIndex(common::Point2D(x, y))).c_str()));

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
      QPushButton *btn = m_gameBoardButtonList.at(
                                       this->getGbBtnIndex(common::Point2D(x, y))
                                       );
      ui->gameBoardLayout->addWidget(btn, x, y);
    }
  }
}

void MainWindow::onGbBtnClicked(QPushButton *obj)
{
  obj->setText("x");
}

std::size_t MainWindow::getGbBtnIndex(const common::Point2D &p) const
{
  return (p.x * m_gameBoard.getBoard().size() + p.y);
}

common::Point2D MainWindow::getGbPointOfGbBtn(std::size_t index) const
{
  int x = index % m_gameBoard.getBoard().size();
  int y = index - m_gameBoard.getBoard().size() * x;
  return common::Point2D(x, y);
}

common::Point2D MainWindow::getGbPointOfGbBtn(QPushButton *btn) const
{
  std::size_t index = 0;
  for (auto &b : m_gameBoardButtonList)
  {
    if (b == btn)
    {
      return this->getGbPointOfGbBtn(index);
    }
    index++;
  }

  return common::Point2D();
}
