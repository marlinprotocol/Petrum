#pragma once

#include "tscore/Hash.h"
#include <cstdint>

/*
  Siphash is a Hash Message Authentication Code and can take a key.

  If you don't care about MAC use the void constructor and it will use
  a zero key for you.
 */

struct ATSHash64Sip24 : ATSHash64 {
  ATSHash64Sip24(void);
  ATSHash64Sip24(const unsigned char key[16]);
  ATSHash64Sip24(std::uint64_t key0, std::uint64_t key1);
  void update(const void *data, std::size_t len) override;
  void final(void) override;
  std::uint64_t get(void) const override;
  void clear(void) override;

private:
  unsigned char block_buffer[8] = {0};
  std::uint8_t block_buffer_len = 0;
  std::uint64_t k0              = 0;
  std::uint64_t k1              = 0;
  std::uint64_t v0              = 0;
  std::uint64_t v1              = 0;
  std::uint64_t v2              = 0;
  std::uint64_t v3              = 0;
  std::uint64_t hfinal          = 0;
  std::size_t total_len         = 0;
  bool finalized                = false;
};
