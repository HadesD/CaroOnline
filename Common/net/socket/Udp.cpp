#include "Udp.hpp"

#include "../../Logger.hpp"

namespace common { namespace net { namespace socket {

  Udp::Udp(const std::string &ip, const int &port) :
    Socket()
    , m_socket(
      m_ioService,
      asio::ip::udp::endpoint(
        asio::ip::udp::v4(),
        // asio::ip::address::from_string(ip),
        port
        )
      )
  {
    Log::info("UdpSocket will use " + ip + ":" + std::to_string(port));
  }

  Udp::~Udp()
  {
  }

  bool Udp::isOpening()
  {
    return (m_ioService.stopped() == false);
  }

  void Udp::open()
  {
    Log::info("UdpSocket :: open()");

    while (this->isOpening() == true)
    {
      try
      {
        m_ioService.run();
      }
      catch(...)
      {
        Log::error("Error while open()");
        throw std::runtime_error("Can not run io_service");
      }
    }
  }

  void Udp::send(
    const std::string &s,
    const EndPoint &endpoint,
    const onReceiveHandle &handle
    )
  {
    Log::info("UdpSocket :: send()");
    Log::info("Send Message: " + s);
    std::string send_buff = common::config::networkCheckSum + s;
    m_socket.async_send_to(asio::buffer(send_buff), endpoint, handle);
  }

  void Udp::receive(
    Buffer &buffer,
    EndPoint &endpoint,
    const onReceiveHandle &handle
    )
  {
    Log::info("UdpSocket :: receive()");
    m_socket.async_receive_from(asio::buffer(buffer), endpoint, handle);
  }

  void Udp::sync_recv(
    const std::string &s,
    EndPoint &endpoint
    )
  {
    Log::info("UdpSocket :: sync_recv()");
    std::string send_buff = common::config::networkCheckSum + s;
    m_socket.receive_from(asio::buffer(send_buff), endpoint);
  }

  Udp::EndPoint Udp::resolver(const std::string &from_adr, const int port)
  {
    asio::ip::udp::resolver resolv(m_ioService);
    asio::ip::udp::resolver::query q(
      asio::ip::udp::v4(), from_adr,
      std::to_string(port)
      );
    return *resolv.resolve(q);
  }

} } }
