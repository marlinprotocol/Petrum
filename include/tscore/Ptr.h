#pragma once

#include "tscore/ink_atomic.h"

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//////              ATOMIC VERSIONS
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

struct ForceVFPTToTop {
  virtual ~ForceVFPTToTop() {}
};

////////////////////////////////////////////////////////////////////////
//
// class RefCountObj
// prototypical class for reference counting
//
////////////////////////////////////////////////////////////////////////
class RefCountObj : public ForceVFPTToTop
{
public:
  RefCountObj() : m_refcount(0) {}
  RefCountObj(const RefCountObj &s) : m_refcount(0)
  {
    (void)s;
    return;
  }

  ~RefCountObj() override {}
  RefCountObj &
  operator=(const RefCountObj &s)
  {
    (void)s;
    return (*this);
  }

  // Increment the reference count, returning the new count.
  int
  refcount_inc()
  {
    return ink_atomic_increment((int *)&m_refcount, 1) + 1;
  }

  // Decrement the reference count, returning the new count.
  int
  refcount_dec()
  {
    return ink_atomic_increment((int *)&m_refcount, -1) - 1;
  }

  int
  refcount() const
  {
    return m_refcount;
  }

  virtual void
  free()
  {
    delete this;
  }

private:
  int m_refcount;
};

////////////////////////////////////////////////////////////////////////
//
// class Ptr
//
////////////////////////////////////////////////////////////////////////
template <class T> class Ptr
{
public:
  explicit Ptr(T *p = nullptr);
  Ptr(const Ptr<T> &);
  ~Ptr();

  void clear();
  Ptr<T> &operator=(const Ptr<T> &);
  Ptr<T> &operator=(T *);

  T *operator->() const { return (m_ptr); }
  T &operator*() const { return (*m_ptr); }

  // Making this explicit avoids unwanted conversions.  See https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Safe_bool .
  explicit operator bool() const { return m_ptr != nullptr; }

  int
  operator==(const T *p)
  {
    return (m_ptr == p);
  }

  int
  operator==(const Ptr<T> &p)
  {
    return (m_ptr == p.m_ptr);
  }

  int
  operator!=(const T *p)
  {
    return (m_ptr != p);
  }

  int
  operator!=(const Ptr<T> &p)
  {
    return (m_ptr != p.m_ptr);
  }

  // Return the raw pointer.
  T *
  get() const
  {
    return m_ptr;
  }

  // Return the raw pointer as a RefCount object. Typically
  // this is for keeping a collection of heterogenous objects.
  RefCountObj *
  object() const
  {
    return static_cast<RefCountObj *>(m_ptr);
  }

  // Return the stored pointer, storing NULL instead. Do not increment
  // the refcount; the caller is now responsible for owning the RefCountObj.
  T *
  detach()
  {
    T *tmp = m_ptr;
    m_ptr  = nullptr;
    return tmp;
  }

  // XXX Clearly this is not safe. This is used in HdrHeap::unmarshal() to swizzle
  // the refcount of the managed heap pointers. That code needs to be cleaned up
  // so that this can be removed. Do not use this in new code.
  void
  swizzle(RefCountObj *ptr)
  {
    m_ptr = ptr;
  }

private:
  T *m_ptr;

  friend class CoreUtils;
};

template <typename T>
Ptr<T>
make_ptr(T *p)
{
  return Ptr<T>(p);
}

////////////////////////////////////////////////////////////////////////
//
// inline functions definitions
//
////////////////////////////////////////////////////////////////////////
template <class T> inline Ptr<T>::Ptr(T *ptr /* = 0 */) : m_ptr(ptr)
{
  if (m_ptr) {
    m_ptr->refcount_inc();
  }
}

template <class T> inline Ptr<T>::Ptr(const Ptr<T> &src) : m_ptr(src.m_ptr)
{
  if (m_ptr) {
    m_ptr->refcount_inc();
  }
}

template <class T> inline Ptr<T>::~Ptr()
{
  if (m_ptr && m_ptr->refcount_dec() == 0) {
    m_ptr->free();
  }
}

template <class T>
inline Ptr<T> &
Ptr<T>::operator=(T *p)
{
  T *temp_ptr = m_ptr;

  if (m_ptr == p) {
    return (*this);
  }

  m_ptr = p;

  if (m_ptr) {
    m_ptr->refcount_inc();
  }

  if (temp_ptr && temp_ptr->refcount_dec() == 0) {
    temp_ptr->free();
  }

  return (*this);
}

template <class T>
inline void
Ptr<T>::clear()
{
  if (m_ptr) {
    if (!m_ptr->refcount_dec())
      m_ptr->free();
    m_ptr = nullptr;
  }
}

template <class T>
inline Ptr<T> &
Ptr<T>::operator=(const Ptr<T> &src)
{
  return (operator=(src.m_ptr));
}

// Bit of subtly here for the flipped version of equality checks
// With only the template versions, the compiler will try to substitute @c nullptr_t
// for @c T and fail, because that's not the type and no operator will be found.
// Therefore there needs to be specific overrides for @c nullptr_t.

template <typename T>
inline bool
operator==(std::nullptr_t, Ptr<T> const &rhs)
{
  return rhs.get() == nullptr;
}

template <typename T>
inline bool
operator!=(std::nullptr_t, Ptr<T> const &rhs)
{
  return rhs.get() != nullptr;
}

template <typename T>
inline bool
operator==(T const *lhs, Ptr<T> const &rhs)
{
  return rhs.get() == lhs;
}

template <typename T>
inline bool
operator!=(T const *lhs, Ptr<T> const &rhs)
{
  return rhs.get() != lhs;
}
