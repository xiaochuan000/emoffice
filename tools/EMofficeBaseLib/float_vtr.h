// VTR.H
#ifndef VTR_H
#define VTR_H

class vtr {
  friend float dotP(vtr, vtr);
  friend float Length(vtr);
  friend float Determinant(vtr, vtr, vtr);
  
 private:
  float x, y, z;

 public:
  // constructor
  vtr(float =0.0, float =0.0, float =0.0);
  
  // operators
  vtr operator+(const vtr &) const;
  vtr operator-(const vtr &) const;
  vtr operator*(const vtr &) const;
  vtr operator*(const float &) const;
  vtr operator/(const float &) const;
  vtr& operator=(const vtr &);

  // set functions
  void setvtr(float, float, float);
  void reset();
  void unitvtr();
  void addvtr(float = 0.0, float = 0.0, float = 0.0);
  void subvtr(float = 0.0, float = 0.0, float = 0.0);
  void Scale(float = 1.0);
  void negate();

  // get functions
  float getx() const;
  float gety() const;
  float getz() const;
  float magnitude();
  float magSquare();

  // print
  void print();
};

#endif
