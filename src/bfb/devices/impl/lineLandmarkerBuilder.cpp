#include "lineLandmarkerBuilder.hpp"

namespace bfb {
LineLandmarkerBuilder::LineLandmarkerBuilder() {
}

LineLandmarker LineLandmarkerBuilder::build() const {
  return LineLandmarker{lines, relativePose, port, threshold};
}

LineLandmarkerBuilder LineLandmarkerBuilder::withLine(okapi::QLength distance,
                                                      Orientation orientation) {
  lines.push_back({distance, orientation});
  return *this;
}

LineLandmarkerBuilder LineLandmarkerBuilder::withRelativePose(const Pose &iRelativePose) {
  relativePose = iRelativePose;
  return *this;
}

LineLandmarkerBuilder LineLandmarkerBuilder::withPort(uint8_t iPort) {
  port = iPort;
  return *this;
}

LineLandmarkerBuilder LineLandmarkerBuilder::withThreshold(int iThreshold) {
  threshold = iThreshold;
  return *this;
}
} // namespace bfb