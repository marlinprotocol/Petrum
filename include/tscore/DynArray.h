#pragma once

template <class T> class DynArray
{
public:
  DynArray(const T *val = 0, intptr_t initial_size = 0);
  ~DynArray();

#ifndef __GNUC__
  operator const T *() const;
#endif
  operator T *();
  T &operator[](intptr_t idx);
  T &operator()(intptr_t idx);
  T *detach();
  T defvalue() const;
  intptr_t length();
  void clear();
  void set_length(intptr_t i);

private:
  void resize(intptr_t new_size);

private:
  T *data;
  const T *default_val;
  int size;
  int pos;
};

template <class T>
inline DynArray<T>::DynArray(const T *val, intptr_t initial_size) : data(nullptr), default_val(val), size(0), pos(-1)
{
  if (initial_size > 0) {
    int i = 1;

    while (i < initial_size) {
      i <<= 1;
    }

    resize(i);
  }
}

template <class T> inline DynArray<T>::~DynArray()
{
  if (data) {
    delete[] data;
  }
}

#ifndef __GNUC__
template <class T> inline DynArray<T>::operator const T *() const
{
  return data;
}
#endif

template <class T> inline DynArray<T>::operator T *()
{
  return data;
}

template <class T> inline T &DynArray<T>::operator[](intptr_t idx)
{
  return data[idx];
}

template <class T>
inline T &
DynArray<T>::operator()(intptr_t idx)
{
  if (idx >= size) {
    intptr_t new_size;

    if (size == 0) {
      new_size = 64;
    } else {
      new_size = size * 2;
    }

    if (idx >= new_size) {
      new_size = idx + 1;
    }

    resize(new_size);
  }

  if (idx > pos) {
    pos = idx;
  }

  return data[idx];
}

template <class T>
inline T *
DynArray<T>::detach()
{
  T *d;

  d    = data;
  data = nullptr;

  return d;
}

template <class T>
inline T
DynArray<T>::defvalue() const
{
  return *default_val;
}

template <class T>
inline intptr_t
DynArray<T>::length()
{
  return pos + 1;
}

template <class T>
inline void
DynArray<T>::clear()
{
  if (data) {
    delete[] data;
    data = nullptr;
  }

  size = 0;
  pos  = -1;
}

template <class T>
inline void
DynArray<T>::set_length(intptr_t i)
{
  pos = i - 1;
}

template <class T>
inline void
DynArray<T>::resize(intptr_t new_size)
{
  if (new_size > size) {
    T *new_data;
    intptr_t i;

    new_data = new T[new_size];

    for (i = 0; i < size; i++) {
      new_data[i] = data[i];
    }

    for (; i < new_size; i++) {
      if (default_val) {
        new_data[i] = (T)*default_val;
      }
    }

    if (data) {
      delete[] data;
    }
    data = new_data;
    size = new_size;
  }
}
