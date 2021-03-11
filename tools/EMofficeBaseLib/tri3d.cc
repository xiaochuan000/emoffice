// TRI3D.CC
// Member functions for classes tri3d
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "mesh3d.h"
#include "vtr.h"

using namespace std;

template <class T>
void ReArrange(int n, T **nd, int OPT)
{
  int i, j;
  T *tmp;

  for (i = 0; i < n; i ++) {
    for (j = (i + 1); j < n; j ++) {
      if ((OPT == ASCENDING && (*nd[i]) > (*nd[j])) ||
	  (OPT == DECENDING && (*nd[i]) < (*nd[j]))) {
	tmp = nd[i];
	nd[i] = nd[j];
	nd[j] = tmp;
      }
    }
  }
}

// constructor for tri3d
tri3d::tri3d(void )
{
  int i;
  for (i = 0; i < 3; i ++) eg[i] = 0;
  n = 1; // only one star per triangle for now
  id = new int[n];
  type = NONE;
  done = 0;
  orient = PORIENT;
}

// set up procedures for tri3d
void tri3d::SetTri(edge3d *eg0, edge3d *eg1, edge3d *eg2)
{
  eg[0] = eg0;
  eg[1] = eg1;
  eg[2] = eg2;
}

void tri3d::ReArrange() {
  node3d *nd[3];

  nd[0] = eg[0]->GetNodePtr(0);
  nd[1] = eg[0]->GetNodePtr(1);
  if (eg[1]->GetNodePtr(0) != nd[0] &&
      eg[1]->GetNodePtr(0) != nd[1])
    nd[2] = eg[1]->GetNodePtr(0);
  else
    nd[2] = eg[1]->GetNodePtr(1);
  
  ReArrangeNd(3, nd, ASCENDING);
  int j;
  edge3d *tmpEdge[3];
  for (j = 0; j < 3; j ++) {
    int j1 = (j + 1) % 3;
    int j2 = (j + 2) % 3;
    
    int k;
    for (k = 0; k < 3; k ++) {
      if (SameEdge(eg[k], nd[j1], nd[j2]))
	tmpEdge[j] = eg[k];
    }
  }
  eg[0] = tmpEdge[0];
  eg[1] = tmpEdge[1];
  eg[2] = tmpEdge[2];
}

void tri3d::SetN(int nn) { 
  if (n != nn) {
    n = nn; 
    if (id != 0) delete[] id;
    id = new int[n];
  }
}
void tri3d::SetId(int nn, int idx)
{
  if (nn >= 0 && nn < n) {
    id[nn] = idx;
  }
}
void tri3d::SetType(int typeNum) { type = typeNum; }

// get functions for tri3d
int tri3d::GetId(int nn) {
  if (nn < 0 || nn >= n) return NOT_ID_YET;

  return id[nn];
}
int tri3d::GetType() { return type; }
node3d *tri3d::GetNodePtr(int nn)
{
  if (nn < 0 || nn >= 3) return 0;

  switch (nn) {
  case 0: return eg[2]->GetNodePtr(0);
  case 1: return eg[0]->GetNodePtr(0);
  case 2: return eg[0]->GetNodePtr(1);
  }
}

// overload operators
const tri3d &tri3d::operator=(const tri3d &right)
{
  if (&right != this) {
    int i;
    for (i = 0; i < 3; i ++) eg[i] = right.eg[i];
    n = right.n;
    id = new int[n];
    for (i = 0; i < n; i ++)
      id[i] = right.id[i];
    type = right.type;
  }
}
int tri3d::operator==(const tri3d &right) const
{
  if (eg[0] != right.eg[0]) return 0;
  if (eg[1] != right.eg[1]) return 0;
  if (eg[2] != right.eg[2]) return 0;

  return 1;
}
int tri3d::operator>(const tri3d &right) const
{
  int i;
  for (i = 0; i < 3; i ++) {
    if ((*(eg[i])) > (*(right.eg[i]))) return 1;
    if ((*(eg[i])) < (*(right.eg[i]))) return 0;
  }
  
  return 0;
}
int tri3d::operator<(const tri3d &right) const
{
  int i;
  for (i = 0; i < 3; i ++) {
    if ((*(eg[i])) > (*(right.eg[i]))) return 0;
    if ((*(eg[i])) < (*(right.eg[i]))) return 1;
  }
  
  return 0;
}
int tri3d::operator>=(const tri3d &right) const
{
  int i;
  for (i = 0; i < 3; i ++) {
    if ((*(eg[i])) > (*(right.eg[i]))) return 1;
    if ((*(eg[i])) < (*(right.eg[i]))) return 0;
  }
  
  return 1;
}
int tri3d::operator<=(const tri3d &right) const
{
  int i;
  for (i = 0; i < 3; i ++) {
    if ((*(eg[i])) > (*(right.eg[i]))) return 0;
    if ((*(eg[i])) < (*(right.eg[i]))) return 1;
  }
  
  return 1;
}

