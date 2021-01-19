#pragma once

#include "landmarker.hpp"

namespace bfb {
enum class Orientation { vertical, horizontal };

struct Line {
  okapi::QLength distance;
  Orientation orientation;
};

using Lines = std::vector<Line>;

class LineLandmarker : public Landmarker {
  public:
  LineLandmarker(const Lines &iLines,
                 const Pose &iRelativePose,
                 uint8_t port,
                 int iThreshold = 500);
  void update(const Pose &iReferencePose) override;
  void setReference(const Pose &iReferencePose) override;
  bool isReading() override;
  Pose getReading() override;
  void reset() override;

  private:
  Line getClosestLine() const;
  double calculateDistance(const Line &line) const;
  void calculatePose(const Line &line);

  private:
  Pose pose{0.0_in, 0.0_in, 0.0_rad};
  const Pose relativePose;
  const Lines lines;
  const int threshold;
  pros::ADILineSensor lineSensor;
};
} // namespace bfb