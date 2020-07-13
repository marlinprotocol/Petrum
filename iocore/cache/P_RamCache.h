#pragma once

#include "I_Cache.h"

// Generic Ram Cache interface

struct RamCache {
  // returns 1 on found/stored, 0 on not found/stored, if provided auxkey1 and auxkey2 must match
  virtual int get(CryptoHash *key, Ptr<IOBufferData> *ret_data, uint32_t auxkey1 = 0, uint32_t auxkey2 = 0) = 0;
  virtual int put(CryptoHash *key, IOBufferData *data, uint32_t len, bool copy = false, uint32_t auxkey1 = 0,
                  uint32_t auxkey2 = 0)                                                                     = 0;
  virtual int fixup(const CryptoHash *key, uint32_t old_auxkey1, uint32_t old_auxkey2, uint32_t new_auxkey1,
                    uint32_t new_auxkey2)                                                                   = 0;
  virtual int64_t size() const                                                                              = 0;

  virtual void init(int64_t max_bytes, Vol *vol) = 0;
  virtual ~RamCache(){};
};

RamCache *new_RamCacheLRU();
RamCache *new_RamCacheCLFUS();
