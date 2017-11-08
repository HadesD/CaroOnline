#include <iostream>

#include "app/Server.hpp"

int main(int argc, char *argv[])
{
  /*
   * if (argc < 2)
   * {
   *   std::cerr << "Usage: ./server <port>" << std::endl;

   *   return 1;
   * }
   */

  try
  {
    int port = common::config::serverPort;

    if (argc > 1)
    {
      std::string s = argv[1];
      port = std::stoi(s);
    }

    // TCP
    asio::io_service io_service;

    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
    asio::ip::tcp::acceptor acceptor(io_service, endpoint);

    int i = 1;
    while (true)
    {
      if (i == 1)
      {
        i = 0;

        std::cout << "Choosen port: " <<  port << std::endl;

        app::Server server("0.0.0.0", port);

        server.run();
      }
      asio::ip::tcp::iostream stream;
      std::error_code ec;
      acceptor.accept(*stream.rdbuf(), ec);
      if (!ec)
      {
        stream <<
          "HTTP/1.1 404 Notfound"
          "Allow: GET, HEAD"
          "Server: CaroOnline/0.0.1"
          "Content-Type: text/html; charset=utf-8"
          "Content-Length: 0"
          "Connection: close"
          ;
      }
    }
    // TCP

  }
  catch(const std::exception &e)
  {
    std::cerr << "Exeption: " << e.what() << std::endl;
  }

  std::cout << "Server shutdown" << std::endl;

  return 0;
}
