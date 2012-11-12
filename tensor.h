/*
 * Tensor.h
 *
 *  Created on: May 18, 2011
 *      Author: Tor E Hagemann <hagemt@rpi.edu>
 */

#ifndef TENSOR_H
#define TENSOR_H

#define ZERO_RANK 0ul
#define DEFAULT_SIZE 11

class TensorBase {
public:
  typedef unsigned long size_type;
  size_type size() const {
    return m_size;
  }
  virtual void clear() = 0;
protected:
  explicit TensorBase(size_type size) :
    m_size(size) { };
  virtual ~TensorBase() {
    m_size = 0;
  }
  bool rebase(const TensorBase &t) {
    if (this != &t) {
      clear();
      m_size = t.m_size;
      return true;
    }
    return false;
  }
private:
  size_type m_size;
};

template <typename T, TensorBase::size_type N>
class Tensor : public TensorBase {
  Tensor<T, N - 1> *m_data;
public:
	explicit Tensor(TensorBase::size_type size = DEFAULT_SIZE, const T& t = T()) :
    TensorBase(size)
  {
    m_data = new Tensor<T, N - 1>[size];
    for (TensorBase::size_type i = 0; i < size; ++i) {
      m_data[i] = Tensor<T, N - 1>(size, t);
    }
  }
  Tensor<T, N>& operator=(const Tensor<T, N> &t) {
    if (rebase(t)) {
      m_data = new Tensor<T, N - 1>[t.size()];
      for (TensorBase::size_type i = 0; i < size(); ++i) {
        m_data[i] = t.m_data[i];
      }
    }
    return *this;
  }
  virtual ~Tensor() {
    clear();
  }
  /* Accessors */
  const Tensor<T, N - 1>& operator[](TensorBase::size_type i) const {
    return m_data[i];
  }
  Tensor<T, N - 1>& operator[](TensorBase::size_type i) {
    return m_data[i];
  }
  void clear() {
    if (m_data) {
      for (TensorBase::size_type i = 0; i < size(); ++i) {
        m_data[i].clear();
      }
      delete[] m_data;
      m_data = NULL;
    }
  }
};

template <typename T>
class Tensor<T, ZERO_RANK> : public TensorBase {
  T *m_data;
public:
	explicit Tensor(TensorBase::size_type size = DEFAULT_SIZE, const T& t = T()) :
    TensorBase(size)
  {
    m_data = new T[size];
    for (TensorBase::size_type i = 0; i < size; ++i) {
      m_data[i] = t;
    }
  }
  Tensor<T, ZERO_RANK>& operator=(const Tensor<T, ZERO_RANK> &t) {
    if (rebase(t)) {
      m_data = new T[t.size()];
      for (TensorBase::size_type i = 0; i < size(); ++i) {
        m_data[i] = t.m_data[i];
      }
    }
    return *this;
  }
  virtual ~Tensor() {
    clear();
  }
  /* Accessors */
  const T& operator[](TensorBase::size_type i) const {
    return m_data[i];
  }
  T& operator[](TensorBase::size_type i) {
    return m_data[i];
  }
  void clear() {
    if (m_data) {
      delete[] m_data;
      m_data = NULL;
    }
  }
};

#endif /* TENSOR_H */
