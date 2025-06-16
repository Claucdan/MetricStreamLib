#include "Scheduler.h"

namespace mes {

    Scheduler::Scheduler(std::chrono::milliseconds timeout,
                         std::shared_ptr<MetricsStorage> metricsStorage,
                         std::shared_ptr<MetricsController> metricsController) {
        this->_timeout = timeout;
        this->_isRunning = false;
        this->_metricsStorage = std::move(metricsStorage);
        this->_metricsController = std::move(metricsController);
    }

    Scheduler::~Scheduler() {
        this->stop();
        slg::log->debug("Destruct schedular");
    }

    void Scheduler::process() {
        while (_isRunning) {
            try {
                std::string timeOfCollection = stf::getNowTime();
                auto start = std::chrono::system_clock::now();

                slg::log->debug("Start of scheduler process");
                _metricsController->collectAllMetrics();
                _metricsStorage->uploadBuffer(timeOfCollection);
                slg::log->debug("End of schedular process");

                auto end = std::chrono::system_clock::now();
                auto result = end - start;
                if (result < _timeout.load())
                    std::this_thread::sleep_for(_timeout.load() - result);
            } catch (std::exception e) {
                slg::log->error(e.what());
            }
        }
    }

    void Scheduler::start() {
        try {
            _isRunning = true;
            _processingThread = std::thread(&Scheduler::process, this);
            slg::log->info("Scheduler processingThread started");
        } catch (std::exception e) {
            slg::log->error(e.what());
        }
    }

    void Scheduler::stop() {
        slg::log->info("Stop schedular processingThread");
        this->_isRunning = false;
        if (this->_processingThread.joinable()) {
            this->_processingThread.join();
        }
    }

    void Scheduler::setTimeout(std::chrono::milliseconds timeout) {
        this->_timeout = timeout;
    }

}  // namespace mes