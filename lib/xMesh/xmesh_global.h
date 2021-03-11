#ifndef XMESH_GLOBAL_H
#define XMESH_GLOBAL_H
//This header serves as declaration of base class and basic data format;
#include <complex>
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#define DOUBLE_PRECISION
namespace xMesh
{
#ifdef DOUBLE_PRECISION
	typedef double Real;
#else
	typedef float Real;
#endif
	
	typedef std::complex<Real> Complex;
	typedef std::complex<float> FloatComplex;
	
	class vector;
	class base_node;
	class base_edge;
	class base_face; 
	class base_element; 
	class xmesh_sort;
	
	
//	const Real xmeshPI= 3.14159265358979323846264338327950288;
	const Real xmeshPI= cos(-1.0);
	const Real MAX_DOUBLEFLOAT=1.0e10;
	const Real TOLERANCE=1.e-5;
	const Real TOLERANCE_SORT=TOLERANCE;
}
#endif