void tri3d::ComputeNormal()
{
  vtr avtr, bvtr, nvtr;

  avtr.setvtr(eg[2]->GetX(), eg[2]->GetY(), eg[2]->GetZ());
  bvtr.setvtr(eg[1]->GetX(), eg[1]->GetY(), eg[1]->GetZ());
  nvtr = avtr * bvtr;
  nvtr.unitvtr();

  nx = nvtr.getx();
  ny = nvtr.gety();
  nz = nvtr.getz();
}

void tri3d::NormalReverse()
{
  nx = -nx;
  ny = -ny;
  nz = -nz;

  orient = NORIENT;
}

char tri3d::GetOrient() { return orient; }

void tri3d::GetValidEdges(int triEdge[])
{
  int i;
  for (i = 0; i < 3; i ++) {
    if (eg[i]->GetTriNumber() == 1) triEdge[i] = 0;
    else
      triEdge[i] = 1;
  }
}

void tri3d::ResetDone() { done = 0; }
void tri3d::SetDone() { done = 1; }
char tri3d::IsDone() { return done; }

edge3d* tri3d::GetEdgePtr(int nn) 
{
  if (nn < 0 || nn >= 3) return 0;
  
  return eg[nn];
}

void tri3d::GetNormal(double *xn, double *yn, double *zn)
{
  (*xn) = (double)(nx);
  (*yn) = (double)(ny);
  (*zn) = (double)(nz);
}

void tri3d::GetGradVtr(int nn, double *gx, double *gy, double *gz)
{
  double area = Area(this);

  if (nn < 0 || nn >= 3) {
    (*gx) = (*gy) = (*gz) = 0.0;
    return;
  }

  vtr nvtr, tvtr, gvtr;
  tvtr.setvtr(eg[nn]->GetX(), eg[nn]->GetY(), eg[nn]->GetZ());
  nvtr.setvtr((double)nx, (double)ny, (double)nz);
  gvtr = nvtr * tvtr;
  gvtr = gvtr * (1.0 / (2.0 * area));

  node3d *pt0, *pt1;
  pt1 = GetNodePtr(nn);
  pt0 = eg[nn]->GetNodePtr(0);
  tvtr.setvtr(pt1->GetX() - pt0->GetX(), pt1->GetY() - pt0->GetY(), pt1->GetZ() - pt0->GetZ());
  if (dotP(gvtr, tvtr) < 0.0) {
    (*gx) = -gvtr.getx();
    (*gy) = -gvtr.gety();
    (*gz) = -gvtr.getz();
  } else {
    (*gx) = gvtr.getx();
    (*gy) = gvtr.gety();
    (*gz) = gvtr.getz();
  }
}

void tri3d::GetGradVtr(int nn, double area, double *gx, double *gy, double *gz)
{
  if (nn < 0 || nn >= 3) {
    (*gx) = (*gy) = (*gz) = 0.0;
    return;
  }

  vtr nvtr, tvtr, gvtr;
  tvtr.setvtr(eg[nn]->GetX(), eg[nn]->GetY(), eg[nn]->GetZ());
  nvtr.setvtr((double)nx, (double)ny, (double)nz);
  gvtr = nvtr * tvtr;
  gvtr = gvtr * (1.0 / (2.0 * area));

  node3d *pt0, *pt1;
  pt1 = GetNodePtr(nn);
  pt0 = eg[nn]->GetNodePtr(0);
  tvtr.setvtr(pt1->GetX() - pt0->GetX(), pt1->GetY() - pt0->GetY(), pt1->GetZ() - pt0->GetZ());
  if (dotP(gvtr, tvtr) < 0.0) {
    (*gx) = -gvtr.getx();
    (*gy) = -gvtr.gety();
    (*gz) = -gvtr.getz();
  } else {
    (*gx) = gvtr.getx();
    (*gy) = gvtr.gety();
    (*gz) = gvtr.getz();
  }
}

void tri3d::print()
{
  cout << "NODES " << endl;
  GetNodePtr(0)->print();
  GetNodePtr(1)->print();
  GetNodePtr(2)->print();
  cout << "EDGES" << endl;
  eg[0]->print();
  eg[1]->print();
  eg[2]->print();
  cout << endl;

  cout << "Normal: ( " << nx << ", " << ny << ", " << nz << " )" << endl;
  cout << "Orientation ";
  if (GetOrient() == 0) cout << " 0 " << endl;
  else
    if (GetOrient() == 1) cout << " 1 " << endl;

  cout << "Unknown Number " << id[0] << endl << endl;
}

double Area(tri3d *tt)
{
  edge3d *eg0, *eg1;
  eg0 = tt->GetEdgePtr(0);
  eg1 = tt->GetEdgePtr(1);

  vtr avtr(eg0->GetX(), eg0->GetY(), eg0->GetZ());
  vtr bvtr(eg1->GetX(), eg1->GetY(), eg1->GetZ());
  vtr nvtr = avtr * bvtr;

  return 0.5 * nvtr.magnitude();
}

