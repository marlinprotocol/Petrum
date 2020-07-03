#pragma once

#include <string>
#include "tscpp/api/Transaction.h"
#include "tscpp/api/TransactionPlugin.h"

namespace atscppapi
{
/**
 * Allows a plugin to act as a server and return the response. This
 * plugin can be created in read request headers hook (pre or post
 * remap).
 */
class InterceptPlugin : public TransactionPlugin
{
protected:
  /**
   * The available types of intercepts.
   */
  enum Type {
    SERVER_INTERCEPT = 0, /**< Plugin will act as origin */
    TRANSACTION_INTERCEPT /**< Plugin will act as cache and origin (on cache miss) */
  };

  /** a plugin must implement this interface, it cannot be constructed directly */
  InterceptPlugin(Transaction &transaction, Type type);

public:
  enum RequestDataType {
    REQUEST_HEADER = 0,
    REQUEST_BODY,
  };

  /**
   * A method that you must implement when writing an InterceptPlugin, this method will be
   * invoked whenever client request data is read.
   */
  virtual void consume(const std::string &data, RequestDataType type) = 0;

  /**
   * A method that you must implement when writing an InterceptPlugin, this method
   * will be invoked when the client request is deemed complete.
   */
  virtual void handleInputComplete() = 0;

  /** Should be called only after request header has completely been consumed */
  Headers &getRequestHeaders();

  ~InterceptPlugin() override;

  struct State; /** Internal use only */

protected:
  /**
   * This method is how an InterceptPlugin will send output back to
   * the client.
   */
  bool produce(const void *data, int data_size);

  bool
  produce(const std::string &data)
  {
    return produce(data.data(), data.size());
  }

  bool setOutputComplete();

private:
  State *state_;

  bool doRead();
  void handleEvent(int, void *);

  friend class utils::internal;
};

} // namespace atscppapi
