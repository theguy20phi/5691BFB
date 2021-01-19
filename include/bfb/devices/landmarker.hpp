/**
 * @file landermarker.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "bfb/utility/literals.hpp"
#include "poseEstimator.hpp"
#include "pros/adi.hpp"
#include <vector>

using namespace bfb::literals;
using namespace okapi::literals;

namespace bfb {
enum class Orientation { vertical, horizontal };

struct Line {
  okapi::QLength distance;
  Orientation orientation;
};

using Lines = std::vector<Line>;
class Landmarker : public PoseEstimator {
  public:
  Landmarker(const Lines &iLines, const Pose &iRelativePose, uint8_t port, int iThreshold = 500);
  Pose getPose() override;
  void setPose(const Pose &iPose) override;
  void reset() override;
  void updatePose();
  bool isReady();

  private:
  bool seeLine();
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

using LandmarkerPtr = std::shared_ptr<Landmarker>;
} // namespace bfb