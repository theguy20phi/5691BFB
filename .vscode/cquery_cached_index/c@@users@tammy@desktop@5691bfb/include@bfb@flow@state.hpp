/**
 * @file state.hpp
 * @author Braden Pierce
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/robot.hpp"
#include <memory>

#define DECLARE_STATE(a, b, c)                                                                     \
  class a : public b<c> {                                                                          \
    public:                                                                                        \
    using b<c>::b;                                                                                 \
    bool step(const std::shared_ptr<Robot> &robot) const override;                                 \
  };                                                                                               \
  std::shared_ptr<a> make##a(const c &c##Param)

#define DEFINE_STATE(a, c)                                                                         \
  std::shared_ptr<a> make##a(const c &c##param) {                                                  \
    return std::make_shared<a>(c##param);                                                          \
  }                                                                                                \
  bool a::step(const std::shared_ptr<Robot> &robot) const

namespace bfb {
/**
 * @brief Provides a parent, template class to be subclassed for a variety of states to be used in
 * tandem with a StateMachine. Subclasses can define their own parameters via templating.
 *
 * @tparam ParameterType
 */
template <typename ParameterType> class State {
  public:
  /**
   * @brief Construct a new State object
   *
   * @param iParameter
   */
  State(const ParameterType &iParameter) : parameter(iParameter) {
  }
  virtual bool step(const std::shared_ptr<Robot> &robot) const = 0;

  protected:
  const ParameterType parameter;
};
} // namespace bfb