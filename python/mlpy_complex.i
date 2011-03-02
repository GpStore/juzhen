%{
#include <mlcpp.h>
typedef mlcpp::Complex<double> Complex; 
%}

struct Complex {
  Complex();
  Complex(const double r);
  Complex(const double r, const double i);
  Complex(const Complex &c);
  ~Complex();

  bool operator==(const Complex &c);
  bool operator==(const double &c);
  bool operator!=(const Complex &c);
  bool operator!=(const double &c);

  %extend {
    char *__str__() {
      static char temp[256];
      sprintf(temp, "(%f, %f)", $self->real, $self->imag);
      return temp;
    }

    Complex __add__(const Complex &a) {
      return *$self + a;
    }

    Complex __add__(const double &a) {
      return *$self + a;
    }

    Complex __sub__(const Complex &a) {
      return *$self - a;
    }

    Complex __sub__(const double &a) {
      return *$self - a;
    }

    Complex __mul__(const Complex &a) {
      return *$self * a;
    }

    Complex __mul__(const double &a) {
      return *$self * a;
    }

    Complex __div__(const Complex &a) {
      return *$self / a;
    }

    Complex __div__(const double &a) {
      return *$self / a;
    }

  }

  double real;
  double imag;
}; 


Complex Conjugate(const Complex &c);

double abs(const Complex &a);

double abs2(const Complex &a);

double real(const Complex &a);

double imag(const Complex &a);
