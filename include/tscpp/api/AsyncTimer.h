#pragma once

#include <string>
#include <memory>
#include "tscpp/api/Async.h"
#include "tscpp/api/Request.h"
#include "tscpp/api/Response.h"

namespace atscppapi
{
// forward declarations
struct AsyncTimerState;

/**
 * @brief This class provides an implementation of AsyncProvider that
 * acts as a timer. It sends events at the set frequency. Calling the
 * destructor will stop the events. A one-off timer just sends one
 * event. Calling the destructor before this event will cancel the timer.
 *
 * For either type, user must delete the timer.
 *
 * See example async_timer for sample usage.
 */
class AsyncTimer : public AsyncProvider
{
public:
  enum Type {
    TYPE_ONE_OFF = 0,
    TYPE_PERIODIC,
  };

  /**
   * Constructor.
   *
   * @param type A one-off timer fires only once and a periodic timer fires periodically.
   * @param period_in_ms The receiver will receive an event every this many milliseconds.
   * @param initial_period_in_ms The first event will arrive after this many milliseconds. Subsequent
   *                             events will have "regular" cadence. This is useful if the timer is
   *                             set for a long period of time (1hr etc.), but an initial event is
   *                             required. Value of 0 (default) indicates no initial event is desired.
   */
  AsyncTimer(Type type, int period_in_ms, int initial_period_in_ms = 0);

  ~AsyncTimer() override;

  /**
   * Starts the timer.
   */
  void run() override;

  void cancel() override;

private:
  AsyncTimerState *state_;
};

} // namespace atscppapi
