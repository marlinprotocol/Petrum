#pragma once

#include "tscore/ink_config.h"

#ifdef HAVE_PCRE_PCRE_H
#include <pcre/pcre.h>
#else
#include <pcre.h>
#endif

enum REFlags {
  RE_CASE_INSENSITIVE = 0x0001, // default is case sensitive
  RE_UNANCHORED       = 0x0002, // default (for DFA) is to anchor at the first matching position
  RE_ANCHORED         = 0x0004, // default (for Regex) is unanchored
};

class Regex
{
public:
  Regex() : regex(nullptr), regex_extra(nullptr) {}
  bool compile(const char *pattern, const unsigned flags = 0);
  // It is safe to call exec() concurrently on the same object instance
  bool exec(const char *str);
  bool exec(const char *str, int length);
  bool exec(const char *str, int length, int *ovector, int ovecsize);
  int get_capture_count();
  ~Regex();

private:
  pcre *regex;
  pcre_extra *regex_extra;
};

typedef struct __pat {
  int _idx;
  Regex *_re;
  char *_p;
  __pat *_next;
} dfa_pattern;

class DFA
{
public:
  DFA() : _my_patterns(nullptr) {}
  ~DFA();

  int compile(const char *pattern, unsigned flags = 0);
  int compile(const char **patterns, int npatterns, unsigned flags = 0);

  int match(const char *str) const;
  int match(const char *str, int length) const;

private:
  dfa_pattern *build(const char *pattern, unsigned flags = 0);

  dfa_pattern *_my_patterns;
};
