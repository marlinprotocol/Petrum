#pragma once

#include "Hash.h"
#include <cstdint>
#include <iostream>
#include <map>

/*
  Helper class to be extended to make ring nodes.
 */

struct ATSConsistentHashNode {
  bool available;
  char *name;
};

std::ostream &operator<<(std::ostream &os, ATSConsistentHashNode &thing);

typedef std::map<uint64_t, ATSConsistentHashNode *>::iterator ATSConsistentHashIter;

/*
  TSConsistentHash requires a TSHash64 object

  Caller is responsible for freeing ring node memory.
 */

struct ATSConsistentHash {
  ATSConsistentHash(int r = 1024, ATSHash64 *h = nullptr);
  void insert(ATSConsistentHashNode *node, float weight = 1.0, ATSHash64 *h = nullptr);
  ATSConsistentHashNode *lookup(const char *url = nullptr, ATSConsistentHashIter *i = nullptr, bool *w = nullptr,
                                ATSHash64 *h = nullptr);
  ATSConsistentHashNode *lookup_available(const char *url = nullptr, ATSConsistentHashIter *i = nullptr, bool *w = nullptr,
                                          ATSHash64 *h = nullptr);
  ATSConsistentHashNode *lookup_by_hashval(uint64_t hashval, ATSConsistentHashIter *i = nullptr, bool *w = nullptr);
  ~ATSConsistentHash();

private:
  int replicas;
  ATSHash64 *hash;
  std::map<uint64_t, ATSConsistentHashNode *> NodeMap;
};
