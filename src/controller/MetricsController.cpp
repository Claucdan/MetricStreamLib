#include "MetricsController.h"

#include <utility>

namespace mes {

void MetricsController::addMetricToBuffer(std::string name, std::string value) {
  _metricsStorage->addMetricToBuffer(std::move(name), std::move(value));
}

MetricsController::MetricsController(
    std::shared_ptr<MetricsStorage> metricsStorage)
    : _metricsStorage(std::move(metricsStorage)) {}

}  // namespace mes