double Area(tri3d tt)
{
  edge3d *eg0, *eg1;
  eg0 = tt.GetEdgePtr(0);
  eg1 = tt.GetEdgePtr(1);

  vtr avtr(eg0->GetX(), eg0->GetY(), eg0->GetZ());
  vtr bvtr(eg1->GetX(), eg1->GetY(), eg1->GetZ());
  vtr nvtr = avtr * bvtr;

  return 0.5 * nvtr.magnitude();
}

tri3d *GetNeighborTriPtr(tri3d *tt, int nn)
{
  if (nn < 0 || nn >= 3) return 0;
  
  edge3d *eg;
  eg = tt->GetEdgePtr(nn);
  int i;
  for (i = 0; i < eg->GetTriNumber(); i ++) {
    if (eg->GetTriPtr(i) != tt)
      return eg->GetTriPtr(i);
  }

  return 0;
}

int NodeInTri(node3d *nd, tri3d *tt)
{
  int i;
  for (i = 0; i < 3; i ++) {
    if (tt->GetNodePtr(i) == nd) return (i + 1);
  }

  return 0;
}

// GetCartesian takes as inputs tt (the triangle), (zeta0, zeta1, zeta2) the barycentric coordinates
// It returns the corresponding Cartesian coordinates (x, y, z) at the point. 
void GetCartesian(tri3d *tt, 
		   double zeta0, double zeta1, double zeta2,
		   double *x, double *y, double *z)
{
  int i;
  node3d *nd;
  double zc[3];
  zc[0] = zeta0; 
  zc[1] = zeta1;
  zc[2] = zeta2;
  (*x) = (*y) = (*z) = 0.0;
  for (i = 0; i < 3; i ++) {
    nd = tt->GetNodePtr(i);

    (*x) += zc[i] * nd->GetX();
    (*y) += zc[i] * nd->GetY();
    (*z) += zc[i] * nd->GetZ();
  }
}

// GetCartesian takes as inputs tt (the triangle), (zeta0, zeta1, zeta2) the barycentric coordinates
// It returns the corresponding Cartesian coordinates (x, y, z) at the point. 
void GetCartesian(tri3d *tt, 
		  double zc[],
		  double *x, double *y, double *z)
{
  int i;
  node3d *nd;

  (*x) = (*y) = (*z) = 0.0;
  for (i = 0; i < 3; i ++) {
    nd = tt->GetNodePtr(i);

    (*x) += zc[i] * nd->GetX();
    (*y) += zc[i] * nd->GetY();
    (*z) += zc[i] * nd->GetZ();
  }
}

double Distance(tri3d *t1, tri3d *t2)
{
  double x0, y0, z0;
  double x1, y1, z1;
  double Rmin = 1.0e30;

  int i;
  for (i = 0; i < 3; i ++) {
    x0 = t1->GetNodePtr(i)->GetX();
    y0 = t1->GetNodePtr(i)->GetY();
    z0 = t1->GetNodePtr(i)->GetZ();
    
    int j;
    for (j = 0; j < 3; j ++) {
      x1 = t2->GetNodePtr(j)->GetX();
      y1 = t2->GetNodePtr(j)->GetY();
      z1 = t2->GetNodePtr(j)->GetZ();
      double dd = (x1 - x0) * (x1 - x0) + (y1 - y0) * ( y1 - y0) + (z1 - z0) * (z1 - z0);

      if (dd < Rmin) Rmin = dd;
    }
  }

  return sqrt(Rmin);
}

vtr DirectLine(node3d *nd0, node3d *nd1)
{
  vtr vv(nd1->GetX() - nd0->GetX(),
	 nd1->GetY() - nd0->GetY(),
	 nd1->GetZ() - nd0->GetZ());
  
  return vv;
}

void tri3d::ComputeCenter(double *x, double *y, double *z)
{
  vtr L10 = DirectLine(GetNodePtr(1), GetNodePtr(0));
  vtr L12 = DirectLine(GetNodePtr(1), GetNodePtr(2));
  vtr L02 = DirectLine(GetNodePtr(0), GetNodePtr(2));
  
  vtr nd = L10 - L12 * (dotP(L10, L12) / L12.magSquare());
  double d = dotP(L10, L02) / dotP(nd, L02) * 0.5;
  
  (*x) = 0.5 * (GetNodePtr(1)->GetX() + GetNodePtr(2)->GetX()) + d * nd.getx();
  (*y) = 0.5 * (GetNodePtr(1)->GetY() + GetNodePtr(2)->GetY()) + d * nd.gety();  
  (*z) = 0.5 * (GetNodePtr(1)->GetZ() + GetNodePtr(2)->GetZ()) + d * nd.getz();  
}

double tri3d::ComputeRadius()
{
  double cx, cy, cz;
  ComputeCenter(&cx, &cy, &cz);

  return Distance(GetNodePtr(0), cx, cy, cz);
}
