#pragma once

#include <string>

namespace atscppapi
{
/**
 * An enumeration of all available Http Methods.
 */
enum HttpMethod {
  HTTP_METHOD_UNKNOWN = 0,
  HTTP_METHOD_GET,
  HTTP_METHOD_POST,
  HTTP_METHOD_HEAD,
  HTTP_METHOD_CONNECT,
  HTTP_METHOD_DELETE,
  HTTP_METHOD_OPTIONS,
  HTTP_METHOD_PURGE,
  HTTP_METHOD_PUT,
  HTTP_METHOD_TRACE,
  HTTP_METHOD_PUSH
};

/**
 * An array of printable strings representing of the HttpMethod
 * \code
 * cout << HTTP_METHOD_STRINGS[HTTP_METHOD_GET] << endl;
 * \endcode
 */
extern const std::string HTTP_METHOD_STRINGS[];
} // namespace atscppapi
