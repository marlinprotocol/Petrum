#pragma once

namespace atscppapi
{
/**
 * @brief noncopyable is a base class that will prevent derived classes from being copied.
 *
 * @private Prevent Doxygen from showing this class in the inheritance diagrams.
 *
 * To use noncopyable you only need to inherit from this class and you're derived class
 * will become uncopyable
 *
 * \code
 * class myClass : uncopyable {
 * public:
 *  int test_;
 * }
 *
 * // The following will fail:
 * myClass a;
 * myClass b(a); // fails
 * myClass c = a; // fails
 * \endcode
 */
class noncopyable
{
protected:
  noncopyable() {}
  ~noncopyable() {}

  noncopyable(const noncopyable &) = delete;
  const noncopyable &operator=(const noncopyable &) = delete;
};

} // namespace atscppapi
