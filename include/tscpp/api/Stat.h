#pragma once

#include "tscpp/api/noncopyable.h"
#include <cstdint>
#include <string>

namespace atscppapi
{
/**
 * @brief A Stat is an atomic variable that can be used to store counters, averages, time averages, or summations.
 *
 * All stats are exposed through the traffic_ctl program included with Apache Traffic Server. Additionally,
 * if you've enabled HttpStats all Stats you define will be displayed there. Stats can be read via
 * traffic_ctl metric get stat_name.
 *
 * Stats are very easy to use, here is a simple example of how you can create a counter and increment its
 * value:
 * \code
 *  Stat stat;
 *  stat.init("stat_name");
    stat.inc();
 * \endcode
 *
 * A full example is available in examples/stat_example/.
 */
class Stat : noncopyable
{
public:
  /**
   * The available Stat types.
   */
  enum SyncType {
    SYNC_SUM = 0, /**< The stat will sum all values from a stat.inc(VAL) */
    SYNC_COUNT,   /**< The stat will count all calls to stat.inc(VAL) */
    SYNC_AVG,     /**< The stat will keep an average after call calls to stat.inc(VAL) */
    SYNC_TIMEAVG  /**< The stat will keep a time average of all calls to stat.inc(VAL) */
  };

  Stat();
  ~Stat();

  /**
   * You must initialize your Stat with a call to this init() method.
   *
   * @param name The string name of the stat, this will be visbible via traffic_ctl, or through http stats.
   * @param type The SyncType of the Stat, this decides how TrafficServer will treat your inputs. The default
   *   value is SYNC_COUNT.
   * @param persistent This determines if your Stats will persist, the default value is false.
   * @return True if the stat was successfully created and false otherwise.
   *
   * @see SyncType
   */
  bool init(const std::string &name, Stat::SyncType type = SYNC_COUNT, bool persistent = false);

  /**
   * This method allows you to increment a stat by a certain amount.
   * @param amount the amount to increment the stat by the default value is 1.
   */
  void increment(int64_t amount = 1);

  /**
   * This method allows you to decrement a stat by a certain amount.
   * @param amount the amount to decrement the stat by the default value is 1.
   */
  void decrement(int64_t amount = 1);

  /**
   * This method returns the current value of the stat.
   * @return The value of the stat.
   */
  int64_t get() const;

  /** This method sets the value of the stat.
   * @param value the value to set the stat to.
   */
  void set(int64_t value);

private:
  int stat_id_; /**< The internal stat ID */
};

} // namespace atscppapi
