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
  std::cout << message << std::endl;
  if (path == "")
    return;
  std::ofstream file;
  file.open(path, std::ios::app);
  file << message << std::endl;
  file.close();
}
} // namespace bfb