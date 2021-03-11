// TETRA.CC
// Member functions for classes tetra
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "mesh3d.h"

using namespace std;

tetra::tetra(void )
{
  int i;
  for (i = 0; i < 4; i ++) node[i] = 0;
  n = 0;
  id = 0;
}

// set up functions
void tetra::SetTetra(node3d *nd0, node3d *nd1, node3d *nd2, node3d *nd3)
{
  node[0] = nd0;
  node[1] = nd1;
  node[2] = nd2;
  node[3] = nd3;
  
  ReArrange<node3d>(4, node, ASCENDING);
}
void tetra::SetN(int nn)
{
  if (n != nn) {
    if (id != 0) delete[] id;
    n = nn;
    id = new int[n];
  }
}
void tetra::SetId(int nn, int idx)
{
  if (nn >= 0 && nn < n) 
    id[nn] = idx;
}

// get functions
node3d *tetra::GetNodePtr(int nn)
{
  if (nn < 0 || nn >= 4) return 0;
  
  return node[nn];
}
int tetra::GetId(int nn)
{
  if (nn < 0 || nn >= n)
    return NOT_ID_YET;
  
  return id[nn];
}

// overload operator
const tetra& tetra::operator=(const tetra &right)
{
  if (&right != this) {
    int i;
    for (i = 0; i < 4; i ++)
      node[i] = right.node[i];
    n = right.n;
    if (id != 0) delete[] id;
    id = new int[n];
    for (i = 0; i < n; i ++)
      id[i] = right.id[i];
  }
  
  return *this;
}

double Volume(tetra tt)
{
  double x[4], y[4], z[4];
  int i;
  for (i = 0; i < 4; i ++) {
    x[i] = tt.GetNodePtr(i)->GetX();
    y[i] = tt.GetNodePtr(i)->GetY();
    x[i] = tt.GetNodePtr(i)->GetZ();    
  }
  double ax = x[1] - x[0], ay = y[1] - y[0], az = z[1] - z[0];
  double bx = x[2] - x[0], by = y[2] - y[0], bz = z[2] - z[0];
  double cx = x[3] - x[0], cy = y[3] - y[0], cz = z[3] - z[0];
  double vol;
  vol = ax * (by * cz - cy * bz) -
    ay * (bx * cz - cx * bz) +
    az * (bx * cy - cx * by);
  vol = fabs(vol) / 6.0;

  return vol;
}

double Volume(tetra *tt)
{
  double x[4], y[4], z[4];
  int i;
  for (i = 0; i < 4; i ++) {
    x[i] = tt->GetNodePtr(i)->GetX();
    y[i] = tt->GetNodePtr(i)->GetY();
    x[i] = tt->GetNodePtr(i)->GetZ();    
  }
  double ax = x[1] - x[0], ay = y[1] - y[0], az = z[1] - z[0];
  double bx = x[2] - x[0], by = y[2] - y[0], bz = z[2] - z[0];
  double cx = x[3] - x[0], cy = y[3] - y[0], cz = z[3] - z[0];
  double vol;
  vol = ax * (by * cz - cy * bz) -
    ay * (bx * cz - cx * bz) +
    az * (bx * cy - cx * by);
  vol = fabs(vol) / 6.0;

  return vol;
}
