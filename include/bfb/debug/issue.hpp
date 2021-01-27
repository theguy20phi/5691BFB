/**
 * @file issue.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

namespace bfb {
namespace Severity {
/**
 * @brief Used to sort and display issues of varying severity.
 *
 */
struct SeverityLevel {
  int numeric;
  char alpha;
};
constexpr SeverityLevel Low{1, 'L'};
constexpr SeverityLevel Medium{2, 'M'};
constexpr SeverityLevel High{3, 'H'};
#ifdef TESTING
constexpr SeverityLevel Test{INT32_MIN, 'T'};
#endif
} // namespace Severity

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
   * @brief Constructs an Issue object, logging the Issue to the list of issues.
   * In order to avoid repeated logging, construct as a static const (static const Issue
   * aIssue{...}).
   *
   * @param iDescription
   * @param iSeverity
   */
  Issue(const std::string &iDescription, const Severity::SeverityLevel &iSeverity);

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
  Severity::SeverityLevel getSeverity() const;

  private:
  static std::vector<Issue> issueList;
  std::string description;
  Severity::SeverityLevel severity;
};
} // namespace bfb