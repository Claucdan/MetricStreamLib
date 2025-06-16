#include "MultiThreadController.h"

namespace mes {

MultiThreadController::MultiThreadController(
    std::shared_ptr<MetricsStorage> storage, int threadCount)
    : MetricsController(std::move(storage)) {
  _threadPool.resize(threadCount);
}

std::shared_ptr<Metric> MultiThreadController::getNextMetric(
    std::shared_ptr<std::list<std::shared_ptr<Metric>>> metricsPool) {
  while (!_metricPoolMutex.try_lock())
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

  slg::log->debug("Lock metric pool for get next metric for collection");

  std::shared_ptr<Metric> tmp = nullptr;
  if (!metricsPool->empty()) {
    tmp = metricsPool->front();
    metricsPool->pop_front();
  }

  _metricPoolMutex.unlock();

  slg::log->debug("Unlock metric pool");

  return tmp;
}

void MultiThreadController::collectMetric(
    std::shared_ptr<std::list<std::shared_ptr<Metric>>> metricPool) {

  std::shared_ptr<Metric> tmp;
  while ((tmp = getNextMetric(metricPool)) != nullptr) {
    try {
      std::string metricName = tmp->getName();
      std::string metricValue = tmp->getValue();

      addMetricToBuffer(metricName, metricValue);
      slg::log->info("Collect info and save to storage of metric: " +
                     metricName);
    } catch (std::exception e) {
      slg::log->error(e.what());
    }
  }
}

void MultiThreadController::collectAllMetrics() {
  /*Get metrics pool copy for collection*/
  while (!_queueMutex.try_lock())
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

  slg::log->debug("Lock queueMutex for copy metrics queue");
  std::shared_ptr<std::list<std::shared_ptr<Metric>>> metricsPool =
      std::make_shared<std::list<std::shared_ptr<Metric>>>();
  *metricsPool = _metricsQueue;
  _queueMutex.unlock();
  slg::log->debug("Unlock queueMutex");

  /*Wait another collection End*/
  while (!_threadPoolMutex.try_lock())
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

  slg::log->info("Start collection metrics info");

  slg::log->debug("Starting creation thread for collection metrics");
  /*Start all thread for collection*/
  for (auto& i : _threadPool) {
    i = std::thread(&MultiThreadController::collectMetric, this, metricsPool);
  }

  slg::log->debug("Waiting thread for end collection metrics");
  /*Wait all thread for end collection information*/
  for (auto& i : _threadPool) {
    if (i.joinable())
      i.join();
  }

  _threadPoolMutex.unlock();

  slg::log->info("End collection metrics info");
}

void MultiThreadController::addMetric(std::shared_ptr<Metric>&& metric) {
  while (!_queueMutex.try_lock())
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

  _metricsQueue.push_back(std::move(metric));
  _queueMutex.unlock();

  slg::log->debug("Add new metric to MultiThreadController");
}

void MultiThreadController::removeMetricByName(std::string metricName) {
  while (!_queueMutex.try_lock())
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

  _metricsQueue.remove_if([metricName](const std::shared_ptr<Metric>& metric) {
    return metric->getName() == metricName;
  });
  _queueMutex.unlock();
}

MultiThreadController::~MultiThreadController() {
  while (!_threadPoolMutex.try_lock()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  for (auto& i : _threadPool) {
    if (i.joinable())
      i.join();
  }

  _threadPoolMutex.unlock();
}
}  // namespace mes