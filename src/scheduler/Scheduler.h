#ifndef METRICSTREAM_SCHEDULER_H
#define METRICSTREAM_SCHEDULER_H

#include <chrono>
#include <exception>
#include <memory>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#include "ConsoleLog.h"
#include "Metric.h"
#include "MetricsController.h"
#include "MetricsStorage.h"

#include "SimpleTimeFormat.h"

namespace mes {

/**
 * @class Scheduler
 * @brief Controls the start time. Schedules the launch time of the metrics controller and upload to storage.
 */
class Scheduler {
 private:
  /// @brief time between stream starts
  std::atomic<std::chrono::milliseconds> _timeout;
  /// @brief boolean is stream running
  std::atomic<bool> _isRunning;
  /// @brief thread of metric stream
  std::thread _processingThread;

  /// @brief pointer to metrics storage
  std::shared_ptr<MetricsStorage> _metricsStorage;
  /// @brief pointer to metrics controller
  std::shared_ptr<MetricsController> _metricsController;

 protected:
  /**
   * @brief Metric processing method
   */
  void process();

 public:
  /// @brief Default constructor
  explicit Scheduler(std::chrono::milliseconds timeout,
                     std::shared_ptr<MetricsStorage> metricsStorage,
                     std::shared_ptr<MetricsController> metricsController);

  /**
   * @brief Default destructor
   * @details Stops processing the MetricStream
   */
  ~Scheduler();

  /**
   * @brief Starts processing of MetricStream
   * @details Creates a new thread where metrics are processed
   */
  void start();

  /**
   * @brief Stop processing of MetricStream
   * @details Stop a thread where metrics are processed
   */
  void stop();

  /**
   * @brief Sets the timeout
   * @param timeout time delay for resuming the MetricStream
   */
  void setTimeout(std::chrono::milliseconds timeout);
};

}  // namespace mes

#endif  //METRICSTREAM_SCHEDULER_H