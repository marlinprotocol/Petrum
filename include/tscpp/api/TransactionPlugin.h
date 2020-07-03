#pragma once

#include <memory>
#include <mutex>

#include "tscpp/api/Plugin.h"
#include "tscpp/api/Transaction.h"

namespace atscppapi
{
#if !defined(ATSCPPAPI_MUTEX_DEFINED_)
#define ATSCPPAPI_MUTEX_DEFINED_

using Mutex = std::recursive_mutex;

#endif

namespace utils
{
  class internal;
} // namespace utils

/**
 * @private
 */
struct TransactionPluginState;

/**
 * @brief The interface used when creating a TransactionPlugin.
 *
 * A Transaction Plugin is a plugin that will fire only for the specific Transaction it
 * was bound to. When you create a TransactionPlugin you call the parent constructor with
 * the associated Transaction and it will become automatically bound. This means that your
 * TransactionPlugin will automatically be destroyed when the Transaction dies.
 *
 * Implications of this are that you can easily add Transaction scoped storage by adding
 * a member to a TransactionPlugin since the destructor will be called of your TransactionPlugin
 * any cleanup that needs to happen can happen in your destructor as you normally would.
 *
 * You must always be sure to implement the appropriate callback for the type of hook you register.
 *
 * \code
 * // For a more detailed example see examples/transactionhook/
 * class TransactionHookPlugin : publicTransactionPlugin {
 * public:
 *   TransactionHookPlugin(Transaction &transaction) : TransactionPlugin(transaction) {
 *     char_ptr_ = new char[100]; // Transaction scoped storage
 *     registerHook(HOOK_SEND_RESPONSE_HEADERS);
 *   }
 *   virtual ~TransactionHookPlugin() {
 *     delete[] char_ptr_; // cleanup
 *   }
 *   void handleSendResponseHeaders(Transaction &transaction) {
 *     transaction.resume();
 *   }
 * private:
 *   char *char_ptr_;
 * };
 * \endcode
 *
 * @see Plugin
 * @see HookType
 */
class TransactionPlugin : public Plugin
{
public:
  /**
   * registerHook is the mechanism used to attach a transaction hook.
   *
   * \note Whenever you register a hook you must have the appropriate callback definied in your TransactionPlugin
   *  see HookType and Plugin for the correspond HookTypes and callback methods. If you fail to implement the
   *  callback, a default implmentation will be used that will only resume the Transaction.
   *
   * @param HookType the type of hook you wish to register
   * @see HookType
   * @see Plugin
   */
  void registerHook(Plugin::HookType hook_type);
  ~TransactionPlugin() override;

  bool isWebsocket() const;

protected:
  TransactionPlugin(Transaction &transaction);

  /**
   * This method will return a std::shared_ptr to a Mutex that can be used for AsyncProvider and AsyncReceiver operations.
   *
   * If another thread wanted to stop this transaction from dispatching an event it could be passed
   * this mutex and it would be able to lock it and prevent another thread from dispatching back into this
   * TransactionPlugin.
   */
  std::shared_ptr<Mutex> getMutex();

private:
  TransactionPluginState *state_; /**< The internal state for a TransactionPlugin */
  friend class utils::internal;
};

} // end namespace atscppapi
