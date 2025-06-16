#include "MetricStreamClient.h"

namespace mes {

MetricStreamClient::MetricStreamClient(int timeout, int countOfThread,
                                       std::string filename) {
  std::shared_ptr<MetricsStorage> _storage = std::make_shared<FileMetricsStorage>(filename);
  _controller =
      std::make_shared<MultiThreadController>(_storage, countOfThread);
  _scheduler = std::make_shared<Scheduler>(std::chrono::milliseconds(timeout),
                                           std::move(_storage), _controller);
}

MetricStreamClient::~MetricStreamClient() {
  stopStream();
}

void MetricStreamClient::startStream() {
  _scheduler->start();
}

void MetricStreamClient::stopStream() {
  _scheduler->stop();
}

void MetricStreamClient::addMetricToStream(std::shared_ptr<Metric>&& metric) {
  _controller->addMetric(std::move(metric));
}

void MetricStreamClient::removeMetric(std::string metricName) {
  _controller->removeMetricByName(std::move(metricName));
}

void MetricStreamClient::setTimeout(int timeout) {
  _scheduler->setTimeout(std::chrono::milliseconds(timeout));
}
}  // namespace mes