#pragma once

#include "tscore/ink_apidefs.h"
#include "tscore/ink_defs.h"
#if TS_ENABLE_FIPS == 0
#include <openssl/md5.h>

/* INK_MD5 context. */
typedef MD5_CTX INK_DIGEST_CTX;

/*
  Wrappers around the MD5 functions, all of this should be depericated and just use the functions directly
*/

inkcoreapi int ink_code_md5(unsigned const char *input, int input_length, unsigned char *sixteen_byte_hash_pointer);
inkcoreapi int ink_code_incr_md5_init(INK_DIGEST_CTX *context);
inkcoreapi int ink_code_incr_md5_update(INK_DIGEST_CTX *context, const char *input, int input_length);
inkcoreapi int ink_code_incr_md5_final(char *sixteen_byte_hash_pointer, INK_DIGEST_CTX *context);
#endif
