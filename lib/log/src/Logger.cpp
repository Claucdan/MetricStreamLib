#include "Logger.h"

namespace slg {
void Logger::debug(std::string&& message) {
#ifdef DEBUG_LOG
  log(DEBUG, message);
#endif
}

void Logger::info(std::string&& message) {
  log(INFO, message);
}

void Logger::warn(std::string&& message) {
  log(WARN, message);
}

void Logger::error(std::string&& message) {
  log(ERROR, message);
}

void Logger::fatal(std::string&& message) {
  log(FATAL, message);
}

}  // namespace slg