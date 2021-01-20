#pragma once

#include "landmarker.hpp"

namespace bfb {
class NullLandmarker : public Landmarker {
  public:
  void updatePose(const Pose &iReferencePose) override;
  void setPose(const Pose &iReferencePose) override;
  bool isReading() override;
  Pose getPose() override;
  void reset() override;

  private:
  Pose pose;
};
} // namespace bfb