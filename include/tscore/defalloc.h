#pragma once

#include "tscore/ink_memory.h"

class DefaultAlloc
{
public:
  static void *
  alloc(int s)
  {
    return ats_malloc(s);
  }
  static void
  free(void *p)
  {
    ats_free(p);
  }
};
