#ifndef METRICSTREAM_MULTITHREADCONTROLLER_H
#define METRICSTREAM_MULTITHREADCONTROLLER_H

#include <chrono>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

#include "ConsoleLog.h"
#include "MetricsController.h"
#include "MetricsStorage.h"

namespace mes {

/**
     * @class MultiThreadController
     * @implements MetricsController
     * @brief Control Metrics in multithread
     */
class MultiThreadController : public MetricsController {
 private:
  /// @brief queue mutex of controlled metrics
  std::mutex _queueMutex;
  /// @brief thread pool mutex
  std::mutex _threadPoolMutex;
  /// @brief metric pool mutex for control pool
  std::mutex _metricPoolMutex;

  /// @brief metrics queue of controlled metrics
  std::list<std::shared_ptr<Metric>> _metricsQueue;
  /// @brief thread pool
  std::vector<std::thread> _threadPool;

 protected:
  /**
   * @brief Returns the following metric for processing from the pool
   * @return null if pool is empty or pointer to Metric
   */
  std::shared_ptr<Metric> getNextMetric(
      std::shared_ptr<std::list<std::shared_ptr<Metric>>>);

  /// @brief Collects metrics from the pool until it becomes empty
  void collectMetric(std::shared_ptr<std::list<std::shared_ptr<Metric>>>);

 public:
  /// @brief Default constructor MultiThreadController
  explicit MultiThreadController(std::shared_ptr<MetricsStorage> storage,
                                 int threadCount = 1);

  void collectAllMetrics() override;

  void addMetric(std::shared_ptr<Metric>&& metric) override;

  void removeMetricByName(std::string metricName) override;

  /**
   * @brief Default destructor
   * @details Stop all thread for control metric
   */
  ~MultiThreadController() override;
};

}  // namespace mes

#endif  //METRICSTREAM_MULTITHREADCONTROLLER_H
