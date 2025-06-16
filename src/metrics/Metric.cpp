#include "Metric.h"

namespace mes {
std::string Metric::getValue() {
  std::string metric = getMetric();
  reset();
  return metric;
}
}  // namespace mes