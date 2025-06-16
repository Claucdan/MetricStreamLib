#include "CPUMetric.h"

std::string CPUMetric::getName() const {
  return "CPU";
}

std::string CPUMetric::getMetric() {
  std::random_device device;
  std::mt19937 gen(device());
  std::uniform_int_distribution<> distr(1, 100);

  _cpuReit = distr(gen);
  return std::to_string(_cpuReit);
}

void CPUMetric::reset() {
  _cpuReit = 0;
}