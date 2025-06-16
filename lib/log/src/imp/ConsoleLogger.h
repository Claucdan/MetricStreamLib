#ifndef METRICSTREAM_CONSOLELOGGER_H
#define METRICSTREAM_CONSOLELOGGER_H

#include <iostream>
#include <chrono>
#include <format>
#include <mutex>

#include "../Logger.h"
#include "SimpleTimeFormat.h"

namespace slg {

    /**
     * @class ConsoleLogger
     * @implements Logger
     * @brief log information to console
     */
    class ConsoleLogger : public Logger {
    private:
        std::mutex lock;
    protected:
        void log(LogLevel, std::string) override;
    };

}  // namespace slg

#endif  //METRICSTREAM_CONSOLELOGGER_H
