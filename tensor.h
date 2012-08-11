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
  explicit TensorBase(size_type size) :
    m_size(size) { };
  size_type size() const {
    return m_size;
  }
protected:
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
  }
  virtual ~Tensor() {
    delete[] m_data;
  }
  Tensor<T, N>& operator=(const Tensor<T, N> &t) {
    if (this != &t) {
      delete[] m_data;
      m_size = t.m_size;
      m_data = new Tensor<T, N - 1>[m_size];
      for (TensorBase::size_type i = 0; i < m_size; ++i) {
        m_data[i] = t.m_data[i];
      }
    }
  }
  /* Accessors */
  const Tensor<T, N - 1>& operator[](TensorBase::size_type i) const {
    return m_data[i];
  }
  Tensor<T, N - 1>& operator[](TensorBase::size_type i) {
    return m_data[i];
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
  virtual ~Tensor() {
    delete[] m_data;
  }
  Tensor<T, ZERO_RANK>& operator=(const Tensor<T, ZERO_RANK> &t) {
    if (this != &t) {
      delete[] m_data;
      m_size = t.m_size;
      m_data = new T[m_size];
      for (TensorBase::size_type i = 0; i < m_size; ++i) {
        m_data[i] = t.m_data[i];
      }
    }
    return *this;
  }
  /* Accessors */
  const T& operator[](TensorBase::size_type i) const {
    return m_data[i];
  }
  T& operator[](TensorBase::size_type i) {
    return m_data[i];
  }
};

#endif /* TENSOR_H */
