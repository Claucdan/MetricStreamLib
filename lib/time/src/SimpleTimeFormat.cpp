#include "SimpleTimeFormat.h"

namespace stf {

std::string getNowTime() {
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  auto since_epoch = now.time_since_epoch();
  auto ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch) % 1000;

  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
  ss << "." << std::setfill('0') << std::setw(3) << ms.count();

  return ss.str();
}

}  // namespace stf
