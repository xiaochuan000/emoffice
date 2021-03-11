// CTENSOR.H
#ifndef CTENSOR_H
#define CTENSOR_H
#include "EMcomplex.h"
#include "vtr.h"
#include "cvtr.h"

class cTensor {
private: 
  Complex val[3][3];

public:
  cTensor();
  void setEntry(int, int, Complex );
  void setcTensor(vtr, vtr, vtr);

  // operators
  cTensor operator+(const cTensor &) const;
  cTensor operator-(const cTensor &) const;
  cTensor operator*(const double &) const;
  cTensor operator*(const Complex &) const;
  cTensor operator*(const cTensor &) const;
  cTensor operator/(const double &) const;
  cTensor operator/(const Complex &) const;
  cTensor operator/(const cTensor &) const;
  cVtr operator*(vtr &);
  cVtr operator*(cVtr &);
  cTensor& operator=(const cTensor &);
  cTensor inverse() const;
  cTensor transpose() const;

  // get functions
  Complex getEntry(int, int);
  
  // print function
  void print() const;
};

#endif
