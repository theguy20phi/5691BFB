/**
 * Issue provides a basis for managing and logging problems that may occur during driving.
 * Issues should be constructed as static and constant, in the event the problem occurs.
 * Issues are logged in vector that can be globally read from, but only modified by Issue objects.
 * Issues are sorted by highest to lowest severity when logged.
 *
 * @author Braden Pierce
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
class Issue {
  public:
  class SeverityLevel {
    public:
    /**
     * Gets the numeric value of the severity level.
     *
     * @return The numeric value of the severity level.
     */
    virtual int getNumeric() const = 0;

    /**
     * Gets the string representation of the severity level.
     *
     * @return The string representation of the severity level.
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
   * Constructs an Issue object, logging the Issue to the list of issues.
   * In order to avoid repeated logging, construct as a static const (static const Issue
   * aIssue{...}).
   *
   * @param iDescription The description of the issue.
   * @param iSeverity The severity of the issue.
   */
  Issue(const std::string &iDescription, std::shared_ptr<SeverityLevel> iSeverity);

  /**
   * Gets the sorted list of issues.
   *
   * @return The sorted list of issues.
   */
  static std::vector<Issue> getIssueList();

  /**
   * Compares two issues by severity.
   * Used for sorting.
   *
   * @param a The first issue.
   * @param b the second issue.
   * @return If a is greater than b.
   */
  static bool compareIssues(const Issue &a, const Issue &b);

  /**
   * Gets the description for the issue.
   *
   * @return The description for the issue.
   */
  std::string getDescription() const;

  /**
   * Gets the severity for the issue.
   *
   * @return The severity for the issue.
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