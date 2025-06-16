#ifndef METRICSTREAM_METRICSCONTROLLER_H
#define METRICSTREAM_METRICSCONTROLLER_H

#include <memory>
#include <string>

#include "Metric.h"
#include "MetricsStorage.h"

namespace mes {

/**
 * @interface MetricsController
 * @brief Control all metrics in MetricStream
 */
class MetricsController {
 private:
  /// @brief pointer to metrics storage
  std::shared_ptr<MetricsStorage> _metricsStorage;

 protected:
  /**
   * @brief add new collected value of metric to storage buffer
   * @param name name of the metric
   * @param value value of the metric
   */
  void addMetricToBuffer(std::string name, std::string value);

 public:
  /**
   * @brief Default constructor
   * @param metricsStorage metric storage for metrics
   */
  explicit MetricsController(std::shared_ptr<MetricsStorage> metricsStorage);

  /// @brief start collecting all metrics
  virtual void collectAllMetrics() = 0;

  /**
   * @brief Adds metric to control
   * @param metric metric for control
   */
  virtual void addMetric(std::shared_ptr<Metric>&& metric) = 0;

  /**
   * @brief
   * @param metricName name of metric in controller
   */
  virtual void removeMetricByName(std::string metricName) = 0;

  virtual ~MetricsController() = default;
};
}  // namespace mes
#endif  //METRICSTREAM_METRICSCONTROLLER_H