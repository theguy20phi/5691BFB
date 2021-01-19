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
class Landmarker {
  public:
  virtual void update(const Pose &iReferencePose) = 0;
  virtual void setReference(const Pose &iReferencePose) = 0;
  virtual bool isReading() = 0;
  virtual Pose getReading() = 0;
  virtual void reset() = 0;
};

using LandmarkerPtr = std::shared_ptr<Landmarker>;
} // namespace bfb