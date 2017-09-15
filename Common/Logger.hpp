#ifndef COMMON_LOGGER_HPP
#define COMMON_LOGGER_HPP
#include <memory>
#include <string>

namespace spdlog {
  class logger;
}

namespace common {

  class Logger//  : std::enable_shared_from_this<Logger>
  {
    public:
      static std::shared_ptr<Logger> /* Logger * */getInstance();
      std::shared_ptr<Logger> operator<<(const std::string &/* message */);

    public:
      void info(const std::string &s);

    private:
    // public:
      Logger();
      // ~Logger();

    private:
      static std::weak_ptr<Logger> /* Logger * */m_pLogger;
      std::shared_ptr<spdlog::logger> m_pLogAPI;

  };

}

extern std::shared_ptr<common::Logger> Log;

#endif
