#pragma once

#ifdef HAVE_SYS_ENDIAN_H
#include <sys/endian.h>
#endif
#ifdef HAVE_MACHINE_ENDIAN_H
#include <machine/endian.h>
#endif
#ifdef HAVE_ENDIAN_H
#include <endian.h>
#endif
#ifdef HAVE_SYS_BYTEORDER_H
#include <sys/byteorder.h>
#endif

#if defined(darwin)
#include <libkern/OSByteOrder.h>
inline uint64_t
be64toh(uint64_t x)
{
  return OSSwapBigToHostInt64(x);
}
inline uint64_t
htobe64(uint64_t x)
{
  return OSSwapHostToBigInt64(x);
}
#endif
