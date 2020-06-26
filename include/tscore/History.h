#pragma once

#include "tscore/SourceLocation.h"

#define NO_REENTRANT 99999
#define NO_EVENT NO_REENTRANT
#define HISTORY_DEFAULT_SIZE 65

struct HistoryEntry {
  SourceLocation location;
  unsigned short event = 0;
  short reentrancy     = 0;
};

template <unsigned Count> class History
{
public:
  void
  push_back(const SourceLocation &location, int event, int reentrant = NO_REENTRANT)
  {
    int pos                 = history_pos++ % Count;
    history[pos].location   = location;
    history[pos].event      = (unsigned short)event;
    history[pos].reentrancy = (short)reentrant;
  }

  void
  clear()
  {
    ink_zero(history);
    history_pos = 0;
  }

  bool
  overflowed() const
  {
    return history_pos >= Count;
  }

  unsigned int
  size() const
  {
    return history_pos > Count ? Count : history_pos;
  }

  const HistoryEntry &operator[](unsigned int i) const { return history[i]; }

private:
  HistoryEntry history[Count];

  unsigned int history_pos = 0;
};
