/*
+---------------------------------------------------------------------------+
|  Matrix Library for C++ (mlcpp)                                           |
+---------------------------------------------------------------------------+
|                                                                           |
|  Copyright 2011 Hui Chen                                                  |
|                                                                           |
|  Licensed under the Apache License, Version 2.0 (the "License");          |
|  you may not use this file except in compliance with the License.         |
|  You may obtain a copy of the License at                                  |
|                                                                           |
|      http://www.apache.org/licenses/LICENSE-2.0                           |
|                                                                           |
|  Unless required by applicable law or agreed to in writing, software      |
|  distributed under the License is distributed on an "AS IS" BASIS,        |
|  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. |
|  See the License for the specific language governing permissions and      |
|  limitations under the License.                                           |
|                                                                           |
+---------------------------------------------------------------------------+
*/

#ifndef MLCPP_VECTOR_H_
#define MLCPP_VECTOR_H_

#include <mlcpp_matrix.h>
#include <algorithm>
#include <vector>
#include <math.h>

namespace mlcpp {

/////////////////////////////////////////////////////////////////////////////
/** 
 *  Vector class
 */
template<typename DataType> 
class Vector : public Matrix<DataType> {
public:
  /**
   * Default constructor.
   */
  Vector();

  /**
   * Construct a Vector of size i.
   */
  Vector(size_t i);

  /**
   * Construct a Vector from a Matrix's column-major raw array.
   */
  Vector(const Matrix<DataType> &m);

  /**
   * Construct a Vector from an array. The size of the Vector will be
   * the bigger of data's size and n.
   */
  template<typename T> 
  Vector(const T *data, size_t n);

  /**
   * Construct a Vector from an existing Vector.
   */
  Vector(const std::vector<DataType> &v);

  /**
   * Copy a Vector from another Vector.
   */
  Vector<DataType>& operator=(const Vector<DataType> &v);

  /**
   * Copy a Vector from a STL Vector.
   */
  Vector<DataType>& operator=(const std::vector<DataType> &v);

  /**
   * Assign all elements in the Vector to be rhs. 
   */
  Vector<DataType>& operator=(const DataType rhs);

  /**
   * Resize a Vector.
   */
  void resize(size_t n);

  /**
   * Resize a Vector to have nc*nr elements. 
   */
  void resize(size_t nc, size_t nr);

  /**
   * Return the size of the Vector.
   */
  inline size_t size() const;

  /**
   * Add two Vectors.
   */
  template<typename T> 
  const Vector<DataType> operator+(const Vector<T>& rhs) const;
 
  /**
   * Add two Vectors.
   */
  template<typename T> 
  Vector<DataType>& operator+=(const Vector<T>& rhs);
 
  /**
   * Subtract two Vectors.
   */
  template<typename T> 
  const Vector<DataType> operator-(const Vector<T>& rhs) const;
 
  /**
   * Subtract two Vectors.
   */
  template<typename T> 
  Vector<DataType>& operator-=(const Vector<T>& rhs); 

  /**
   * Multiply a Vector with a real number. 
   */
  template<typename T>
  const Vector<DataType> operator*(const T rhs) const;

  /**
   * Multiply a Vector with a real number. 
   */
  template<typename T>
  Vector<DataType>& operator*=(const T rhs); 

  /**
   * Multiply a Vector and a Matrix. The Vector's size must be equal
   * to the Matrix's number of rows. 
   */
  Vector<DataType>& operator*=(const Matrix<DataType>& rhs);

  /**
   * Divide a Vector by a constant.
   */
  template<typename T> 
  const Vector<DataType> operator/(const T rhs) const;

  /**
   * Divide a Vector by a constant.
   */
  template<typename T> 
  Vector<DataType>& operator/=(const T rhs); 

  /**
   * Get real part of a Vector.
   */
  template<typename T>
  Vector<T> real() const;

  /**
   * Get imaginary part of a Vector.
   */
  template<typename T>
  Vector<T> imag() const;

  /**
   * Get transpose of a Vector (just conjugate it). 
   */
  Vector<DataType> trans() const;

  /**
   * Get hermitian of a Vector (just conjugate it). 
   */
  Vector<DataType> herm() const;

  /**
   * Get conjugate of a Vector.
   */
  Vector<DataType> conj() const; 

  /**
   * Get sum of a Vector's all elements.
   */
  DataType sum() const; 

  /**
   * Get the maximum element of a Vector.
   */
  DataType max() const; 

  /**
   * Swap two elements.
   */
  Vector<DataType> &swap(size_t i1, size_t i2);

