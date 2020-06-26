#pragma once

#include "tscore/ink_defs.h"
#include "tscore/ink_apidefs.h"

class InkRand
{
public:
  InkRand(uint64_t d);

  void seed(uint64_t d);
  inkcoreapi uint64_t random();
  double drandom();

private:
  uint64_t mt[312];
  int mti;
};

inline int
ink_rand_r(uint32_t *p)
{
  return (((*p) = (*p) * 1103515245 + 12345) % ((uint32_t)0x7fffffff + 1));
}
