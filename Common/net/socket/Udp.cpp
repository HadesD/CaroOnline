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

  void Udp::open()
  {
    try
    {
      m_ioService.run();
    }
    catch(...)
    {
      Log::error("Error while open()");
    }
  }

  void Udp::send(const std::string &s,const EndPoint &endpoint)
  {
    m_socket.async_send_to(
      asio::buffer(s), endpoint,
      [this](const std::error_code &e, const std::size_t &bytes){
        if (e)
        {
          Log::info(e.message());
          // throw std::
        }
        else
        {
          Log::info("Sent <" + std::to_string(bytes)  + ">");
        }
      }
      );
  }

  void Udp::receive(Buffer &buffer, EndPoint &endpoint)
  {
  }

} } }