  /**
   * Return a sub-vector of [i1, i2)
   */
  Vector<DataType> block(size_t i1, size_t i2);

  /**
   * Replace the sub-vector starting at i with another Vector v. 
   */
  Vector<DataType> &insert(size_t i, Vector<DataType> v);

  /**
   * Sort a Vector. This will give you error for a complex Vector.
   */
  Vector<DataType> &sort();

  /**
   * Get a STL Vector from the Vector. 
   */
  std::vector<DataType> stl();
};

typedef Vector<float> svector;
typedef Vector<double> dvector;
typedef Vector<CS> cvector;
typedef Vector<CD> zvector;

template<typename DataType>
Vector<DataType>::Vector() : Matrix<DataType>() { }

template<typename DataType>
Vector<DataType>::Vector(size_t i) : Matrix<DataType>(i, 1) { }

template<typename DataType>
Vector<DataType>::Vector(const Matrix<DataType> &m) {
  Matrix<DataType>::m_data = 
   typename Matrix<DataType>::DataPtr(new DataArray<DataType>(m.dataptr(), 
                                      m.nrow()*m.ncol())); 
  Matrix<DataType>::m_ncol =1;
  Matrix<DataType>::m_nrow = m.nrow()*m.ncol();
  Matrix<DataType>::m_rawptr = Matrix<DataType>::m_data->m_data;
  Matrix<DataType>::m_temporary = m.gettemporary();
}

template<typename DataType>
template<typename T> 
Vector<DataType>::Vector(const T *data, size_t n) 
  : Matrix<DataType>(data, n, 1){ } 

template<typename DataType>
Vector<DataType>::Vector(const std::vector<DataType> &v) 
  : Matrix<DataType>(&v[0], v.size(), 1) {
}

template<typename DataType>
Vector<DataType>& Vector<DataType>::operator=(const Vector<DataType> &v) { 
  Matrix<DataType>::operator=(v);
  return *this;
} 

template<typename DataType>
Vector<DataType> & 
Vector<DataType>::operator=(const std::vector<DataType> &v) { 
  size_t s = v.size();
  resize(s);
  DataType *p1;
  p1 = Matrix<DataType>::dataptr();
  for(size_t i=0; i<s; i++) *(p1++) = v[i];
  return *this;
} 

template<typename DataType>
Vector<DataType>& Vector<DataType>::operator=(const DataType rhs) {
  Matrix<DataType>::operator=(rhs);
  return *this;
}

template<typename DataType>
void Vector<DataType>::resize(size_t n) { Matrix<DataType>::resize(n,1);}

template<typename DataType>
void Vector<DataType>::resize(size_t nc, size_t nr) {Matrix<DataType>::resize(nc*nr,1);};

template<typename DataType>
inline size_t Vector<DataType>::size() const {
  return Matrix<DataType>::m_nrow;
}

template<typename DataType>
template<typename T> 
const Vector<DataType> Vector<DataType>::operator+(const Vector<T>& rhs) const {
  return Matrix<DataType>::operator+(rhs);
}

template<typename DataType>
template<typename T> 
Vector<DataType>& Vector<DataType>::operator+=(const Vector<T>& rhs) {
  Matrix<DataType>::operator+=(rhs);
  return *this;
}

template<typename DataType>
template<typename T> 
const Vector<DataType> 
Vector<DataType>::operator-(const Vector<T>& rhs) const {
  return Matrix<DataType>::operator-(rhs);
}

template<typename DataType>
template<typename T> 
Vector<DataType>& Vector<DataType>::operator-=(const Vector<T>& rhs) {
  Matrix<DataType>::operator-=(rhs);
  return *this;
}

template<typename DataType>
template<typename T>
const Vector<DataType> Vector<DataType>::operator*(const T rhs) const {
  return Matrix<DataType>::operator*(rhs);
}

template<typename DataType>
template<typename T>
Vector<DataType>& Vector<DataType>::operator*=(const T rhs) {
  Matrix<DataType>::operator*=(rhs);
  return *this;
}

template<typename DataType>
Vector<DataType>& Vector<DataType>::operator*=(const Matrix<DataType>& rhs) {
  
  Matrix<DataType> m = *this;
  (*this) = m.trans() * rhs;
  return *this;
}

template<typename DataType>
template<typename T> 
const Vector<DataType> Vector<DataType>::operator/(const T rhs) const {
  return Matrix<DataType>::operator/(rhs);
}

template<typename DataType>
template<typename T> 
Vector<DataType>& Vector<DataType>::operator/=(const T rhs) {
  Matrix<DataType>::operator/=(rhs);
  return *this;
}

template<typename DataType>
Vector<DataType> Vector<DataType>::trans() const {
  return *this;
}


template<typename DataType>
DataType Vector<DataType>::sum() const {
  DataType r = 0;
  DataType *p = Matrix<DataType>::dataptr();
  for(size_t i=0; i<size(); i++)
    r += *(p++);
  return r;
} 
 
template<typename DataType>
Vector<DataType> Vector<DataType>::herm() const {
  return Matrix<DataType>::conj();
}

template<typename DataType>
Vector<DataType> Vector<DataType>::conj() const {
  return Matrix<DataType>::conj();
}

template<typename DataType>
DataType Vector<DataType>::max() const {
  assert(size()>0);
  DataType r = (*this)(0);
  DataType *p = Matrix<DataType>::dataptr();
  for(size_t i=0; i<size(); i++) {
    if (r < *p) r = *p; 
    p++;
  }
  return r;
} 

template<typename DataType> 
Vector<DataType> & Vector<DataType>::swap(size_t i1, size_t i2) {
  assert(i1<size() && i2<size());
  DataType *p = Matrix<DataType>::m_data->m_data;
  DataType temp;
  temp = p[i1];
  p[i1] = p[i2];
  p[i2] = temp;
  return *this;
}

template<typename DataType>
Vector<DataType> Vector<DataType>::block(size_t i1, size_t i2) {
  return Matrix<DataType>::block(i1, i2, 0, 1);
}

template<typename DataType>
Vector<DataType> & Vector<DataType>::insert(size_t i, Vector<DataType> v) {
  Matrix<DataType>::insert(i, 0);
  return (*this);
}

template<typename DataType>
Vector<DataType> & Vector<DataType>::sort() {
  std::vector<DataType> v(Matrix<DataType>::dataptr(), 
                          Matrix<DataType>::dataptr()+size());
  std::sort(v.begin(), v.end());
  for (size_t i=0; i<v.size(); i++) (*this)[i] = v[i];
  return (*this);
}

template<typename DataType>
std::vector<DataType> Vector<DataType>::stl() {
  std::vector<DataType> v(Matrix<DataType>::dataptr(), 
                          Matrix<DataType>::dataptr()+size());
  return v;
}

/////////////////////////////////////////////////////////////////////////////

/**
 * Return the transpose of a Vector.
 */
template<typename DataType> 
Vector<DataType> trans(const Vector<DataType> &v) {
  return v;
}

/**
 * Return the hermitian of a Vector.
 */
template<typename DataType> 
Vector<DataType> herm(const Vector<DataType> &v) {
  return v.herm();
}

/**
 * Return the conjugate of a Vector.
 */
template<typename DataType> 
Vector<DataType> conj(const Vector<DataType> &v) {
  return v.conj();
}

/**
 * Return the real part of a Vector.
 */
Vector<float> real(const Vector<float> &v) {
  return real((Matrix<float>)v);
} 

/**
 * Return the imaginary part of a Vector.
 */
Vector<float> imag(const Vector<float> &v) {
  return imag((Matrix<float>)v);
}


/**
 * Return the real part of a Vector.
 */
Vector<double> real(const Vector<double> &v) {
  return real((Matrix<double>)v);
} 

/**
 * Return the imaginary part of a Vector.
 */
Vector<double> imag(const Vector<double> &v) {
  return imag((Matrix<double>)v);
}


/**
 * Return the real part of a Vector.
 */
Vector<float> real(const Vector<CS> &v) {
  return real((Matrix<CS>)v);
} 

/**
 * Return the imaginary part of a Vector.
 */
Vector<float> imag(const Vector<CS> &v) {
  return imag((Matrix<CS>)v);
}

/**
 * Return the real part of a Vector.
 */
Vector<double> real(const Vector<CD> &v) {
  return real((Matrix<CD>)v);
} 

/**
 * Return the imaginary part of a Vector.
 */
Vector<double> imag(const Vector<CD> &v) {
  return imag((Matrix<CD>)v);
}

/**
 * Find the sum of a Vector's all elements.
 */
template<typename DataType> 
DataType sum(const Vector<DataType> v) {
  return v.sum();
} 

/**
 * Find the norm-2 of a Vector.
 */
double norm(const Vector<CD> &v)  {
  double r = 0;
  CD *p = v.dataptr();
  size_t size = v.size();
  for(size_t i=0; i<size; i++)
    r += abs2(*(p++));
  return sqrt(r);
}

float norm(const Vector<CS> &v)  {
  float r = 0;
  CS *p = v.dataptr();
  size_t size = v.size();
  for(size_t i=0; i<size; i++)
    r += abs2(*(p++));
  return sqrt(r);
}

double norm(const Vector<double> &v)  {
  double r = 0;
  double *p = v.dataptr();
  size_t size = v.size();
  for(size_t i=0; i<size; i++)
    r += abs2(*(p++));
  return sqrt(r);
}

float norm(const Vector<float> &v)  {
  double r = 0;
  float *p = v.dataptr();
  size_t size = v.size();
  for(size_t i=0; i<size; i++)
    r += abs2(*(p++));
  return sqrt(r);
}

/**
 * Find the maximum element in a Vector.
 */
template<typename DataType> 
DataType max(const Vector<DataType> v) {
  return v.max();
} 

/**
 * Sort a Vector.
 */
template<typename DataType> 
Vector<DataType> sort(const Vector<DataType> &v) {
  Vector<DataType> v2(v.size());
  std::vector<DataType> v1(v.dataptr(), v.dataptr()+v.size());
  std::sort(v1.begin(), v1.end());
  for (size_t i=0; i<v1.size(); i++) v2[i] = v1[i];
  return v2;
}

/**
 * Multiply a real number and a Vector.
 */
template<typename DataType> 
const Vector<DataType> 
operator*(const double lhs, const Vector<DataType> &ma) {
  if (ma.m_temporary) {
    DataType *p = ma.dataptr();
    size_t maxi = ma.size();
    for (size_t i=0; i<maxi; i++)
      *(p++) *= lhs; 
    return ma; 
  } else {
    Vector<DataType> m(ma.size());
    DataType *p1 = ma.dataptr();
    DataType *p2 = m.dataptr();
    size_t maxi = ma.size();
    for (size_t i=0; i<maxi; i++)
      *(p2++) = *(p1++)*lhs; 
    return m;
  }
}

/**
 * Multiply a complex number and a Vector.
 */
template<typename DataType> 
const Vector<DataType> 
operator*(const CD lhs, const Vector<DataType> &ma) {
  if (ma.m_temporary) {
    DataType *p = ma.dataptr();
    size_t maxi = ma.size();
    for (size_t i=0; i<maxi; i++)
      *(p++) *= lhs; 
    return ma; 
  } else {
    Vector<DataType> m(ma.size());
    DataType *p1 = ma.dataptr();
    DataType *p2 = m.dataptr();
    size_t maxi = ma.size();
    for (size_t i=0; i<maxi; i++)
      *(p2++) = *(p1++)*lhs; 
    return m;
  }
}

/**
 * Vector dot product.
 */
template<typename DataType> 
const DataType operator*(const Vector<DataType>& v1, const Vector<DataType>& v2) {
  assert(v1.size() == v2.size());
  DataType res = 0;
  size_t s = v1.size();
  DataType *p1 = v1.dataptr();
  DataType *p2 = v2.dataptr();
  for(size_t i =0;i<s; i++) res+=*(p1++)*(*(p2++));
  return res;
}

/**
 * Multiply a Matrix and a Vector.
 */
template<typename DataType> 
const Vector<DataType> 
operator*(const Matrix<DataType>& ma, const Vector<DataType>& v) {
  return ma*((Matrix<DataType>&)v);
}

/**
 * Multiply a Matrix and a Vector.
 */
template<typename DataType> 
const Vector<DataType> 
operator*(const Vector<DataType>& v, const Matrix<DataType>& ma) {
  return ma*((Matrix<DataType>&)v);
}

/**
 * Multiply a Matrix and a Vector.
 */
template<typename DataType> 
Vector<DataType>& 
operator*=(Matrix<DataType>& ma, const Vector<DataType>& v) {
  ma *= (Matrix<DataType>&) v;
  return ma;
}

template<typename DataType> 
std::ostream& operator<< (std::ostream& out, const Vector<DataType> &m) {
  out << "{";
  for (size_t i=0; i<m.size(); i++) {
    if (i!=m.size()-1) out << m(i) << ", ";
    else out << m(i);
  }
  out << "}";
  return out; 
}

/**
 * Return string form of a Matrix.
 */

template<typename DataType> 
std::string toString(const Vector<DataType> &m) {
  std::ostringstream out;
  out << m;
  return out.str(); 
}


}
/////////////////////////////////////////////////////////////////////////////

#endif