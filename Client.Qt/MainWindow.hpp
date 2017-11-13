#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QCloseEvent>
#include <QPushButton>
#include <QTimer>
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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  public:
    void init();

  private:
    void drawGameBoard();
    void run_service();
    void sendQuitGame();
    void computerRun();

  private:
    void onGbBtnClicked(GbButton *obj);
    void disableLoginForm(const bool disable);
    void closeEvent(QCloseEvent *event);
    void onLogoutClicked();
    void onGameOver();

  private slots:
    void onTimerProgressBar();
    void setNextPlayer(const int p);
    void onReceiveHandle(const std::string &/* data */);

  private:
    std::size_t getGbBtnIndex(const common::Point2D &/* p */) const;
    common::Point2D getGbPointOfGbBtn(const GbButton * /* index */) const;

  private:
    Ui::MainWindow *ui;
    common::GameBoard m_gameBoard;
    std::vector< GbButton* > m_gameBoardButtonList;
    QTimer *m_timer;

  private:
    // Network socket
    common::net::socket::Udp m_udpSocket;
    common::net::Socket::Buffer m_buffers;
    std::thread m_serviceThread;

    // Server
    common::net::socket::Udp::EndPoint m_udpServerEndpoint;
    common::net::socket::Udp::EndPoint m_udpCurrentEndpoint;
    int m_turn;
    int m_seqNo;
    int m_playerId;
    common::PlayerMark m_playerMark;
    bool m_isGameOver;
    bool m_isLosed;
    int m_timeLeft;
    int m_peopleCount;
};

#endif // MAINWINDOW_HPP
