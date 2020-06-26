#pragma once

// The SourceLocation class wraps up a source code location, including
// file name, function name, and line number, and contains a method to
// format the result into a string buffer.

#define MakeSourceLocation() SourceLocation(__FILE__, __FUNCTION__, __LINE__)

class SourceLocation
{
public:
  const char *file = nullptr;
  const char *func = nullptr;
  int line         = 0;

  SourceLocation()                          = default;
  SourceLocation(const SourceLocation &rhs) = default;

  SourceLocation(const char *_file, const char *_func, int _line) : file(_file), func(_func), line(_line) {}

  bool
  valid() const
  {
    return file && line;
  }

  SourceLocation &
  operator=(const SourceLocation &rhs)
  {
    this->file = rhs.file;
    this->func = rhs.func;
    this->line = rhs.line;
    return *this;
  }

  char *str(char *buf, int buflen) const;
};
