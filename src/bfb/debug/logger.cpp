#include "logger.hpp"

namespace bfb {
void Logger::disable() {
  disabled = true;
}

void Logger::setPath(const std::string &iPath) {
  path = iPath;
}

void Logger::operator<<(const std::string &message) const {
  if (disabled)
    return;
  std::cout << message;
  if (path == "")
    return;
  std::ofstream file;
  file.open(path, std::ios::app);
  file << message;
  file.close();
}
} // namespace bfb