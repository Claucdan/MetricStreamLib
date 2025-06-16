#ifndef METRICSTREAM_METRICSSTORAGE_H
#define METRICSTREAM_METRICSSTORAGE_H

#include "Metric.h"

namespace mes {

/**
 * @interface MetricsStorage
 * @brief Class that stores metrics instead of storing
 */
class MetricsStorage {
 public:
  /**
   * @brief Uploads the metrics buffer to a storage location
   * @param time time to uploads the metrics
   */
  virtual void uploadBuffer(std::string time) = 0;

  /**
   * @brief Adds the metric value to the buffer.
   * @param name name of the metric
   * @param value the metric value
   */
  virtual void addMetricToBuffer(std::string name, std::string value) = 0;

  virtual ~MetricsStorage() = default;
};

}  // namespace mes

#endif  //METRICSTREAM_METRICSSTORAGE_H