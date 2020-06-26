#pragma once

#include "ink_thread.h"

class ContFlags
{
public:
  enum flags { DEBUG_OVERRIDE = 0, DISABLE_PLUGINS = 1, LAST_FLAG };

  ContFlags() {}
  ContFlags(ContFlags const &that) = default;
  ContFlags(uint32_t in_flags) : raw_flags(in_flags) {}
  void
  set_flags(uint32_t new_flags)
  {
    raw_flags = new_flags;
  }
  ContFlags &
  operator=(ContFlags const &other)
  {
    this->set_flags(other.get_flags());
    return *this;
  }

  uint32_t
  get_flags() const
  {
    return raw_flags;
  }
  void
  set_flag(enum flags flag_bit, bool value)
  {
    if (flag_bit >= 0 && flag_bit < LAST_FLAG) {
      if (value)
        raw_flags |= (1 << flag_bit);
      else
        raw_flags &= ~(1 << flag_bit);
    }
  }
  bool
  get_flag(enum flags flag_bit) const
  {
    if (flag_bit >= 0 && flag_bit < LAST_FLAG) {
      return (raw_flags & (1 << flag_bit)) != 0;
    } else {
      return false;
    }
  }
  bool
  is_set() const
  {
    return raw_flags != 0;
  }

private:
  uint32_t raw_flags = 0;
};

void set_cont_flags(const ContFlags &flags);
void set_cont_flag(ContFlags::flags flag_bit, bool value);
ContFlags get_cont_flags();
bool get_cont_flag(ContFlags::flags flag_bit);
