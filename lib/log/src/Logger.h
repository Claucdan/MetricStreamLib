#ifndef METRICSTREAM_LOGGER_H
#define METRICSTREAM_LOGGER_H

#include <string>
#include "LogLevel.h"

namespace slg {

/**
 * @interface Logger
 * @brief Logs messages of different levels
 */
class Logger {
 protected:
  /// @brief log information with the specified level
  virtual void log(LogLevel, std::string) = 0;

 public:
  /// @brief log debug information
  void debug(std::string&& message);

  /// @brief log information
  void info(std::string&& message);

  /// @brief log warning information
  void warn(std::string&& message);

  /// @brief log error information
  void error(std::string&& message);

  /// @brief log fatal information
  void fatal(std::string&& message);
};

}  // namespace slg

#endif  //METRICSTREAM_LOGGER_H
