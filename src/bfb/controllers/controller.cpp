#include "controller.hpp"

namespace bfb {
void Controller::setReference(const double iReference) {
  reference = iReference;
}

double Controller::getReference() const {
  return reference;
}

double Controller::getOutput() const {
  return output;
}
} // namespace bfb