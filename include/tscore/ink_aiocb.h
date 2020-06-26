#pragma once

#include "tscore/ink_defs.h"

/* TODO use native aiocb where possible */

#define LIO_READ 0x1
#define LIO_WRITE 0x2

struct ink_aiocb {
  int aio_fildes;
#if defined(__STDC__)
  void *aio_buf; /* buffer location */
#else
  void *aio_buf; /* buffer location */
#endif
  size_t aio_nbytes; /* length of transfer */

  // TODO change to off_t
  off_t aio_offset; /* file offset */

  int aio_reqprio; /* request priority offset */
  //    struct sigevent aio_sigevent;   /* signal number and offset */
  int aio_lio_opcode; /* listio operation */
  //    aio_result_t    aio_resultp;    /* results */
  int aio_state;   /* state flag for List I/O */
  int aio__pad[1]; /* extension padding */
};
