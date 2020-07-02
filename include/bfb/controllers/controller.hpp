#pragma once

namespace bfb {
class Controller {
  public:
  virtual ~Controller() = default;
  virtual void setReference(double iReference);
  virtual double step(double state);
  virtual double getOutput() const;
  virtual bool isSettled(double state);
  virtual void reset();
};
} // namespace bfb