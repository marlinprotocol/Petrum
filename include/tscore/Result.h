#pragma once

#include "TextBuffer.h"

// Result is simple error object that carries a success/fail status and
// a corresponding error message for the failure case. It is a simplified
// form of Rust's Result object in that we don't carry a return value for
// the success case. Arguably it ought to just be Error(), but Diags.h
// already owns that name.

#include <utility>
struct Result {
  Result() {}

  Result &
  operator=(Result &&other)
  {
    if (this != &other) {
      buf = std::move(other.buf);
    }
    return *this;
  }

  Result(Result &&other) { *this = std::move(other); }

  bool
  failed() const
  {
    return !buf.empty();
  }

  const char *
  message() const
  {
    return buf.bufPtr();
  }

  static Result
  ok()
  {
    return Result();
  }

  static Result
  failure(const char *fmt, ...) TS_PRINTFLIKE(1, 2)
  {
    Result result;
    va_list ap;

    va_start(ap, fmt);
    result.buf.vformat(fmt, ap);
    va_end(ap);

    return result;
  }

private:
  TextBuffer buf;
};
