#ifndef METRICSTREAM_METRIC_H
#define METRICSTREAM_METRIC_H

#include <string>

namespace mes {

/**
 * @class Metric
 * @brief Abstract class for metrics
 */
class Metric {
 protected:
  /**
   * @brief Collect metric value
   * @return collected metric value
   */
  virtual std::string getMetric() = 0;

  /// @brief Reset metric value
  virtual void reset() = 0;

 public:
  /**
   * @brief Return name of the metric
   * @return name of metric
   */
  virtual std::string getName() const = 0;

  /**
   * @brief Return value of the metric
   * @return value of metric
   */
  virtual std::string getValue();

  virtual ~Metric() = default;
};
}  // namespace mes

#endif  //METRICSTREAM_METRIC_H