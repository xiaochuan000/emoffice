// tensor.H
#ifndef tensor_H
#define tensor_H
#include "vtr.h"

class tensor {
private: 
  float val[3][3];

public:
  tensor(float = 0.0, float = 0.0, float = 0.0,
	 float = 0.0, float = 0.0, float = 0.0,
	 float = 0.0, float = 0.0, float = 0.0);
  void setEntry(int, int, float );
  void settensor(vtr, vtr, vtr);

  // operators
  tensor operator+(const tensor &) const;
  tensor operator-(const tensor &) const;
  tensor operator*(const float &) const;
  tensor operator*(const tensor &) const;
  tensor operator/(const float &) const;
  tensor operator/(const tensor &) const;
  vtr operator*(vtr &);
  tensor& operator=(const tensor &);
  tensor inverse() const;
  tensor transpose() const;

  // get functions
  float getEntry(int, int);
  
  // print function
  void print() const;
};

#endif
