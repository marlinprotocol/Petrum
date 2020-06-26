#pragma once

#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cassert>

#include "tscore/ink_defs.h"
#include "tscore/ink_apidefs.h"
#include "tscore/ink_mutex.h"

/* GCC compiler >= 4.1 */
#if defined(__GNUC__) && (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 1)) || (__GNUC__ >= 5))

/* see http://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Atomic-Builtins.html */

// ink_atomic_swap(ptr, value)
// Writes @value into @ptr, returning the previous value.
template <typename T>
static inline T
ink_atomic_swap(T *mem, T value)
{
  return __sync_lock_test_and_set(mem, value);
}

// ink_atomic_cas(mem, prev, next)
// Atomically store the value @next into the pointer @mem, but only if the current value at @mem is @prev.
// Returns true if @next was successfully stored.
template <typename T>
static inline bool
ink_atomic_cas(T *mem, T prev, T next)
{
  return __sync_bool_compare_and_swap(mem, prev, next);
}

// ink_atomic_increment(ptr, count)
// Increment @ptr by @count, returning the previous value.
template <typename Type, typename Amount>
static inline Type
ink_atomic_increment(Type *mem, Amount count)
{
  return __sync_fetch_and_add(mem, (Type)count);
}

// ink_atomic_decrement(ptr, count)
// Decrement @ptr by @count, returning the previous value.
template <typename Type, typename Amount>
static inline Type
ink_atomic_decrement(Type *mem, Amount count)
{
  return __sync_fetch_and_sub(mem, (Type)count);
}

// Special hacks for ARM 32-bit
#if (defined(__arm__) || defined(__mips__)) && (SIZEOF_VOIDP == 4)
extern ink_mutex __global_death;

template <>
inline int64_t
ink_atomic_swap<int64_t>(int64_t *mem, int64_t value)
{
  int64_t old;
  ink_mutex_acquire(&__global_death);
  old  = *mem;
  *mem = value;
  ink_mutex_release(&__global_death);
  return old;
}

template <>
inline bool
ink_atomic_cas<int64_t>(int64_t *mem, int64_t old, int64_t new_value)
{
  int64_t curr;
  ink_mutex_acquire(&__global_death);
  curr = *mem;
  if (old == curr)
    *mem = new_value;
  ink_mutex_release(&__global_death);
  if (old == curr)
    return 1;
  return 0;
}

template <typename Amount>
static inline int64_t
ink_atomic_increment(int64_t *mem, Amount value)
{
  int64_t curr;
  ink_mutex_acquire(&__global_death);
  curr = *mem;
  *mem = curr + value;
  ink_mutex_release(&__global_death);
  return curr;
}

template <typename Amount>
static inline int64_t
ink_atomic_decrement(int64_t *mem, Amount value)
{
  int64_t curr;
  ink_mutex_acquire(&__global_death);
  curr = *mem;
  *mem = curr - value;
  ink_mutex_release(&__global_death);
  return curr;
}

template <typename Amount>
static inline uint64_t
ink_atomic_increment(uint64_t *mem, Amount value)
{
  uint64_t curr;
  ink_mutex_acquire(&__global_death);
  curr = *mem;
  *mem = curr + value;
  ink_mutex_release(&__global_death);
  return curr;
}

template <typename Amount>
static inline uint64_t
ink_atomic_decrement(uint64_t *mem, Amount value)
{
  uint64_t curr;
  ink_mutex_acquire(&__global_death);
  curr = *mem;
  *mem = curr - value;
  ink_mutex_release(&__global_death);
  return curr;
}

#endif /* Special hacks for ARM 32-bit */

/* not used for Intel Processors which have sequential(esque) consistency */
#define INK_WRITE_MEMORY_BARRIER
#define INK_MEMORY_BARRIER

#else /* not gcc > v4.1.2 */
#error Need a compiler / libc that supports atomic operations, e.g. gcc v4.1.2 or later
#endif
