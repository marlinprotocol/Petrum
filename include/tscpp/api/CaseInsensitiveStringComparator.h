#pragma once

#include <string>

namespace atscppapi
{
/**
 * @brief A case insensitive comparator that can be used with standard library containers.
 *
 * The primary use for this class is to make all Headers case insensitive.
 */
class CaseInsensitiveStringComparator
{
public:
  /**
   * @return true if lhs is lexicographically "less-than" rhs; meant for use in std::map or other standard library containers.
   */
  bool operator()(const std::string &lhs, const std::string &rhs) const;

  /**
   * @return numerical value of lexicographical comparison a la strcmp
   */
  int compare(const std::string &lhs, const std::string &rhs) const;
};
} // namespace atscppapi
