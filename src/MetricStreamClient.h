#ifndef METRICSTREAM_METRICSTREAMCLIENT_H
#define METRICSTREAM_METRICSTREAMCLIENT_H

#include <memory>

#include "FileMetricsStorage.h"
#include "MultiThreadController.h"
#include "Scheduler.h"

namespace mes {

/**
 * @class MetricStreamClient
 * @brief Provides a simplified interface for working with the library
 */
class MetricStreamClient {
 private:
  ///@brief pointer to library scheduler
  std::shared_ptr<Scheduler> _scheduler;
  ///@brief pointer to library storage
  std::shared_ptr<MetricsStorage> _storage;
  ///@brief pointer to library controller of metric
  std::shared_ptr<MetricsController> _controller;

 public:
  /**
   * @brief Creates a facade with the specified parameters.
   * @param timeout The time between restarts of the stream.
   * @param countOfThread The number of threads allowed to be used to build metrics.
   * @param filename The name of the file where the collected metrics will be recorded.
   */
  MetricStreamClient(int timeout, int countOfThread, std::string filename);

  /**
   * @brief Facade destructor for safe resource release
   * @details It is waiting for the completion of the last metrics build.
   */
  ~MetricStreamClient();

  /// @brief Starts the metric stream.
  void startStream();

  /// @brief Stop the metric stream.
  void stopStream();

  /**
   * @brief Adds a metric to the stream.
   * @param metric the metric required for tracking
   */
  void addMetricToStream(std::shared_ptr<Metric>&& metric);

  /**
   * @brief Remove a metric from the stream.
   * @param metricName name of the metric in the stream
   */
  void removeMetric(std::string metricName);

  /**
   * @brief Set timeout sets the time between stream call time
   * @param timeout time between stream turns on
   */
  void setTimeout(int timeout);
};

}  // namespace mes

#endif  //METRICSTREAM_METRICSTREAMCLIENT_H
