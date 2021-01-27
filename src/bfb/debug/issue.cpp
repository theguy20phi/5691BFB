#include "issue.hpp"

namespace bfb {
std::vector<Issue> Issue::issueList{};

Issue::Issue(const std::string &iDescription, const Severity::SeverityLevel &iSeverity)
  : description(iDescription), severity(iSeverity) {
  issueList.push_back(*this);
  std::sort(issueList.begin(), issueList.end(), [](const Issue &a, const Issue &b) {
    return a.getSeverity().numeric > b.getSeverity().numeric;
  });
}

std::string Issue::getDescription() const {
  return description;
}

Severity::SeverityLevel Issue::getSeverity() const {
  return severity;
}

std::vector<Issue> Issue::getIssueList() {
  return issueList;
}
} // namespace bfb