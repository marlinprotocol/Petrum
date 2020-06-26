#pragma once

/*
 * Base64 encoding and decoding as according to RFC1521.  Similar to uudecode.
 * See RFC1521 for specificiation.
 *
 * RFC 1521 requires inserting line breaks for long lines.  The basic web
 * authentication scheme does not require them.  This implementation is
 * intended for web-related use, and line breaks are not implemented.
 *
 * These routines return char*'s to malloc-ed strings.  The caller is
 * responsible for freeing the strings.
 *
 */
// Encodes / Decodes into user supplied buffer.  Returns number of bytes decoded
bool ats_base64_encode(const char *inBuffer, size_t inBufferSize, char *outBuffer, size_t outBufSize, size_t *length);
bool ats_base64_encode(const unsigned char *inBuffer, size_t inBufferSize, char *outBuffer, size_t outBufSize, size_t *length);

bool ats_base64_decode(const char *inBuffer, size_t inBufferSize, unsigned char *outBuffer, size_t outBufSize, size_t *length);

// Little helper functions to calculate minimum required output buffer for encoding/decoding.
#define ATS_BASE64_ENCODE_DSTLEN(_length) ((_length * 8) / 6 + 4)
#define ATS_BASE64_DECODE_DSTLEN(_length) (((_length + 3) / 4) * 3)
