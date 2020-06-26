#pragma once

#include "tscore/ink_mutex.h"
#include "tscore/ink_thread.h"

#define RW_MAGIC 0x19283746

struct ink_rwlock {
  ink_mutex rw_mutex;      /* basic lock on this struct */
  ink_cond rw_condreaders; /* for reader threads waiting */
  ink_cond rw_condwriters; /* for writer threads waiting */
  int rw_magic;            /* for error checking */
  int rw_nwaitreaders;     /* the number waiting */
  int rw_nwaitwriters;     /* the number waiting */
  int rw_refcount;
};

int ink_rwlock_init(ink_rwlock *rw);
int ink_rwlock_destroy(ink_rwlock *rw);
int ink_rwlock_rdlock(ink_rwlock *rw);
int ink_rwlock_wrlock(ink_rwlock *rw);
int ink_rwlock_unlock(ink_rwlock *rw);
