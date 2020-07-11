#include "okapiUtil.hpp"

namespace bfb {
std::unique_ptr<okapi::SettledUtil>
createSettledUtil(double iatTargetError, double iatTargetDerivative, okapi::QTime iatTargetTime) {
  return std::make_unique<okapi::SettledUtil>(okapi::TimeUtilFactory::createDefault().getTimer(),
                                              iatTargetError,
                                              iatTargetDerivative,
                                              iatTargetTime);
}
} // namespace bfb