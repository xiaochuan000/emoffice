#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cvtr.h"

cVtr::cVtr()
{
  x = Complex (0.0, 0.0);
  y = Complex (0.0, 0.0);
  z = Complex (0.0, 0.0);
}

void cVtr::reset()
{
  x = Complex (0.0, 0.0);
  y = Complex (0.0, 0.0);
  z = Complex (0.0, 0.0);
}

void cVtr::setcvtr(Complex xval, Complex yval, Complex zval)
{
  x = xval;
  y = yval;
  z = zval;
}

cVtr cVtr::operator+(const cVtr &operand2) const
{
  cVtr sum;

  sum.setcvtr(x + operand2.x,
	      y + operand2.y,
	      z + operand2.z);

  return sum;
}

cVtr cVtr::operator-(const cVtr &operand2) const
{
  cVtr sub;

  sub.setcvtr(x - operand2.x,
	      y - operand2.y,
	      z - operand2.z);

  return sub;
}

cVtr cVtr::operator*(const double &dd) const
{
  cVtr product;

  product.setcvtr(x * dd,
		  y * dd,
		  z * dd);

  return product;
}

cVtr cVtr::operator*(const Complex &dd) const
{
  cVtr product;

  product.setcvtr(x * dd,
		  y * dd,
		  z * dd);

  return product;
}

cVtr cVtr::operator*(const cVtr &operand2) const
{
  cVtr product;

  product.setcvtr(y * operand2.z - z * operand2.y,
		  z * operand2.x - x * operand2.z,
		  x * operand2.y - y * operand2.x);

  return product;
}

cVtr cVtr::operator*(const vtr &operand2) const
{
  cVtr product;

  product.setcvtr(y * operand2.getz() - z * operand2.gety(),
		  z * operand2.getx() - x * operand2.getz(),
		  x * operand2.gety() - y * operand2.getx());

  return product;
}

cVtr cVtr::operator/(const double &dd) const
{
  cVtr division;

  division.setcvtr(x / dd,
		   y / dd,
		   z / dd);

  return division;
}

cVtr& cVtr::operator=(const cVtr &right)
{
  x = right.x;
  y = right.y;
  z = right.z;

  return *this;
}

cVtr& cVtr::operator=(const vtr &right)
{
  x = right.getx();
  y = right.gety();
  z = right.getz();

  return *this;
}

Complex dotP(cVtr cv, vtr vv)
{
  Complex dp;

  dp = cv.getx() * vv.getx() +
    cv.gety() * vv.gety() +
    cv.getz() * vv.getz();

  return dp;
}

Complex dotP(cVtr cv, cVtr vv)
{
  Complex dp;

  dp = cv.getx() * vv.getx() +
    cv.gety() * vv.gety() +
    cv.getz() * vv.getz();

  return dp;
}

void cVtr::Conjugate()
{
  x = conj(x);
  y = conj(y);
  z = conj(z);
}

void cVtr::Negate()
{
  x = -x;
  y = -y;
  z = -z;
}

Complex cVtr::getx() { return x; }
Complex cVtr::gety() { return y; }
Complex cVtr::getz() { return z; }

void cVtr::print()
{
}

double cVtr::magnitude()
{
  double val;
  
  val = magSquare();

  return (sqrt(val));
}

double cVtr::magSquare()
{
  double val;

  val = norm(x) + norm(y) + norm(z);

  return val;
}

