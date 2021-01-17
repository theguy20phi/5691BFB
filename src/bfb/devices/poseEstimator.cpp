#include "poseEstimator.hpp"

namespace bfb {
Pose operator+(const Pose &lhs, const Pose &rhs) {
  return Pose{lhs.x + rhs.x, lhs.y + rhs.y, lhs.h + rhs.h};
}

Pose operator-(const Pose &lhs, const Pose &rhs) {
  return Pose{lhs.x - rhs.x, lhs.y - rhs.y, lhs.h - rhs.h};
}

Pose operator*(const Pose &lhs, double factor) {
  return Pose{lhs.x * factor, lhs.y * factor, lhs.h * factor};
}

Pose operator/(const Pose &lhs, double denom) {
  return Pose{lhs.x / denom, lhs.y / denom, lhs.h / denom};
}

bool operator == (const Pose &lhs, const Pose &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.h == rhs.h;
}

bool operator != (const Pose &lhs, const Pose &rhs) {
    return !(lhs == rhs);
}
} // namespace bfb