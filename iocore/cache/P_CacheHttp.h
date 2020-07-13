#pragma once

#include "P_CacheArray.h"
#include "HTTP.h"
#include "URL.h"

typedef URL CacheURL;
typedef HTTPHdr CacheHTTPHdr;
typedef HTTPInfo CacheHTTPInfo;

#define OFFSET_BITS 24
enum {
  OWNER_NONE  = 0,
  OWNER_CACHE = 1,
  OWNER_HTTP  = 2,
};

struct vec_info {
  CacheHTTPInfo alternate;
};

struct CacheHTTPInfoVector {
  void *magic;

  CacheHTTPInfoVector();
  ~CacheHTTPInfoVector();

  int
  count()
  {
    return xcount;
  }
  int insert(CacheHTTPInfo *info, int id = -1);
  CacheHTTPInfo *get(int idx);
  void detach(int idx, CacheHTTPInfo *r);
  void remove(int idx, bool destroy);
  void clear(bool destroy = true);
  void
  reset()
  {
    xcount = 0;
    data.clear();
  }
  void print(char *buffer, size_t buf_size, bool temps = true);

  int marshal_length();
  int marshal(char *buf, int length);
  uint32_t get_handles(const char *buf, int length, RefCountObj *block_ptr = nullptr);
  int unmarshal(const char *buf, int length, RefCountObj *block_ptr);

  CacheArray<vec_info> data;
  int xcount;
  Ptr<RefCountObj> vector_buf;
};

TS_INLINE CacheHTTPInfo *
CacheHTTPInfoVector::get(int idx)
{
  ink_assert(idx >= 0);
  ink_assert(idx < xcount);
  return &data[idx].alternate;
}
