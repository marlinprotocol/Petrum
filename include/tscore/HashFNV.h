#pragma once

#include "tscore/Hash.h"
#include <cstdint>

struct ATSHash32FNV1a : ATSHash32 {
  ATSHash32FNV1a(void);

  template <typename Transform> void update(const void *data, size_t len, Transform xfrm);
  void
  update(const void *data, size_t len) override
  {
    update(data, len, ATSHash::nullxfrm());
  }

  void final(void) override;
  uint32_t get(void) const override;
  void clear(void) override;

private:
  uint32_t hval;
};

template <typename Transform>
void
ATSHash32FNV1a::update(const void *data, size_t len, Transform xfrm)
{
  uint8_t *bp = (uint8_t *)data;
  uint8_t *be = bp + len;

  for (; bp < be; ++bp) {
    hval ^= (uint32_t)xfrm(*bp);
    hval += (hval << 1) + (hval << 4) + (hval << 7) + (hval << 8) + (hval << 24);
  }
}

struct ATSHash64FNV1a : ATSHash64 {
  ATSHash64FNV1a(void);

  template <typename Transform> void update(const void *data, size_t len, Transform xfrm);
  void
  update(const void *data, size_t len) override
  {
    update(data, len, ATSHash::nullxfrm());
  }

  void final(void) override;
  uint64_t get(void) const override;
  void clear(void) override;

private:
  uint64_t hval;
};

template <typename Transform>
void
ATSHash64FNV1a::update(const void *data, size_t len, Transform xfrm)
{
  uint8_t *bp = (uint8_t *)data;
  uint8_t *be = bp + len;

  for (; bp < be; ++bp) {
    hval ^= (uint64_t)xfrm(*bp);
    hval += (hval << 1) + (hval << 4) + (hval << 5) + (hval << 7) + (hval << 8) + (hval << 40);
  }
}
