// CVTR.H
#ifndef CVTR_H
#define CVTR_H
#include "EMcomplex.h"
#include "vtr.h"

class cVtr {
  friend class cTensor;
  friend Complex dotP(cVtr, vtr);
  friend Complex dotP(cVtr, cVtr);

public:
  Complex x, y, z;

public:
  cVtr();
  void reset();
  void setcvtr(Complex, Complex, Complex);
  void Negate();

  // operators
  cVtr operator+(const cVtr &) const;
  cVtr operator-(const cVtr &) const;
  cVtr operator*(const double &) const;
  cVtr operator*(const Complex &) const;
  cVtr operator*(const cVtr &) const;
  cVtr operator*(const vtr &) const;

  cVtr operator/(const double &) const;
  cVtr& operator=(const cVtr &);
  cVtr& operator=(const vtr &);

  double magnitude();
  double magSquare();

  void Conjugate();
  // get functions
  Complex getx(), gety(), getz();
  
  // print function
  void print();
};

#endif
