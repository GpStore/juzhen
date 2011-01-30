#ifndef MKLPP_COMPLEX_H
#define MKLPP_COMPLEX_H
#include <iostream>
#include <mkl_cblas.h>
#include <mkl_lapacke.h>
#include <mkl.h>
namespace mklpp {

//#define CD MKL_Complex16 
#define CD ComplexDouble 
#define MKLCD MKL_Complex16 

/////////////////////////////////////////////////////////////////////////////
/* _ComplexDouble structure 
   wrapping MKL_Complex16 with more interfaces*/
struct _ComplexDouble : MKLCD {
  _ComplexDouble() {};
  _ComplexDouble(double r, double i);
  _ComplexDouble(double r);
  _ComplexDouble(MKLCD c);

  const struct _ComplexDouble & operator=(double r);

  const struct _ComplexDouble & operator=(const MKLCD &c);
};

typedef struct _ComplexDouble CD;

_ComplexDouble::_ComplexDouble(double r, double i) { real = r; imag = i;};
_ComplexDouble::_ComplexDouble(double r) { real = r; imag =0.0;};
_ComplexDouble::_ComplexDouble(MKLCD c) { real = c.real; imag =c.imag;};

const CD& _ComplexDouble::operator=(double r) {
  real = r;
  imag = 0.0;
  return *this;
}

const CD& _ComplexDouble::operator=(const MKLCD &c) {
  real = c.real;
  imag = c.imag;
  return *this;
}


/////////////////////////////////////////////////////////////////////////////

/* complex constant */
CD C1 (1.,0.);
CD Ci (0.,1.);
CD C0 (0.,0.);

/* arithmatic operations */
inline const CD operator+(const CD &a, const CD &b) {
  CD c;
  c.real = a.real + b.real; 
  c.imag = a.imag + b.real;
  return c;
}

inline CD& operator+=(CD &a, const CD &b) {
  a.real += b.real; 
  a.imag += b.real;
  return a;
}

inline const CD operator-(const CD &a, const CD &b) {
  CD c;
  c.real = a.real - b.real; 
  c.imag = a.imag - b.imag;
  return c;
}

inline CD& operator-=(CD &a, const CD &b) {
  a.real -= b.real; 
  a.imag -= b.real;
  return a;
}

inline const CD operator*(const CD &a, const CD &b) {
  CD c;
  c.real = a.real*b.real - a.imag*b.imag; 
  c.imag = a.real*b.imag + a.imag*b.real;
  return c;
}

inline CD& operator*=(CD &a, const CD &b) {
  a.real = a.real*b.real - a.imag*b.imag; 
  a.imag = a.real*b.imag + a.imag*b.real;
  return a;
}

inline const CD operator*(const CD &a, const double b) {
  CD c;
  c.real = a.real * b; 
  c.imag = a.imag * b;
  return c;
}

inline const CD operator*(const double b, const CD &a) {
  CD c;
  c.real = a.real * b; 
  c.imag = a.imag * b;
  return c;
}

inline CD& operator*=(CD &a, const double b) {
  a.real = a.real * b; 
  a.imag = a.imag * b;
  return a;
}

inline const CD operator/(const CD &a, const double b) {
  CD c;
  c.real = a.real / b; 
  c.imag = a.imag / b;
  return c;
}

inline CD& operator/=(CD &a, const double b) {
  a.real = a.real / b; 
  a.imag = a.imag / b;
  return a;
}

inline double abs2(const CD &a) {
  return a.real*a.real+a.imag*a.imag;
}

inline const CD operator/(const CD &a, const CD &b) {
  CD c;
  double de = 1/abs2(b);
  c.real = de*(a.real*b.real + a.imag*b.imag);
  c.imag = de*(-a.real*b.imag + a.imag*b.real);
  return c;
}

inline CD& operator/=(CD &a, const CD &b) {
  double de = 1/abs2(b);
  double temp = a.real;
  a.real = de*(a.real*b.real + a.imag*b.imag);
  a.imag = de*(-temp*b.imag + a.imag*b.real);
  return a;
}

inline const CD conj(const CD &a) {
  CD c;
  c.real = a.real; 
  c.imag = -a.imag;
  return c;
}

std::ostream& operator<< (std::ostream& out, const CD &m) {
  out << "(" << m.real << ", " << m.imag << ")";
  return out; 
}
/////////////////////////////////////////////////////////////////////////////
 
}
#endif
