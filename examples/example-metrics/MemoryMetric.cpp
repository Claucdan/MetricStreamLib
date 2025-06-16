#include "MemoryMetric.h"

std::string MemoryMetric::getName() const {
  return "Used RAM (MB)";
}

std::string MemoryMetric::getMetric() {
#ifdef WIN32
  MEMORYSTATUSEX memInfo;
  memInfo.dwLength = sizeof(MEMORYSTATUSEX);
  GlobalMemoryStatusEx(&memInfo);

  DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
  DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
  std::stringstream ss;
  ss << (physMemUsed / (1024 * 1024));
  return ss.str();
#else
  std::ifstream file("/proc/meminfo");
  std::unordered_map<std::string, unsigned long long> memData;
  std::string line;

  while (std::getline(file, line)) {
    std::string key;
    unsigned long long value;
    size_t colonPos = line.find(':');
    if (colonPos != std::string::npos) {
      key = line.substr(0, colonPos);
      std::string valueStr = line.substr(colonPos + 1);
      valueStr.erase(0, valueStr.find_first_not_of(" \t"));
      valueStr = valueStr.substr(0, valueStr.find(" kB"));
      value = std::stoull(valueStr);  // Переводим из kB в байты
      memData[key] = value;
    }
  }
  unsigned long long totalMem = memData["MemTotal"];
  unsigned long long freeMem = memData["MemFree"];
  unsigned long long usedMem = totalMem - freeMem;
  return std::to_string(usedMem / 1024);
#endif
}

void MemoryMetric::reset() {}