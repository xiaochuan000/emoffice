// SPARMAT.H
#ifndef SPARMAT_H
#define SPARMAT_H
#include "float_complex.h"
#include "float_densecmat.h"
#include "float_array.h"

class sparMat {
 public: 
  int dim, NZ;
  int *rowA, *colA;
  int SEGSIZE, part[3];
  Complex *entry;

 public:
  sparMat(int = 1000000);
  void sparInit(int, int);
  void setIA(int, int);
  void setJA(int, int);
  int *getIAPtr();
  int *getJAPtr();
  void addEntry(int, int, Complex);
  void blockAddEntry(int, int *, denseCMat);
  Complex getEntry(int);
  int getDim();
  int getNZ();
  int *getPart();
  void getDiagonal(Complex *);

  void readEntry(char *);
  void readIA(char *);
  void readJA(char *);
  void readNZ(char *);
  void setIA(int *);
  void setJA(int *);
  void setDim(int );
  void setNZ(int );
  void setPart(int, int );
  void setSIZE(int = 1000000);
  void setEntry(int, const Complex &);
  void setEntry(int, int, const Complex &);

  // overload operators
       sparMat operator+(const sparMat &) const;
  sparMat operator-(const sparMat &) const;
  sparMat operator*(const float &) const;
  sparMat operator*(const Complex &) const;
  sparMat operator/(const float &) const;
  sparMat operator/(const Complex &) const;
  sparMat &operator+=(const sparMat &);
  sparMat &operator-=(const sparMat &);
  sparMat &operator*=(const float &);
  sparMat &operator*=(const Complex &);
  sparMat &operator/=(const float &);
  sparMat &operator/=(const Complex &);
  sparMat &operator=(const sparMat &);
  
  ArrayComplex operator*(const ArrayComplex &) const;
  void MXV(const ArrayComplex &, ArrayComplex *) const;

  // print functions
  void print(char *);
  void write();
  void PRINTA(char *);

  // matrix solution process
  void preCOND(char *, float = 0.005);
  void solve(char *, ArrayComplex, ArrayComplex *, float = 1.0e-4);
  void READA(char *);
  void DELETEA();
  void OOCMXV(char *, ArrayComplex, ArrayComplex *, int = 0);
};

#endif

