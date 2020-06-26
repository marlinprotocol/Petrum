#pragma once

#include "tscore/ink_mutex.h"
#include <map>
#include <string>

extern int res_track_memory; /* set this to zero to disable resource tracking */
extern uint64_t ssl_memory_allocated;
extern uint64_t ssl_memory_freed;

#define __RES_PATH(x) #x
#define _RES_PATH(x) __RES_PATH(x)
#define RES_PATH(x) x __FILE__ ":" _RES_PATH(__LINE__)

class Resource;

/**
 * Generic class to keep track of memory usage
 * Used to keep track of the location in the code that allocated ioBuffer memory
 */
class ResourceTracker
{
public:
  ResourceTracker(){};
  static void increment(const char *name, const int64_t size);
  static void increment(const void *symbol, const int64_t size, const char *name);
  static void dump(FILE *fd);

private:
  static Resource &lookup(const char *name);
  static std::map<const char *, Resource *> _resourceMap;
  static ink_mutex resourceLock;
};
