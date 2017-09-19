#include "Logger.hpp"

#include "spdlog/spdlog.h"

namespace common {

  static auto console = spdlog::stdout_color_mt("console");

  std::weak_ptr<Logger> Logger::m_pLogger;

  Logger::Logger()
  {
    // m_pLogAPI = std::make_shared<spdlog::logger>();
  }

  std::shared_ptr<Logger> Logger::getInstance()
  {
    if (m_pLogger.lock() == nullptr)
    {
      m_pLogger = std::shared_ptr<Logger>(new Logger());
    }

    return m_pLogger.lock();
  }

  void Logger::info(const std::string &s)
  {
    console->info(s);
  }

  std::shared_ptr<Logger> Logger::operator<<(const std::string &message)
  {
    // m_pLogAPI-> << message;
    // SPDLOGk

    console->info(message);

    return nullptr;

    // return this->shared_from_this();
  }

}
