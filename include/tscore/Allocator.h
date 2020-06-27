#pragma once

#include <new>
#include <cstdlib>
#include "tscore/ink_queue.h"
#include "tscore/ink_defs.h"
#include "tscore/ink_resource.h"
#include <execinfo.h>

#define RND16(_x) (((_x) + 15) & ~15)

extern int cmd_disable_pfreelist;

/** Allocator for fixed size memory blocks. */
class Allocator
{
public:
  /**
    Allocate a block of memory (size specified during construction
    of Allocator.
  */
  void *
  alloc_void()
  {
    return ink_freelist_new(this->fl, freelist_class_ops);
  }

  /**
    Deallocate a block of memory allocated by the Allocator.

    @param ptr pointer to be freed.
  */
  void
  free_void(void *ptr)
  {
    ink_freelist_free(this->fl, ptr, freelist_class_ops);
  }

  /**
    Deallocate blocks of memory allocated by the Allocator.

    @param head pointer to be freed.
    @param tail pointer to be freed.
    @param num_item of blocks to be freed.
  */
  void
  free_void_bulk(void *head, void *tail, size_t num_item)
  {
    ink_freelist_free_bulk(this->fl, head, tail, num_item, freelist_class_ops);
  }

  Allocator() { fl = nullptr; }

  /**
    Creates a new allocator.

    @param name identification tag used for mem tracking .
    @param element_size size of memory blocks to be allocated.
    @param chunk_size number of units to be allocated if free pool is empty.
    @param alignment of objects must be a power of 2.
  */
  Allocator(const char *name, unsigned int element_size, unsigned int chunk_size = 128, unsigned int alignment = 8)
  {
    ink_freelist_init(&fl, name, element_size, chunk_size, alignment);
  }

  /** Re-initialize the parameters of the allocator. */
  void
  re_init(const char *name, unsigned int element_size, unsigned int chunk_size, unsigned int alignment, int advice)
  {
    ink_freelist_madvise_init(&this->fl, name, element_size, chunk_size, alignment, advice);
  }

protected:
  InkFreeList *fl;
};

/**
  Allocator for Class objects. It uses a prototype object to do
  fast initialization. Prototype of the template class is created
  when the fast allocator is created. This is instantiated with
  default (no argument) constructor. Constructor is not called for
  the allocated objects. Instead, the prototype is just memory
  copied onto the new objects. This is done for performance reasons.

*/
template <class C> class ClassAllocator : public Allocator
{
public:
  /** Allocates objects of the templated type. */
  C *
  alloc()
  {
    void *ptr = ink_freelist_new(this->fl, freelist_class_ops);

    memcpy(ptr, (void *)&this->proto.typeObject, sizeof(C));
    return (C *)ptr;
  }

  /**
    Deallocates objects of the templated type.

    @param ptr pointer to be freed.
  */
  void
  free(C *ptr)
  {
    ink_freelist_free(this->fl, ptr, freelist_class_ops);
  }

  /**
    Deallocates objects of the templated type.

    @param head pointer to be freed.
    @param tail pointer to be freed.
    @param num_item of blocks to be freed.
   */
  void
  free_bulk(C *head, C *tail, size_t num_item)
  {
    ink_freelist_free_bulk(this->fl, head, tail, num_item, freelist_class_ops);
  }

  /**
    Allocate objects of the templated type via the inherited interface
    using void pointers.
  */
  void *
  alloc_void()
  {
    return (void *)alloc();
  }

  /**
    Deallocate objects of the templated type via the inherited
    interface using void pointers.

    @param ptr pointer to be freed.
  */
  void
  free_void(void *ptr)
  {
    free((C *)ptr);
  }

  /**
    Deallocate objects of the templated type via the inherited
    interface using void pointers.

    @param head pointer to be freed.
    @param tail pointer to be freed.
    @param num_item of blocks.
  */
  void
  free_void_bulk(void *head, void *tail, size_t num_item)
  {
    free_bulk((C *)head, (C *)tail, num_item);
  }

  /**
    Create a new class specific ClassAllocator.

    @param name some identifying name, used for mem tracking purposes.
    @param chunk_size number of units to be allocated if free pool is empty.
    @param alignment of objects must be a power of 2.
  */
  ClassAllocator(const char *name, unsigned int chunk_size = 128, unsigned int alignment = 16)
  {
    ::new ((void *)&proto.typeObject) C();
    ink_freelist_init(&this->fl, name, RND16(sizeof(C)), chunk_size, RND16(alignment));
  }

  struct {
    uint8_t typeObject[sizeof(C)];
    int64_t space_holder = 0;
  } proto;
};

template <class C> class TrackerClassAllocator : public ClassAllocator<C>
{
public:
  TrackerClassAllocator(const char *name, unsigned int chunk_size = 128, unsigned int alignment = 16)
    : ClassAllocator<C>(name, chunk_size, alignment), allocations(0), trackerLock(PTHREAD_MUTEX_INITIALIZER)
  {
  }

  C *
  alloc()
  {
    void *callstack[3];
    int frames = backtrace(callstack, 3);
    C *ptr     = ClassAllocator<C>::alloc();

    const void *symbol = nullptr;
    if (frames == 3 && callstack[2] != nullptr) {
      symbol = callstack[2];
    }

    tracker.increment(symbol, (int64_t)sizeof(C), this->fl->name);
    ink_mutex_acquire(&trackerLock);
    reverse_lookup[ptr] = symbol;
    ++allocations;
    ink_mutex_release(&trackerLock);

    return ptr;
  }

  void
  free(C *ptr)
  {
    ink_mutex_acquire(&trackerLock);
    std::map<void *, const void *>::iterator it = reverse_lookup.find(ptr);
    if (it != reverse_lookup.end()) {
      tracker.increment((const void *)it->second, (int64_t)sizeof(C) * -1, nullptr);
      reverse_lookup.erase(it);
    }
    ink_mutex_release(&trackerLock);
    ClassAllocator<C>::free(ptr);
  }

private:
  ResourceTracker tracker;
  std::map<void *, const void *> reverse_lookup;
  uint64_t allocations;
  ink_mutex trackerLock;
};