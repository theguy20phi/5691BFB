#include "issue.hpp"

namespace bfb {
DEFINE_SEVERITY(Low, 1, "L");
DEFINE_SEVERITY(Medium, 2, "M");
DEFINE_SEVERITY(High, 3, "H");

std::vector<Issue> Issue::issueList{};

Issue::Issue(const std::string &iDescription, std::shared_ptr<SeverityLevel> iSeverity)
  : description(iDescription), severity(iSeverity) {
  issueList.push_back(*this);
  std::sort(issueList.begin(), issueList.end(), [](const Issue &a, const Issue &b) -> bool {
    return a.getSeverity()->getNumeric() > b.getSeverity()->getNumeric();
  });
}

std::string Issue::getDescription() const {
  return description;
}

std::shared_ptr<SeverityLevel> Issue::getSeverity() const {
  return severity;
}

std::vector<Issue> Issue::getIssueList() {
  return issueList;
}

#ifdef TESTING
DEFINE_SEVERITY(Test, -1, "T");
DEFINE_TEST(issueTest)
static const Issue testIssue{"Test", makeTest()};
IS_EQUAL(Issue::getIssueList().back().getDescription(), std::string("Test"))
IS_EQUAL(Issue::getIssueList().back().getSeverity()->getString(), "T")
END_TEST
#endif
} // namespace bfb