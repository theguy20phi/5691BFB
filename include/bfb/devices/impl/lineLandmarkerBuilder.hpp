#pragma once

#include "bfb/devices/lineLandmarker.hpp"

namespace bfb {
class LineLandmarkerBuilder {
  public:
  LineLandmarkerBuilder();
  LandmarkerPtr build() const;
  LineLandmarkerBuilder withLine(okapi::QLength distance, Orientation orientation);
  LineLandmarkerBuilder withRelativePose(const Pose &iRelativePose);
  LineLandmarkerBuilder withPort(uint8_t iPort);
  LineLandmarkerBuilder withThreshold(int iThreshold);

  private:
  Lines lines;
  Pose relativePose;
  uint8_t port;
  int threshold = 500;
};
} // namespace bfb