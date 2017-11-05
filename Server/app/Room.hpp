#ifndef APP_ROOM_HPP
#define APP_ROOM_HPP

#include "Type.hpp"

#include "../Common/Type.hpp"
#include "../Common/GameBoard.hpp"

namespace app {

  class Server;

  class Room
  {
    public:
      typedef common::GameBoard GameBoard;
    public:
      struct Player
      {
        Player(){}
        Player(
          const Client &c,
          const std::string &n,
          const common::PlayerMark m
          ) : client(c), userName(n), mark(m) {}
        Client client;

        std::string userName;
        // std::string password;

        common::PlayerMark mark;
      };

    public:
      Room(const std::shared_ptr<Server> &sv);
      Room(Server *sv);
      ~Room();

    public:
      void sendGameDataToAllPlayers();
      void onReceiveHandle(const Client &cli , const std::string &/* data */);
      GameBoard getGameBoard() const;
      void onGameOver();

    public:
      void addPlayer(const std::shared_ptr<Player> &player);
      void removePlayer(const std::shared_ptr<Player> &player);
      void removePlayer(const std::size_t player);
      std::size_t getOrCreatePlayer(const Client &client);
      std::size_t getPlayer(const Client &client) const;
      std::vector< std::shared_ptr<Player> > getPlayerList() const;
      void setId(const int id);

    private:
      GameBoard m_gameBoard;
      std::vector< std::shared_ptr<Player> > m_playerList;
      int m_id;
      int m_seqNo;
      std::size_t m_turn;
      bool m_isGameOver;
      // std::shared_ptr<Server> m_pServer;
      Server *m_pServer;

  };

}

#endif
