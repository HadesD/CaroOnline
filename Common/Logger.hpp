#ifndef COMMON_LOGGER_HPP
#define COMMON_LOGGER_HPP
#include <memory>
#include <string>

#ifdef IS_QT_CLIENT
# include <QTextEdit>
#endif

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

static const std::shared_ptr<common::Logger> logger = common::Logger::getInstance();
#include <iostream>
class Log {
  public:
    static void info(const std::string &s)
    {
      logger->info(s);
    }

    static void error(const std::string &s)
    {
      logger->error(s);
    }

    static void error(const char *file, const int line, const std::string &s)
    {
      logger->error(s);
    }
};

#endif
