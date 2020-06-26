#pragma once

#include "tscore/Hash.h"
#include <openssl/evp.h>

struct ATSHashMD5 : ATSHash {
  ATSHashMD5(void);
  void update(const void *data, size_t len) override;
  void final(void) override;
  const void *get(void) const override;
  size_t size(void) const override;
  void clear(void) override;
  ~ATSHashMD5() override;

private:
  EVP_MD_CTX *ctx;
  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len;
  bool finalized;
};
