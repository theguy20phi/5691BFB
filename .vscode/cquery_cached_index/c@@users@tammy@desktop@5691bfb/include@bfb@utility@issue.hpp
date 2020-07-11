/**
 * @file issue.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "test.hpp"
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#define DECLARE_SEVERITY(a)                                                                        \
  class a : public SeverityLevel {                                                                 \
    int getNumeric() const override;                                                               \
    std::string getString() const override;                                                        \
  };

#define DEFINE_SEVERITY(a, b, c)                                                                   \
  int Issue::a::getNumeric() const {                                                               \
    return b;                                                                                      \
  }                                                                                                \
  std::string Issue::a::getString() const {                                                        \
    return c;                                                                                      \
  }

namespace bfb {
/**
 * @brief Issue provides a basis for managing and logging problems that may occur during driving.
 * Issues should be constructed as static and constant, in the event the problem occurs.
 * Issues are logged in vector that can be globally read from, but only modified by Issue objects.
 * Issues are sorted by highest to lowest severity when logged.
 *
 */
class Issue {
  public:
  /**
   * @brief Provides a parent class for many SeverityLevel subclasses.
   *
   */
  class SeverityLevel {
    public:
    /**
     * @brief Gets the numeric value of the severity level.
     *
     * @return int
     */
    virtual int getNumeric() const = 0;

    /**
     * @brief Gets the string representation of the severity level.
     *
     * @return std::string
     */
    virtual std::string getString() const = 0;
  };
  DECLARE_SEVERITY(Low)
  DECLARE_SEVERITY(Medium)
  DECLARE_SEVERITY(High)
#ifdef TESTING
  DECLARE_SEVERITY(Test)
#endif

  /**
   * @brief Constructs an Issue object, logging the Issue to the list of issues.
   * In order to avoid repeated logging, construct as a static const (static const Issue
   * aIssue{...}).
   *
   * @param iDescription
   * @param iSeverity
   */
  Issue(const std::string &iDescription, std::shared_ptr<SeverityLevel> iSeverity);

  /**
   * @brief Gets the sorted list of issues.
   *
   * @return std::vector<Issue>
   */
  static std::vector<Issue> getIssueList();

  /**
   * Gets the description for the issue.
   *
   * @return std::string
   */
  std::string getDescription() const;

  /**
   * Gets the severity for the issue.
   *
   * @return std::shared_ptr<SeverityLevel>
   */
  std::shared_ptr<SeverityLevel> getSeverity() const;

  private:
  static std::vector<Issue> issueList;
  // not const because of sort implications, objects should be constant anyways
  std::string description;
  std::shared_ptr<SeverityLevel> severity;
};

#ifdef TESTING
DECLARE_TEST(issueTest)
#endif
} // namespace bfb