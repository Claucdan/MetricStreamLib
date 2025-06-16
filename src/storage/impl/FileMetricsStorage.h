#ifndef METRICSTREAM_FILEMETRICSSTORAGE_H
#define METRICSTREAM_FILEMETRICSSTORAGE_H

#include <fstream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "ConsoleLog.h"
#include "MetricsStorage.h"

namespace mes {

/**
 * @class FileMetricsStorage
 * @implements MetricsStorage
 * @brief Implements MetricsStorage with the storage presented as a file
 */
class FileMetricsStorage : public MetricsStorage {
 private:
  /// @brief mutex for buffer
  std::mutex _bufferMutex;
  /// @brief mutex for file stream
  std::mutex _fileMutex;

  /// @brief file name
  std::string _filename;
  /// @brief file stream to storage
  std::ofstream _file;

  /// @buffer buffer for metrics and their values
  std::queue<std::pair<std::string, std::string>> _buffer;

 public:
  FileMetricsStorage() = delete;

  /**
   * @brief Default constructor
   * @param filename the name of the file where the storage will be located
   */
  explicit FileMetricsStorage(std::string filename);

  void uploadBuffer(std::string time) override;

  void addMetricToBuffer(std::string name, std::string value) override;

  /**
   * @brief Default destructor
   * @details Close file stream
   */
  ~FileMetricsStorage() override;
};

}  // namespace mes

#endif  //METRICSTREAM_FILEMETRICSSTORAGE_H
