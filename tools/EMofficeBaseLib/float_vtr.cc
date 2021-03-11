#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "float_vtr.h"

using namespace std;
typedef float Real;
vtr::vtr(Real xval, Real yval, Real zval)
{
  x = xval;
  y = yval;
  z = zval;
}

void vtr::reset()
{
  x = y = z = 0.0;
}

void vtr::negate() 
{ 
  x = -x;
  y = -y;
  z = -z;
}

void vtr::setvtr(Real xval, Real yval, Real zval)
{
  x = xval;
  y = yval;
  z = zval;
}

void vtr::addvtr(Real xval, Real yval, Real zval)
{
  x += xval;
  y += yval;
  z += zval;
}

void vtr::subvtr(Real xval, Real yval, Real zval)
{
  x -= xval;
  y -= yval;
  z -= zval;
}

Real vtr::getx() const { return x; }
Real vtr::gety() const { return y; }
Real vtr::getz() const { return z; }

vtr vtr::operator + (const vtr &operand2) const
{
  vtr sum;

  sum.setvtr(x + operand2.x, 
	     y + operand2.y,
	     z + operand2.z);

  return sum;
}

vtr vtr::operator-(const vtr &operand2) const
{
  vtr sub;

  sub.setvtr(x - operand2.x,
	     y - operand2.y,
	     z - operand2.z);
  
  return sub;
}

vtr vtr::operator*(const vtr &operand2) const
{
  vtr product;
  Real xval, yval, zval;

  xval = y * operand2.z - z * operand2.y;
  yval = -(x * operand2.z - z * operand2.x);
  zval = x * operand2.y - y * operand2.x;
  product.setvtr(xval, yval, zval);

  return product;
}

vtr vtr::operator*(const Real &val) const
{
  vtr product;

  product.setvtr(x * val,
		 y * val,
		 z * val);

  return product;
}

vtr vtr::operator/(const Real &val) const
{
  vtr division;
  
  division.setvtr(x / val,
		  y / val,
		  z / val);
  
  return division;
}

vtr &vtr::operator=(const vtr &right)
{
  x = right.x;
  y = right.y;
  z = right.z;

  return *this;
}

Real dotP(vtr v1, vtr v2)
{
  Real product;

  product = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

  return product;
}

void vtr::unitvtr()
{
  Real magnitude;

  magnitude = x * x +
    y * y +
    z * z;
  magnitude = sqrt(magnitude);
  x = x / magnitude;
  y = y / magnitude;
  z = z / magnitude;
}

void vtr::Scale(Real scale) 
{
  Real mag;

  mag = magnitude();
  mag = scale / mag;

  x *= mag;
  y *= mag;
  z *= mag;
}

void vtr::print()
{
  cout << "( " << x << ", " << y << ", " << z << ")" << endl;
}

Real vtr::magSquare() { return (x * x + y * y + z * z); }

Real vtr::magnitude()
{
  Real mag;

  mag = x * x + y * y + z * z;
  mag = sqrt(mag);

  return mag;
}

Real Length(vtr vv)
{
  return vv.magnitude();
}

Real Determinant(vtr a, vtr b, vtr c)
{
  return (a.x * (b.y * c.z - b.z * c.y) -
	  a.y * (b.x * c.z - c.x * b.z) +
	  a.z * (b.x * c.y - c.x * b.y));
}
