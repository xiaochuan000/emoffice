// QUADRATURE.H
// Gaussian quadrature rules for numerically integrate 'smooth' functions over
// simplexes, triangle for 2d and tetrahedra for 3d.

#ifndef QUADRATURE_H
#define QUADRATURE_H

#define one_third 0.333333333333333
#define two_third 0.666666666666667
#define one_sixth 0.166666666666667
void GetFormula1D(int, int, double *, double *, double *);

void GetFormula(int, int, double *, double *, double *, double *);
void GetGauss(int, int, int, double *, double *, double *, double *);
void GetDuffy(int, int, int, int, double *, double *, double *, double *);

#endif
