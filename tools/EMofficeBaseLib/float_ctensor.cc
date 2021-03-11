#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "float_ctensor.h"

using namespace std;

cTensor::cTensor()
{
  int i, j;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) val[i][j] = Complex (0.0, 0.0);
  }
}

void cTensor::setEntry(int rr, int cc, Complex value)
{
  val[rr][cc] = value;
}

cTensor cTensor::operator+(const cTensor &operand2) const
{
  cTensor sum;
  int i, j;
  Complex cval;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cval = val[i][j] + operand2.val[i][j];

      sum.setEntry(i, j, cval);
    }
  }

  return sum;
}

cTensor cTensor::operator-(const cTensor &operand2) const
{
  cTensor sub;
  int i, j;
  Complex cval;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cval = val[i][j] - operand2.val[i][j];

      sub.setEntry(i, j, cval);
    }
  }

  return sub;
}

cTensor cTensor::operator*(const double &dd) const
{
  int i, j;
  cTensor product;
  Complex cval;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cval = val[i][j] * (float)dd;
      
      product.setEntry(i, j, cval);
    }
  }

  return product;
}

cTensor cTensor::operator*(const Complex &cc) const
{
  int i, j;
  cTensor product;
  Complex cval;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cval = val[i][j] * cc;
      
      product.setEntry(i, j, cval);
    }
  }

  return product;
}


cTensor cTensor::operator/(const double &dd) const
{
  int i, j;
  Complex cval;
  cTensor division;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cval = val[i][j] / (float)dd;

      division.setEntry(i, j, cval);
    }
  }

  return division;
}

cTensor cTensor::operator/(const Complex &dd) const
{
  int i, j;
  Complex cval;
  cTensor division;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cval = val[i][j] / dd;

      division.setEntry(i, j, cval);
    }
  }

  return division;
}

cVtr cTensor::operator*(vtr &vv)
{
  cVtr cv;
  Complex cval[3];
  int i;

  for (i = 0; i < 3; i ++) {
    cval[i] = Complex (0.0, 0.0);

    cval[i] = (val[i][0] * (float)vv.getx()) +
      (val[i][1] * (float)vv.gety()) +
      (val[i][2] * (float)vv.getz());
  }
  cv.setcvtr(cval[0], cval[1], cval[2]);

  return cv;
}

cVtr cTensor::operator*(cVtr &vv)
{
  cVtr cv;
  Complex cval[3];
  int i;

  for (i = 0; i < 3; i ++) {
    cval[i] = Complex (0.0, 0.0);

    cval[i] = (val[i][0] * vv.getx()) +
      (val[i][1] * vv.gety()) +
      (val[i][2] * vv.getz());
  }
  cv.setcvtr(cval[0], cval[1], cval[2]);

  return cv;
}

cTensor& cTensor::operator=(const cTensor &right)
{
  int i, j;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      val[i][j] = right.val[i][j];
    }
  }

  return *this;
}

Complex cTensor::getEntry(int rr, int cc)
{
  return val[rr][cc];
}

void Gaussj(cTensor *a)
{
  int    n, indxc[3], indxr[3], ipiv[3];
  int    i, icol, irow, j, k, l, ll;
  double big;
  Complex  dum, pivinv, tval;
  Complex  unitVAL(1.0, 0.0), zeroVAL(0.0, 0.0);

  n = 3;
  for (j = 0; j < n; j ++) ipiv[j] = 0;
  for (i = 0; i < n; i ++) {
    big = 0.0;
    for (j = 0; j < n; j ++)
      if (ipiv[j] != 1)
	for (k = 0; k < n; k ++) {
	  if (ipiv[k] == 0) {
	    if (abs(a->getEntry(j, k)) >= big) {
	      big = abs(a->getEntry(j, k));
	      irow = j; icol = k;
	    }
	  } else if (ipiv[k] > 1) {
	    printf("Gaussj: Singular Matrix -- 1\n");
	    exit(1);
	  }
	}
    ++(ipiv[icol]);
    if (irow != icol) {
      for (l = 0; l < n; l ++) {
	tval = a->getEntry(irow, l);
	a->setEntry(irow, l, a->getEntry(icol, l));
	a->setEntry(icol, l, tval);
      }
    }
    indxr[i] = irow;
    indxc[i] = icol;
    if (abs(a->getEntry(icol, icol)) < ZERO) {
      printf("Gaussj: Singular Matrix -- 2\n");
      exit(1);
    }
    pivinv = unitVAL / (a->getEntry(icol, icol));
    a->setEntry(icol, icol, unitVAL);

    for (l = 0; l < n; l ++) {
      a->setEntry(icol, l, (a->getEntry(icol, l)) * pivinv);
    }
    for (ll = 0; ll < n; ll ++)
      if (ll != icol) {
	dum = a->getEntry(ll, icol);
	a->setEntry(ll, icol, zeroVAL);

	for (l = 0; l < n; l ++) {
	  tval = a->getEntry(icol, l) * dum;
	  a->setEntry(ll, l, (a->getEntry(ll, l)) - tval);
	}
      }
  }
  for (l = (n-1); l >= 0; l --) {
    if (indxr[l] != indxc[l])
      for (k = 0; k < n; k ++) {
	tval = a->getEntry(k, indxr[l]);
	a->setEntry(k, indxr[l], a->getEntry(k, indxc[l]));
	a->setEntry(k, indxc[l], tval);
      }
  }
}

cTensor cTensor::operator/(const cTensor &operand2) const
{
  cTensor division, invert;
  int i, j, k;
  Complex cij;

  invert = operand2.inverse();
  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cij = Complex (0.0, 0.0);

      for (k = 0; k < 3; k ++) {
	cij = cij + (val[i][k] * invert.val[k][j]);
      }
      division.setEntry(i, j, cij);
    }
  }

  return division;
}

cTensor cTensor::inverse() const
{
  cTensor invert;
  int i, j;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) invert.setEntry(i, j, val[i][j]);
  }
  Gaussj(&invert);
  
  return invert;
}

void cTensor::setcTensor(vtr a, vtr b, vtr c)
{
  val[0][0] = a.getx();
  val[1][0] = a.gety();
  val[2][0] = a.getz();

  val[0][1] = b.getx();
  val[1][1] = b.gety();
  val[2][1] = b.getz();

  val[0][2] = c.getx();
  val[1][2] = c.gety();
  val[2][2] = c.getz();
}
 
cTensor cTensor::transpose() const
{
  cTensor transP;
  int i, j;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      transP.val[i][j] = val[j][i];
    }
  }

  return transP;
}

cTensor cTensor::operator*(const cTensor &operand2) const
{
  cTensor product;
  int i, j, k;
  Complex cval;
  
  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cval= Complex(0.0, 0.0);

      for (k = 0; k < 3; k ++) {
	cval = cval + (val[i][k] * operand2.val[k][j]);
      }
      product.val[i][j] = cval;
    }
  }

  return product;
}

void cTensor::print() const
{
  int i, j;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cout << val[i][j] << " ";
    }
    cout << endl;
  }
}


