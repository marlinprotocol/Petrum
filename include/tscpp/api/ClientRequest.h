#pragma once

#include "tscpp/api/Request.h"

namespace atscppapi
{
struct ClientRequestState;

/**
 * @brief Encapsulates a client request. A client request is different from a
 * server request as it has two URLs - the pristine URL sent by the client
 * and a remapped URL created by the server.
 */
class ClientRequest : public Request
{
public:
  /**
   * @private
   */
  ClientRequest(void *raw_txn, void *hdr_buf, void *hdr_loc);

  /**
   * Returns the pristine (pre-remap) client request URL
   *
   * @return Url Reference to non-mutable pristine URL.
   */
  const Url &getPristineUrl() const;

  ~ClientRequest();

private:
  ClientRequestState *state_;
};
} // namespace atscppapi
