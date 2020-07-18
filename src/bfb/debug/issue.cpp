#include "issue.hpp"

namespace bfb {
std::vector<Issue> Issue::issueList{};

Issue::Issue(const std::string &iDescription, const SeverityLevel &iSeverity)
  : description(iDescription), severity(iSeverity) {
  issueList.push_back(*this);
  auto sortBySeverity = [](const Issue &a, const Issue &b) {
    return a.getSeverity().numeric > b.getSeverity().numeric;
  };
  std::sort(issueList.begin(), issueList.end(), sortBySeverity);
}

std::string Issue::getDescription() const {
  return description;
}

SeverityLevel Issue::getSeverity() const {
  return severity;
}

std::vector<Issue> Issue::getIssueList() {
  return issueList;
}

#ifdef TESTING
DEFINE_TEST(issueTest)
static const Issue testIssue{"Test", Test};
IS_EQUAL(Issue::getIssueList().back().getDescription(), std::string("Test"));
IS_EQUAL(Issue::getIssueList().back().getSeverity().alpha, 'T');
END_TEST
#endif
} // namespace bfb