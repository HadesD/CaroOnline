#include "Logger.hpp"

#ifdef USE_SPDLOG
#include "spdlog/spdlog.h"
#endif

#ifdef IS_QT_CLIENT
#include <QDebug>
#endif


namespace common {

#ifdef USE_SPDLOG
  static auto console = spdlog::stdout_color_mt("");
  static auto file = spdlog::basic_logger_mt("file", "all.log");
#endif

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
#ifdef USE_SPDLOG
      file->info(s);
#endif
#if defined(DEBUG) || defined(IS_SERVER)
#  ifdef USE_SPDLOG
      console->info(s);
#  endif
#endif
#ifdef IS_QT_CLIENT
      qDebug() << s.c_str();
#endif
  }

  void Logger::error(const std::string &s)
  {
#ifdef USE_SPDLOG
      file->info(s);
#endif
#if defined(DEBUG) || defined(IS_SERVER)
#  ifdef USE_SPDLOG
      console->error(s);
#  endif
#endif
  }

}
