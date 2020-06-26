#pragma once

/****************************************************************************


A simple linked list queue.
****************************************************************************/
#include "tscore/ink_mutex.h"
#include "tscore/ink_thread.h"

typedef struct llqrec_s {
  struct llqrec_s *next;
  void *data;
} LLQrec;

typedef struct llq_s {
  LLQrec *head, *tail, *free;
  uint64_t len, highwater;
  ink_mutex mux;
  ink_semaphore sema;
} LLQ;

LLQ *create_queue(void);
int enqueue(LLQ *q, void *data);
void *dequeue(LLQ *q);
bool queue_is_empty(LLQ *q);
uint64_t queue_len(LLQ *Q);
uint64_t queue_highwater(LLQ *Q);
void delete_queue(LLQ *Q); /* only deletes an empty queue but
                              provides symmetry. */
