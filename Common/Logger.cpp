#include "Logger.hpp"

#include "spdlog/spdlog.h"

namespace common {

  static auto console = spdlog::stdout_color_mt("");
  static auto file = spdlog::basic_logger_mt("file", "all.log");

  std::weak_ptr<Logger> Logger::m_pLogger;

  Logger::Logger()
  {
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
#ifdef DEBUG
    console->info(s);
#endif
    file->info(s);
  }

  void Logger::error(const std::string &s)
  {
#ifdef DEBUG
    console->error(s);
#endif
  }

  std::shared_ptr<Logger> Logger::operator<<(const std::string &message)
  {
#ifdef DEBUG
    console->info(message);
#endif

    return nullptr;
  }

}
