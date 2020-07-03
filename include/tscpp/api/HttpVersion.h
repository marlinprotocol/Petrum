#pragma once

#include <string>

namespace atscppapi
{
/**
 * An enumeration of all available Http Versions.
 */
enum HttpVersion {
  HTTP_VERSION_UNKNOWN = 0,
  HTTP_VERSION_0_9,
  HTTP_VERSION_1_0,
  HTTP_VERSION_1_1,
};

/**
 * An array of printable strings representing of the HttpVersion
 * \code
 * cout << HTTP_VERSION_STRINGS[HTTP_VERSION_1_1] << endl;
 * \endcode
 */
extern const std::string HTTP_VERSION_STRINGS[];
} // namespace atscppapi
