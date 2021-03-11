#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <string.h>
#include "tensor.h"

using namespace std;

#define ZERO 1.0e-30

tensor::tensor(double a00, double a01, double a02, 
	       double a10, double a11, double a12,
	       double a20, double a21, double a22)
{
  val[0][0] = a00;
  val[0][1] = a01;
  val[0][2] = a02;
  val[1][0] = a10;
  val[1][1] = a11;
  val[1][2] = a12;
  val[2][0] = a20;
  val[2][1] = a21;
  val[2][2] = a22;
}

void tensor::setEntry(int rr, int cc, double value)
{
  val[rr][cc] = value;
}

tensor tensor::operator+(const tensor &operand2) const
{
  tensor sum;
  int i, j;
  double cval;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cval = val[i][j] + operand2.val[i][j];

      sum.setEntry(i, j, cval);
    }
  }

  return sum;
}

tensor tensor::operator-(const tensor &operand2) const
{
  tensor sub;
  int i, j;
  double cval;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cval = val[i][j] - operand2.val[i][j];

      sub.setEntry(i, j, cval);
    }
  }

  return sub;
}

tensor tensor::operator*(const double &dd) const
{
  int i, j;
  tensor product;
  double cval;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cval = val[i][j] * dd;
      
      product.setEntry(i, j, cval);
    }
  }

  return product;
}

tensor tensor::operator/(const double &dd) const
{
  int i, j;
  double cval;
  tensor division;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cval = val[i][j] / dd;

      division.setEntry(i, j, cval);
    }
  }

  return division;
}

vtr tensor::operator*(vtr &vv)
{
  vtr cv;
  double cval[3];
  int i;

  for (i = 0; i < 3; i ++) {
    cval[i] = 0.0;

    cval[i] = (val[i][0] * vv.getx()) +
      (val[i][1] * vv.gety()) +
      (val[i][2] * vv.getz());
  }
  cv.setvtr(cval[0], cval[1], cval[2]);

  return cv;
}

tensor& tensor::operator=(const tensor &right)
{
  int i, j;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      val[i][j] = right.val[i][j];
    }
  }

  return *this;
}

double tensor::getEntry(int rr, int cc)
{
  return val[rr][cc];
}

void Gaussj(tensor *a)
{
  int    n, indxc[3], indxr[3], ipiv[3];
  int    i, icol, irow, j, k, l, ll;
  double big;
  double  dum, pivinv, tval;

  n = 3;
  for (j = 0; j < n; j ++) ipiv[j] = 0;
  for (i = 0; i < n; i ++) {
    big = 0.0;
    for (j = 0; j < n; j ++)
      if (ipiv[j] != 1)
	for (k = 0; k < n; k ++) {
	  if (ipiv[k] == 0) {
	    if (fabs(a->getEntry(j, k)) >= big) {
	      big = fabs(a->getEntry(j, k));
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
    if (fabs(a->getEntry(icol, icol)) < ZERO) {
      printf("Gaussj: Singular Matrix -- 2\n");
      exit(1);
    }
    pivinv = 1.0 / (a->getEntry(icol, icol));
    a->setEntry(icol, icol, 1.0);

    for (l = 0; l < n; l ++) {
      a->setEntry(icol, l, (a->getEntry(icol, l)) * pivinv);
    }
    for (ll = 0; ll < n; ll ++)
      if (ll != icol) {
	dum = a->getEntry(ll, icol);
	a->setEntry(ll, icol, 0.0);

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

tensor tensor::operator/(const tensor &operand2) const
{
  tensor division, invert;
  int i, j, k;
  double cij;

  invert = operand2.inverse();
  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cij = 0.0;

      for (k = 0; k < 3; k ++) {
	cij = cij + (val[i][k] * invert.val[k][j]);
      }
      division.setEntry(i, j, cij);
    }
  }

  return division;
}

tensor tensor::inverse() const
{
  tensor invert;
  int i, j;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) invert.setEntry(i, j, val[i][j]);
  }
  Gaussj(&invert);
  
  return invert;
}

void tensor::settensor(vtr a, vtr b, vtr c)
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
 
tensor tensor::transpose() const
{
  tensor transP;
  int i, j;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      transP.val[i][j] = val[j][i];
    }
  }

  return transP;
}

tensor tensor::operator*(const tensor &operand2) const
{
  tensor product;
  int i, j, k;
  double cval;
  
  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cval = 0.0;

      for (k = 0; k < 3; k ++) {
	cval = cval + (val[i][k] * operand2.val[k][j]);
      }
      product.val[i][j] = cval;
    }
  }

  return product;
}

void tensor::print() const
{
  int i, j;

  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      cout << val[i][j] << " ";
    }
    printf("\n");
  }
  printf("\n\n");
}


