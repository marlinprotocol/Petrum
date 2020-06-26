#pragma once

/***********************************************************************

    Fast Mutex

    Uses atomic memory operations to minimize blocking.


***********************************************************************/

#include "tscore/ink_defs.h"
#include "tscore/ink_error.h"

#include <pthread.h>
#include <cstdlib>
typedef pthread_mutex_t ink_mutex;

void ink_mutex_init(ink_mutex *m);
void ink_mutex_destroy(ink_mutex *m);

static inline void
ink_mutex_acquire(ink_mutex *m)
{
  int error = pthread_mutex_lock(m);
  if (unlikely(error != 0)) {
    ink_abort("pthread_mutex_lock(%p) failed: %s (%d)", m, strerror(error), error);
  }
}

static inline void
ink_mutex_release(ink_mutex *m)
{
  int error = pthread_mutex_unlock(m);
  if (unlikely(error != 0)) {
    ink_abort("pthread_mutex_unlock(%p) failed: %s (%d)", m, strerror(error), error);
  }
}

static inline bool
ink_mutex_try_acquire(ink_mutex *m)
{
  return pthread_mutex_trylock(m) == 0;
}

/** RAII class for locking a @c ink_mutex.

    @code
    ink_mutex m;
    // ...
    {
       ink_mutex_scoped_lock lock(m);
       // code under lock.
    }
    // code not under lock
    @endcode
 */
class ink_scoped_mutex_lock
{
private:
  ink_mutex &_m;

public:
  ink_scoped_mutex_lock(ink_mutex *m) : _m(*m) { ink_mutex_acquire(&_m); }
  ink_scoped_mutex_lock(ink_mutex &m) : _m(m) { ink_mutex_acquire(&_m); }
  ~ink_scoped_mutex_lock() { ink_mutex_release(&_m); }
};
