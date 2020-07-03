#pragma once

#include "tscpp/api/Headers.h"
#include "tscpp/api/HttpVersion.h"
#include "tscpp/api/HttpStatus.h"

namespace atscppapi
{
// forward declarations
struct ResponseState;
namespace utils
{
  class internal;
}

/**
 * @brief Encapsulates a response.
 */
class Response : noncopyable
{
public:
  Response();

  /** @return HTTP version of the response */
  HttpVersion getVersion() const;

  /** @return Status code of the response */
  HttpStatus getStatusCode() const;

  /** @param New status code to set */
  void setStatusCode(HttpStatus);

  /** @return Reason phrase of the response */
  std::string getReasonPhrase() const;

  /** @param New reason phrase to set */
  void setReasonPhrase(const std::string &);

  /** @return Headers of the response */
  Headers &getHeaders() const;

  ~Response();

private:
  ResponseState *state_;
  void init(void *hdr_buf, void *hdr_loc);
  void reset();
  friend class Transaction;
  friend class utils::internal;
};
} // namespace atscppapi
