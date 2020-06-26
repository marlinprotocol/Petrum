#pragma once

#include <cstdarg>
#include "tscore/ink_apidefs.h"
#include "tscore/Regression.h"

namespace
{
/** Class to make handling regression tests easier.
    This holds the important regression test values so they don't have to
    be passed repeated.
*/
struct TestBox {
  typedef TestBox self;  ///< Self reference type.
  RegressionTest *_test; ///< The test object.
  int *_status;          ///< Current status pointer.

  /// Construct from @a test object and @a status pointer.
  TestBox(RegressionTest *test, int *status) : _test(test), _status(status) {}
  /// Construct from @a test object, @a status pointer and @a regression status.
  TestBox(RegressionTest *test, int *status, int rstatus) : _test(test), _status(status) { *this = rstatus; }
  /// Check the result and print a message on failure.
  bool check(bool result, char const *fmt, ...) TS_PRINTFLIKE(3, 4);

  /// Directly assign status.
  self &
  operator=(int status)
  {
    *_status = status;
    return *this;
  }
};

bool
TestBox::check(bool result, char const *fmt, ...)
{
  if (!result) {
    static size_t const N = 1 << 16;
    char buffer[N]; // just stack, go big.
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buffer, N, fmt, ap);
    va_end(ap);
    rprintf(_test, "%s\n", buffer);
    *_status = REGRESSION_TEST_FAILED;
  }
  return result;
}
} // namespace
