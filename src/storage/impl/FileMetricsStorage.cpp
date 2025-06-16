#include "FileMetricsStorage.h"

#include <utility>

namespace mes {

FileMetricsStorage::FileMetricsStorage(std::string filename)
    : _filename(std::move(filename)) {}

void FileMetricsStorage::uploadBuffer(std::string time) {
  try {
    while (!_fileMutex.try_lock())
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    slg::log->debug("Lock FileMetricsStorage file mutex for upload buffer");

    _file.open(_filename, std::ios::app);
    slg::log->debug("Open ofstream for storage");

    _file << time << " ";

    while (!_bufferMutex.try_lock())
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    while (!_buffer.empty()) {
      auto tmp = _buffer.front();
      _buffer.pop();
      _file << '"' << tmp.first << '"' << " ";
      _file << tmp.second << " ";
    }
    _bufferMutex.unlock();

    _file << "\n";

    slg::log->debug("Close ofstream for storage");
    _file.close();
    _fileMutex.unlock();
    slg::log->info("FileMetricStorage upload buffer to file storage");

  } catch (std::exception e) {
    slg::log->error(e.what());
  }
}

void FileMetricsStorage::addMetricToBuffer(std::string name,
                                           std::string value) {
  while (!_bufferMutex.try_lock())
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

  slg::log->debug("Lock FileMetricsStorage buffer mutex for add");
  _buffer.emplace(name, value);
  _bufferMutex.unlock();
  slg::log->debug("Unlock FileMetricsStorage buffer mutex");
}

FileMetricsStorage::~FileMetricsStorage() {
  while (!_fileMutex.try_lock())
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  _file.close();
  _fileMutex.unlock();
}

}  // namespace mes