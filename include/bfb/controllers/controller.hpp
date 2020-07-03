#pragma once

namespace bfb {
class Controller {
  public:
  virtual ~Controller() = default;
  virtual void setReference(const double iReference) = 0;
  virtual double step(const double state) = 0;
  virtual double getOutput() const = 0;
  virtual bool isSettled(const double state) = 0;
  virtual void reset() = 0;
};
} // namespace bfb