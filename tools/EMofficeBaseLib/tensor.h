// tensor.H
#ifndef tensor_H
#define tensor_H
#include "vtr.h"

class tensor {
private: 
  double val[3][3];

public:
  tensor(double = 0.0, double = 0.0, double = 0.0,
	 double = 0.0, double = 0.0, double = 0.0,
	 double = 0.0, double = 0.0, double = 0.0);
  void setEntry(int, int, double );
  void settensor(vtr, vtr, vtr);

  // operators
  tensor operator+(const tensor &) const;
  tensor operator-(const tensor &) const;
  tensor operator*(const double &) const;
  tensor operator*(const tensor &) const;
  tensor operator/(const double &) const;
  tensor operator/(const tensor &) const;
  vtr operator*(vtr &);
  tensor& operator=(const tensor &);
  tensor inverse() const;
  tensor transpose() const;

  // get functions
  double getEntry(int, int);
  
  // print function
  void print() const;
};

#endif
