#include <iostream>
#include <thread>
#include "MetricStreamClient.h"
#include "example-metrics/CPUMetric.h"
#include "example-metrics/MemoryMetric.h"

int main(int argc, char* argv[]) {
  mes::MetricStreamClient client(5000, 3, "test.txt");
  std::shared_ptr<mes::Metric> metric1 = std::make_shared<CPUMetric>();
  std::shared_ptr<mes::Metric> metric2 = std::make_shared<MemoryMetric>();
  client.startStream();

  std::this_thread::sleep_for(std::chrono::milliseconds(15000));
  client.setTimeout(2500);
  client.addMetricToStream(std::move(metric1));
  std::this_thread::sleep_for(std::chrono::milliseconds(15000));
  client.addMetricToStream(std::move(metric2));
  std::this_thread::sleep_for(std::chrono::milliseconds(15000));
  client.removeMetric("CPU");
  std::this_thread::sleep_for(std::chrono::milliseconds(15000));
  client.stopStream();
}