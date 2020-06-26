#pragma once

#include <cstddef>
#include <cstdint>
#include <cctype>

struct ATSHashBase {
  virtual void update(const void *, size_t) = 0;
  virtual void final(void)                  = 0;
  virtual void clear(void)                  = 0;
  virtual ~ATSHashBase();
};

struct ATSHash : ATSHashBase {
  struct nullxfrm {
    uint8_t
    operator()(uint8_t byte) const
    {
      return byte;
    }
  };

  struct nocase {
    uint8_t
    operator()(uint8_t byte) const
    {
      return toupper(byte);
    }
  };

  virtual const void *get(void) const = 0;
  virtual size_t size(void) const     = 0;
  virtual bool operator==(const ATSHash &) const;
};

struct ATSHash32 : ATSHashBase {
  virtual uint32_t get(void) const = 0;
  virtual bool operator==(const ATSHash32 &) const;
};

struct ATSHash64 : ATSHashBase {
  virtual uint64_t get(void) const = 0;
  virtual bool operator==(const ATSHash64 &) const;
};
