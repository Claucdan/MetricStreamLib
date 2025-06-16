#ifndef METRICSTREAMLIB_MEMORYMETRIC_H
#define METRICSTREAMLIB_MEMORYMETRIC_H

#include "Metric.h"

#ifdef WIN32

#include <windows.h>
#include <psapi.h>
#include <sstream>
#include <string>

#pragma comment(lib, "psapi.lib")

#else
#include <fstream>
#include <iostream>
#include <unordered_map>
#endif

class MemoryMetric : public mes::Metric {
 protected:
  std::string getMetric() override;

  void reset() override;

 public:
  MemoryMetric() = default;

  std::string getName() const override;
};

#endif  //METRICSTREAMLIB_MEMORYMETRIC_H
