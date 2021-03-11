#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "vtr.h"

using namespace std;

static const double ZERO_10 = 1.e-10;

vtr::vtr(double xval, double yval, double zval)
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

void vtr::setvtr(double xval, double yval, double zval)
{
  x = xval;
  y = yval;
  z = zval;
}

void vtr::addvtr(double xval, double yval, double zval)
{
  x += xval;
  y += yval;
  z += zval;
}

void vtr::subvtr(double xval, double yval, double zval)
{
  x -= xval;
  y -= yval;
  z -= zval;
}

double vtr::getx() const { return x; }
double vtr::gety() const { return y; }
double vtr::getz() const { return z; }

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
  double xval, yval, zval;

  xval = y * operand2.z - z * operand2.y;
  yval = -(x * operand2.z - z * operand2.x);
  zval = x * operand2.y - y * operand2.x;
  product.setvtr(xval, yval, zval);

  return product;
}

vtr vtr::operator*(const double &val) const
{
  vtr product;

  product.setvtr(x * val,
		 y * val,
		 z * val);

  return product;
}

vtr vtr::operator/(const double &val) const
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

double dotP(vtr v1, vtr v2)
{
  double product;

  product = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

  return product;
}

void vtr::unitvtr()
{
  double magnitude;

  magnitude = x * x +
    y * y +
    z * z;
  magnitude = sqrt(magnitude);
  x = x / magnitude;
  y = y / magnitude;
  z = z / magnitude;
}

int vtr::operator== (const vtr &right) const
{
  double xr = right.getx();
  if ( fabs(x-xr) > ZERO_10 ) return 0;
  xr = right.gety();
  if ( fabs(y-xr) > ZERO_10 ) return 0;
  xr = right.getz();
  if ( fabs(z-xr) > ZERO_10 ) return 0;
  return 1;
}


int vtr::operator!= (const vtr &right) const
{
  double xr = right.getx();
  if ( fabs(x-xr) > ZERO_10 ) return 1;
  xr = right.gety();
  if ( fabs(y-xr) > ZERO_10 ) return 1;
  xr = right.getz();
  if ( fabs(z-xr) > ZERO_10 ) return 1;
  return 0;
}


int vtr::operator>(const vtr &right) const
{
  double r = right.getx();
  if ( x > r + ZERO_10 ) return 1;
  if ( x < r - ZERO_10 ) return 0;
  r = right.gety();
  if ( y > r + ZERO_10 ) return 1;
  if ( y < r - ZERO_10 ) return 0;
  r = right.getz();
  if ( z > r + ZERO_10 ) return 1;
  if ( z < r - ZERO_10 ) return 0;
  return 0;
}


int vtr::operator<(const vtr &right) const
{
  double r = right.getx();
  if ( x > r + ZERO_10 ) return 0;
  if ( x < r - ZERO_10 ) return 1;
  r = right.gety();
  if ( y > r + ZERO_10 ) return 0;
  if ( y < r - ZERO_10 ) return 1;
  r = right.getz();
  if ( z > r + ZERO_10 ) return 0;
  if ( z < r - ZERO_10 ) return 1;
  return 0;  
}

void vtr::Scale(double scale) 
{
  double mag;

  mag = magnitude();
  mag = scale / mag;

  x *= mag;
  y *= mag;
  z *= mag;
}

void vtr::print()
{
  cout << "( " << x << ", " << y << ", " << z << " )" << endl;
}

double vtr::magSquare() { return (x * x + y * y + z * z); }

double vtr::magnitude()
{
  double mag;

  mag = x * x + y * y + z * z;
  mag = sqrt(mag);

  return mag;
}

double Length(vtr vv)
{
  return vv.magnitude();
}

double Determinant(vtr a, vtr b, vtr c)
{
  return (a.x * (b.y * c.z - b.z * c.y) -
	  a.y * (b.x * c.z - c.x * b.z) +
	  a.z * (b.x * c.y - c.x * b.y));
}


double findArea(vtr *ndArray, int ndNum)
{ 
  int i;
  double aera=0.0;
  for (i = 0; i < ndNum-1; i++) 
    aera += triArea(ndArray[0], ndArray[(i+1)%ndNum], ndArray[(i+2)%ndNum]);

  return aera; 
}

double triArea(vtr nd0, vtr nd1, vtr nd2)
{
  double area;
  vtr t0 = nd2 - nd1;
  vtr t1 = nd0 - nd2;
  vtr normal = t0 * t1;
  area = 0.5 * normal.magnitude();
  return area;
}
