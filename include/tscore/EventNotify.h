#pragma once

#include "tscore/ink_thread.h"

class EventNotify
{
public:
  EventNotify();
  void signal(void);
  int wait(void);
  int timedwait(int timeout); // milliseconds
  void lock(void);
  bool trylock(void);
  void unlock(void);
  ~EventNotify();

private:
#ifdef HAVE_EVENTFD
  int m_event_fd;
  int m_epoll_fd;
#else
  ink_cond m_cond;
  ink_mutex m_mutex;
#endif
};
/* vim: set sw=4 ts=4 tw=79 et : */
