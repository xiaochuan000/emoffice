// REGISTER.H
// Definition for FEM solution registers
#ifndef REGISTER_H
#define REGISTER_H
#include <fstream>
#include "EMcomplex.h"
#include "cvtr.h"

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
  void delet() { delete [] field; };
  void del() { delete [] field; }; // added for dd
  void reset(){for(int i=0;i<n;i++) field[i].reset();}
  regcvtr operator*(const Complex right)const;
};

#endif
