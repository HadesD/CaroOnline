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
      void error(const std::string &s);

    private:
    // public:
      Logger();
      // ~Logger();

    private:
      static std::weak_ptr<Logger> /* Logger * */m_pLogger;
      std::shared_ptr<spdlog::logger> m_pLogAPI;

  };

}

static const auto Logger = common::Logger::getInstance();
// template <typename ...T>
class Log {
  private:

  public:
    static void info(const std::string &s)
    {
      Logger->info(s);
    }

    static void error(const std::string &s)
    {
      Logger->error(s);
    }
};

#endif
