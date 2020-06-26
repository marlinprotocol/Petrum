#pragma once

#include "tscore/ink_platform.h"
#include "tscore/ink_defs.h"
#include "tscore/ink_hrtime.h"

/*===========================================================================*

                                 Data Types

 *===========================================================================*/

typedef time_t ink_time_t;

/*===========================================================================*

                                 Prototypes

 *===========================================================================*/

#define MICRO_USER 1
#define MICRO_SYS 2
#define MICRO_REAL 3
#define UNDEFINED_TIME ((time_t)0)

uint64_t ink_microseconds(int which);
double ink_time_wall_seconds();

int cftime_replacement(char *s, int maxsize, const char *format, const time_t *clock);
#define cftime(s, format, clock) cftime_replacement(s, 8192, format, clock)

ink_time_t convert_tm(const struct tm *tp);

inkcoreapi char *ink_ctime_r(const ink_time_t *clock, char *buf);
inkcoreapi struct tm *ink_localtime_r(const ink_time_t *clock, struct tm *res);

/*===========================================================================*
                              Inline Stuffage
 *===========================================================================*/
#if defined(freebsd) || defined(openbsd)

inline int
ink_timezone()
{
  struct timeval tp;
  struct timezone tzp;
  ink_assert(!gettimeofday(&tp, &tzp));
  return tzp.tz_minuteswest * 60;
}

#else // non-freebsd, non-openbsd for the else

inline int
ink_timezone()
{
  return timezone;
}

#endif /* #if defined(freebsd) || defined(openbsd) */
