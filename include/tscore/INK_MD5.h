#pragma once

#include "tscore/ink_code.h"
#include "tscore/ink_defs.h"
#include "tscore/CryptoHash.h"

class MD5Context : public ats::CryptoContextBase
{
protected:
  MD5_CTX _ctx;

public:
  MD5Context();
  /// Update the hash with @a data of @a length bytes.
  bool update(void const *data, int length) override;
  /// Finalize and extract the @a hash.
  bool finalize(CryptoHash &hash) override;
};

typedef CryptoHash INK_MD5;
