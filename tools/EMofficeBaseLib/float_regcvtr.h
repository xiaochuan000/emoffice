// REGISTER.H
// Definition for FEM solution registers
// combined in to EMoffice_base library
#ifndef REGCVTR_H
#define REGCVTR_H
#include <fstream>
#include "float_complex.h"
#include "float_cvtr.h"

using namespace std;

#define SAMPLES 10

class regcvtr {
  friend ifstream &operator>>(ifstream&, regcvtr &);
  friend ofstream &operator<<(ofstream&, const regcvtr &);
  friend void ReadRegcvtr(char *, int, regcvtr *);
  friend cVtr GetField(regcvtr, double, double, double);

 private:
  int  n;
  cVtr *field;

 public:
  regcvtr(); // constructor
  void init(int = 10);
  cVtr GetField(int = 0);
  void SetField(int, cVtr);
};

#endif
