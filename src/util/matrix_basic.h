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

#ifndef SRC_UTIL_MATRIX_BASIC_H_
#define SRC_UTIL_MATRIX_BASIC_H_
#include <core/matrix.h>

#include <sstream>
#include <string>

namespace mlcpp {

/**
 * Return the real part of a Matrix
 */
Matrix<float> Real(const Matrix<float> &ma) {
  Matrix<float> m(ma.num_row(), ma.num_col());
  size_t endi = ma.num_row()*ma.num_col();
  float *p1;
  float *p2;
  p1 = m.raw_ptr();
  p2 = ma.raw_ptr();
  for (size_t i = 0; i < endi; i++)
    *(p1++)=*(p2++);
  m.set_temporary(true);
  return m;
}

/**
 * Return the imaginary part of a Matrix
 */
Matrix<float> Imag(const Matrix<float> &ma) {
  Matrix<float> m(ma.num_row(), ma.num_col());
  m.Clear();
  m.set_temporary(true);
  return m;
}

/**
 * Return the real part of a Matrix
 */
Matrix<double> Real(const Matrix<double> &ma) {
  Matrix<double> m(ma.num_row(), ma.num_col());
  size_t endi = ma.num_row()*ma.num_col();
  double *p1;
  double *p2;
  p1 = m.raw_ptr();
  p2 = ma.raw_ptr();
  for (size_t i = 0; i < endi; i++)
    *(p1++)=*(p2++);
  m.set_temporary(true);
  return m;
}

/**
 * Return the imaginary part of a Matrix
 */
Matrix<double> Imag(const Matrix<double> &ma) {
  Matrix<double> m(ma.num_row(), ma.num_col());
  m.Clear();
  m.set_temporary(true);
  return m;
}

/**
 * Return the real part of a Matrix
 */
Matrix<float> Real(const Matrix<CS> &ma) {
  Matrix<float> m(ma.num_row(), ma.num_col());
  size_t endi = ma.num_row()*ma.num_col();
  float *p1;
  CS *p2;
  p1 = m.raw_ptr();
  p2 = ma.raw_ptr();
  for (size_t i = 0; i < endi; i++)
    *(p1++) = (p2++)->real;
  m.set_temporary(true);
  return m;
}

/**
 * Return the imaginary part of a Matrix
 */
Matrix<float> Imag(const Matrix<CS> &ma) {
  Matrix<float> m(ma.num_row(), ma.num_col());
  size_t endi = ma.num_row()*ma.num_col();
  float *p1;
  CS *p2;
  p1 = m.raw_ptr();
  p2 = ma.raw_ptr();
  for (size_t i = 0; i < endi; i++)
    *(p1++) = (p2++)->imag;
  m.set_temporary(true);
  return m;
}

/**
 * Return the real part of a Matrix
 */
Matrix<double> Real(const Matrix<CD> &ma) {
  Matrix<double> m(ma.num_row(), ma.num_col());
  size_t endi = ma.num_row()*ma.num_col();
  double *p1;
  CD *p2;
  p1 = m.raw_ptr();
  p2 = ma.raw_ptr();
  for (size_t i = 0; i < endi; i++)
    *(p1++) = (p2++)->real;
  m.set_temporary(true);
  return m;
}

/**
 * Return the imaginary part of a Matrix
 */
Matrix<double> Imag(const Matrix<CD> &ma) {
  Matrix<double> m(ma.num_row(), ma.num_col());
  size_t endi = ma.num_row()*ma.num_col();
  double *p1;
  CD *p2;
  p1 = m.raw_ptr();
  p2 = ma.raw_ptr();
  for (size_t i = 0; i < endi; i++)
    *(p1++) = (p2++)->imag;
  m.set_temporary(true);
  return m;
}

/**
 * Return transpose of a Matrix
 */
template<typename DataType>
Matrix<DataType> Transpose(const Matrix<DataType> &m) {
  return m.Transpose();
}

/**
 * Return hermitian of a Matrix
 */
template<typename DataType>
Matrix<DataType> Adjoint(const Matrix<DataType> &m) {
  return m.Adjoint();
}

/**
 * Return conjugate of a Matrix
 */
template<typename DataType>
Matrix<DataType> Conjugate(const Matrix<DataType> &m) {
  return m.Conjugate();
}
}
#endif  // SRC_UTIL_MATRIX_BASIC_H_