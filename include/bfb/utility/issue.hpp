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
    virtual int getNumeric() const = 0;
    virtual std::string getString() const = 0;
  };
  DECLARE_SEVERITY(Low)
  DECLARE_SEVERITY(Medium)
  DECLARE_SEVERITY(High)
#ifdef TESTING
  DECLARE_SEVERITY(Test)
#endif

  Issue(const std::string &iDescription, std::shared_ptr<SeverityLevel> iSeverity);
  static std::vector<Issue> getIssueList();
  static bool compareIssues(const Issue &a, const Issue &b);
  std::string getDescription() const;
  std::shared_ptr<SeverityLevel> getSeverity() const;

  private:
  static std::vector<Issue> issueList;
  // not const because of std::sort implications
  std::string description;
  std::shared_ptr<SeverityLevel> severity;
};

#ifdef TESTING
DECLARE_TEST(issueTest)
#endif
} // namespace bfb