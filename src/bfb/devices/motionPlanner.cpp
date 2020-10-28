#include "motionPlanner.hpp"

namespace bfb {
MotionPlanner::MotionPlanner(const MotionInfo &iConstraints, double iDt)
  : constraints(iConstraints), dt(iDt) {
}

void MotionPlanner::setTarget(double iTarget) {
  target = iTarget;
}

MotionPlanner::MotionInfo MotionPlanner::generateNext(const MotionInfo &current) {
  double A{calculateA(current)};
  double V{current.V + A * dt};
  if (isAlmostZero(target - current.P))
    V = 0;
  double P{current.P + current.V * dt + 0.5 * A * dt * dt};
  step = MotionInfo{P, V, A};
  return step;
}

MotionPlanner::MotionInfo MotionPlanner::getStep() {
  return step;
}

double MotionPlanner::calculateA(const MotionInfo &current) {
  double distance{target - current.P};
  int direction{sign(distance)};
  if (isAlmostZero(distance))
    return 0;
  else if (0 >= current.V * current.V / (2 * -constraints.A) + fabs(distance))
    return -direction * constraints.A;
  else if (fabs(current.V) < constraints.V)
    return direction * constraints.A;
  return 0;
}
} // namespace bfb