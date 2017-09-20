#include "Udp.hpp"

#include "../../Logger.hpp"

namespace common { namespace net { namespace socket {

  Udp::Udp(const std::string &ip, const short &port) :
    Socket()
    , m_socket(
      m_ioService,
      asio::ip::udp::endpoint(asio::ip::address::from_string(ip), port)
      )
  {
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

  void Udp::send(
    const std::string &s,
    const EndPoint &endpoint,
    const onReceiveHandle &handle
    )
  {
    m_socket.async_send_to(
      asio::buffer(s), endpoint, handle
      /*[](const std::error_code &e, const std::size_t &bytes){
        if (e)
        {
          Log::info(e.message());
          // throw std::
        }
        else
        {
          Log::info("Sent <" + std::to_string(bytes)  + ">");
        }
      }*/
      );
  }

  void Udp::receive(
    Buffer &buffer,
    EndPoint &endpoint,
    const onReceiveHandle &handle
    )
  {
    // Log::info("Start :: receive()");
    m_socket.async_receive_from(asio::buffer(buffer), endpoint, handle);
  }

} } }
