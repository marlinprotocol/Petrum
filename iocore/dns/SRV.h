#pragma once

#include <vector>
#include "tscore/ink_platform.h"
#include "I_HostDBProcessor.h"

struct HostDBInfo;

#define RAND_INV_RANGE(r) ((int)((RAND_MAX + 1) / (r)))

struct SRV {
  unsigned int weight   = 0;
  unsigned int port     = 0;
  unsigned int priority = 0;
  unsigned int ttl      = 0;
  unsigned int host_len = 0;
  unsigned int key      = 0;
  char host[MAXDNAME]   = {0};
};

inline bool
operator<(const SRV &left, const SRV &right)
{
  // lower priorities first, then the key
  return (left.priority == right.priority) ? (left.key < right.key) : (left.priority < right.priority);
}

struct SRVHosts {
  unsigned int srv_hosts_length = 0;
  std::vector<SRV> hosts;
};
