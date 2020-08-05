#include "controller.hpp"

namespace bfb {
void Controller::setReference(const double iReference) {
  reference = iReference;
  controllerLog << ("Controller set reference to: " + std::to_string(reference));
}

double Controller::getReference() const {
  return reference;
}

double Controller::getOutput() const {
  return output;
}

Logger Controller::controllerLog{};
} // namespace bfb