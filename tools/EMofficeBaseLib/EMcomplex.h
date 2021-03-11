#ifndef EMOFFICE_COMPLEX_H
#define EMOFFICE_COMPLEX_H

using namespace std;
// namespace EMOFFICE{
#include <complex>
//#define Complex complex<double>
typedef complex<double> Complex;
#define ZERO 1.0e-20

inline
complex<double> operator+(const complex<double> &a, const float &b)
{ return a + (double)b; }

inline
complex<double> operator+(const float &a, const complex<double> &b)
{ return (double)a + b; }

inline
complex<float> operator+(const complex<float> &a, const double &b)
{ return a + (float)b; }

inline
complex<float> operator+(const double &a, const complex<float> &b)
{ return (float)a + b; }

inline
complex<double> operator-(const complex<double> &a, const float &b)
{ return a - (double)b; }

inline
complex<double> operator-(const float &a, const complex<double> &b)
{ return (double)a - b; }

inline
complex<float> operator-(const complex<float> &a, const double &b)
{ return a - (float)b; }

inline
complex<float> operator-(const double &a, const complex<float> &b)
{ return (float)a - b; }

inline
complex<double> operator*(const complex<double> &a, const float &b)
{ return a * (double)b; }

inline
complex<double> operator*(const float &a, const complex<double> &b)
{ return (double)a * b; }

inline
complex<float> operator*(const complex<float> &a, const double &b)
{ return a * (float)b; }

inline
complex<float> operator*(const double &a, const complex<float> &b)
{ return (float)a * b; }

inline
complex<double> operator/(const complex<double> &a, const float &b)
{ return a / (double)b; }

inline
complex<double> operator/(const float &a, const complex<double> &b)
{ return (double)a / b; }

inline
complex<float> operator/(const complex<float> &a, const double &b)
{ return a / (float)b; }

inline
complex<float> operator/(const double &a, const complex<float> &b)
{ return (float)a / b; }

inline
complex<double> operator+(const complex<double> &a, const complex<float> &b)
{ return a + complex<double>(b); }

inline
complex<double> operator+(const complex<float> &a, const complex<double> &b)
{ return complex<double>(a) + b; }

inline
complex<double> operator-(const complex<double> &a, const complex<float> &b)
{ return a - complex<double>(b); }

inline
complex<double> operator-(const complex<float> &a, const complex<double> &b)
{ return complex<double>(a) + b; }

inline
complex<double> operator*(const complex<double> &a, const complex<float> &b)
{ return a * complex<double>(b); }

inline
complex<double> operator*(const complex<float> &a, const complex<double> &b)
{ return complex<double>(a) * b; }

inline
complex<double> operator/(const complex<double> &a, const complex<float> &b)
{ return a / complex<double>(b); }

inline
complex<double> operator/(const complex<float> &a, const complex<double> &b)
{ return complex<double>(a) / b; }

#endif

