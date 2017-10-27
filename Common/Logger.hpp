#ifndef COMMON_LOGGER_HPP
#define COMMON_LOGGER_HPP
#include <memory>
#include <string>

namespace spdlog {
  class logger;
}

namespace common {

  class Logger
  {
    public:
      static std::shared_ptr<Logger> /* Logger * */getInstance();
      std::shared_ptr<Logger> operator<<(const std::string &/* message */);

    public:
      void info(const std::string &s);
      void error(const std::string &s);

    private:
      Logger();

    private:
      static std::weak_ptr<Logger> /* Logger * */m_pLogger;
      std::shared_ptr<spdlog::logger> m_pLogAPI;

  };

}

static const auto Logger = common::Logger::getInstance();
#include <iostream>
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

    static void error(const char *file, const int line, const std::string &s)
    {
      std::cout << file << line << std::endl;
      Logger->error(s);
    }
};

#endif

