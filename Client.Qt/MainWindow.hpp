#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include <memory>

#include "AppConfig.hpp"

#include "../Common/GameBoard.hpp"
#include "../Common/net/socket/Udp.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  public:
    void init();

  private:
    void drawGameBoard();
    void run_service();

  private:
    void onGbBtnClicked(QPushButton *obj = 0);
    void disableLoginForm(const bool disable);

  private:
    std::size_t getGbBtnIndex(const common::Point2D &/* p */) const;
    common::Point2D getGbPointOfGbBtn(const std::size_t /* index */) const;
    common::Point2D getGbPointOfGbBtn(const QPushButton * /* index */) const;

  private:
    Ui::MainWindow *ui;
    common::GameBoard m_gameBoard;
    std::vector< QPushButton* > m_gameBoardButtonList;

  private:
    // Network socket
    common::net::socket::Udp m_udpSocket;
    common::net::Socket::Buffer m_buffers;
    std::thread m_serviceThread;

    // Server
    common::net::socket::Udp::EndPoint m_udpServerEndpoint;
    common::net::socket::Udp::EndPoint m_udpCurrentEndpoint;
    unsigned int m_turn;
    int m_seqNo;

};

#endif // MAINWINDOW_HPP
