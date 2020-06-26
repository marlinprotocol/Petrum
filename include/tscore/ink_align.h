#pragma once

#include "tscore/ink_time.h"

union Alias32 {
  uint8_t byte[4];
  int32_t i32;
  uint32_t u32;
};

union Alias64 {
  uint8_t byte[8];
  int32_t i32[2];
  uint32_t u32[2];
  int64_t i64;
  uint64_t u64;
  ink_time_t i_time;
};

/**
 * Alignment macros
 */

#define INK_MIN_ALIGN 8
/* INK_ALIGN() is only to be used to align on a power of 2 boundary */
#define INK_ALIGN(size, boundary) (((size) + ((boundary)-1)) & ~((boundary)-1))

/** Default alignment */
#define INK_ALIGN_DEFAULT(size) INK_ALIGN(size, INK_MIN_ALIGN)

//
// Move a pointer forward until it meets the alignment width.
//
static inline void *
align_pointer_forward(const void *pointer_, size_t alignment)
{
  char *pointer = (char *)pointer_;
  //
  // Round up alignment..
  //
  pointer = (char *)INK_ALIGN((ptrdiff_t)pointer, alignment);

  return (void *)pointer;
}

//
// Move a pointer forward until it meets the alignment width specified,
// and zero out the contents of the space you're skipping over.
//
static inline void *
align_pointer_forward_and_zero(const void *pointer_, size_t alignment)
{
  char *pointer = (char *)pointer_;
  char *aligned = (char *)INK_ALIGN((ptrdiff_t)pointer, alignment);
  //
  // Fill the skippings..
  //
  while (pointer < aligned) {
    *pointer = 0;
    pointer++;
  }

  return (void *)aligned;
}

//
// We include two signatures for the same function to avoid error
// messages concerning coercion between void* and unsigned long.
// We could handle this using casts, but that's more prone to
// errors during porting.
//
