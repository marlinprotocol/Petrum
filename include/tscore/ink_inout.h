#pragma once

// source of good macros..
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <arpa/nameser.h>
#ifdef __cplusplus
}
#endif /* __cplusplus */

#define GETCHAR(s, cp) \
  {                    \
    (s) = *(cp)++;     \
  }

#define PUTCHAR(s, cp) \
  {                    \
    *(cp)++ = (s);     \
  }

#define GETLONGLONG(l, cp) \
  {                        \
    (l) = *(cp)++ << 8;    \
    (l) |= *(cp)++;        \
    (l) <<= 8;             \
    (l) |= *(cp)++;        \
    (l) <<= 8;             \
    (l) |= *(cp)++;        \
    (l) <<= 8;             \
    (l) |= *(cp)++;        \
    (l) <<= 8;             \
    (l) |= *(cp)++;        \
    (l) <<= 8;             \
    (l) |= *(cp)++;        \
    (l) <<= 8;             \
    (l) |= *(cp)++;        \
  }

/*
 * Warning: PUTLONGLONG destroys its first argument.
 */
#define PUTLONGLONG(l, cp) \
  {                        \
    (cp)[7] = l;           \
    (cp)[6] = (l >>= 8);   \
    (cp)[5] = (l >>= 8);   \
    (cp)[4] = (l >>= 8);   \
    (cp)[3] = (l >>= 8);   \
    (cp)[2] = (l >>= 8);   \
    (cp)[1] = (l >>= 8);   \
    (cp)[0] = l >> 8;      \
    (cp) += 8;             \
  }
