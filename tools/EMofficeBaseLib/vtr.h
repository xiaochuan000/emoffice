// VTR.H
#ifndef VTR_H
#define VTR_H

class vtr {
  friend double dotP(vtr, vtr);
  friend double Length(vtr);
  friend double Determinant(vtr, vtr, vtr);
  
 private:
  double x, y, z;

 public:
  // constructor
  vtr(double =0.0, double =0.0, double =0.0);
  
  // operators
  vtr operator+(const vtr &) const;
  vtr operator-(const vtr &) const;
  vtr operator*(const vtr &) const;
  vtr operator*(const double &) const;
  vtr operator/(const double &) const;
  vtr& operator=(const vtr &);
  int operator== (const vtr &right) const;
  int operator!= (const vtr &right) const;
  int operator>(const vtr &right) const;
  int operator<(const vtr &right) const;

  // set functions
  void setvtr(double, double, double);
  void reset();
  void unitvtr();
  void addvtr(double = 0.0, double = 0.0, double = 0.0);
  void subvtr(double = 0.0, double = 0.0, double = 0.0);
  void Scale(double = 1.0);
  void negate();

  // get functions
  double getx() const;
  double gety() const;
  double getz() const;
  double magnitude();
  double magSquare();

  // print
  void print();
};

// added by MV 05/27/03
double findArea( vtr *ndArray, int ndNum );
double triArea( vtr nd0, vtr nd1, vtr nd2 );

#endif
