#include "ConsoleLogger.h"

namespace slg {

    std::ostream &operator<<(std::ostream &out, const LogLevel &logLevel) {
        switch (logLevel) {
            case DEBUG:
                return (out << "DEBUG");
            case INFO:
                return (out << "INFO");
            case WARN:
                return (out << "WARN");
            case ERROR:
                return (out << "ERROR");
            case FATAL:
                return (out << "FATAL");
        }
        return (out);
    }

    void ConsoleLogger::log(LogLevel level, std::string message) {
        std::string time = stf::getNowTime();

        while (!lock.try_lock());

        std::cout << time << " " << level << " " << message << "\n";
        lock.unlock();
    }
}  // namespace slg