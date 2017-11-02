#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include <memory>

#include "AppConfig.hpp"
#include "GbButton.hpp"

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
    void onGbBtnClicked(GbButton *obj = 0);
    void onReceiveHandle(const std::string &/* data */);
    void disableLoginForm(const bool disable);

  private:
    std::size_t getGbBtnIndex(const common::Point2D &/* p */) const;
    common::Point2D getGbPointOfGbBtn(const GbButton * /* index */) const;
    void setNextPlayer(const int p);

  private:
    Ui::MainWindow *ui;
    common::GameBoard m_gameBoard;
    std::vector< GbButton* > m_gameBoardButtonList;

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
    int m_playerId;

};

#endif // MAINWINDOW_HPP
