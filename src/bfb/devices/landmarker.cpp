#include "landmarker.hpp"

namespace bfb {
Landmarker::Landmarker(const Lines &iLines, const Pose &iRelativePose, uint8_t port, int iThreshold)
  : lines(iLines), relativePose(iRelativePose), lineSensor(port), threshold(iThreshold) {
}

Pose Landmarker::getPose() {
  const Line closestLine{getClosestLine()};
  calculatePose(closestLine);
  return pose;
}

Line Landmarker::getClosestLine() const {
  Line closestLine{lines[0]};
  double shortestDistance{calculateDistance(closestLine)};
  for (Line line : lines) {
    const double distance{calculateDistance(line)};
    if (distance >= shortestDistance)
      continue;
    closestLine = line;
    shortestDistance = distance;
  }
  return closestLine;
}

double Landmarker::calculateDistance(const Line &line) const {
  if (line.orientation == Orientation::horizontal)
    return okapi::abs(line.distance - pose.y).convert(okapi::meter);
  else
    return okapi::abs(line.distance - pose.x).convert(okapi::meter);
}

void Landmarker::calculatePose(const Line &line) {
  if (!seeLine())
    return;
  if (line.orientation == Orientation::horizontal)
    pose = {pose.x, line.distance - relativePose.y * cos(pose.h), pose.h};
  else
    pose = {line.distance - relativePose.x * sin(pose.h), pose.y, pose.h};
}

bool Landmarker::seeLine() {
  if (lineSensor.get_value() < threshold)
    return true;
  return false;
}

void Landmarker::setPose(const Pose &iPose) {
  pose = iPose;
}

void Landmarker::reset() {
  pose = {0.0_in, 0.0_in, 0.0_rad};
}

void Landmarker::updatePose() {
  getPose();
}

bool Landmarker::isReady() {
  return seeLine();
}
} // namespace bfb