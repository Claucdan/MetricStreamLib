#ifndef METRICSTREAMLIB_CPUMETRIC_H
#define METRICSTREAMLIB_CPUMETRIC_H

#include <random>

#include "Metric.h"

class CPUMetric : public mes::Metric {
 private:
  int _cpuReit = 0;

 protected:
  std::string getMetric() override;

  void reset() override;

 public:
  CPUMetric() = default;

  std::string getName() const override;
};

#endif  //METRICSTREAMLIB_CPUMETRIC_H
