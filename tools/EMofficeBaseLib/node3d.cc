// NODE3D.CC
// Member functions for classes node3d
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "mesh3d.h"

using namespace std;

void ReArrangeNd(int n, node3d **nd, int OPT)
{
  int i, j;
  node3d *tmpNODE;

  for (i = 0; i < n; i ++) {
    for (j = (i + 1); j < n; j ++) {
      if ((OPT == ASCENDING && (*nd[i]) > (*nd[j])) ||
	  (OPT == DECENDING && (*nd[i]) < (*nd[j]))) {
	tmpNODE = nd[i];
	nd[i] = nd[j];
	nd[j] = tmpNODE;
      }
    }
  }
}

// constructor for node3d
node3d::node3d(double xval, double yval, double zval)
{
  x = xval;
  y = yval;
  z = zval;

  id = NOT_ID_YET;
  type = VOLUME_NODE;
  valid = 0;
}

// the member functions for node3d. begin with the set up procedures.
void node3d::SetCoord(double xval, double yval, double zval)
{
  x = xval;
  y = yval;
  z = zval;
}
void node3d::SetId(int n) { id = n; }
void node3d::SetType(int n) { type = n; }

// get functions for node3d
int node3d::GetId() { return id; }
int node3d::GetType() { return type; }
double node3d::GetX() { return x; }
double node3d::GetY() { return y; }
double node3d::GetZ() { return z; }

// overload operators for node3d
// Determine whether two nodes are not equal and return
// 1 if not equal and 0 else
int node3d::operator!=(const node3d &right) const
{
  if (fabs(x - right.x) > ZERO) return 1;
  if (fabs(y - right.y) > ZERO) return 1;
  if (fabs(z - right.z) > ZERO) return 1;

  return 0;
}
// Determine whether two nodes are equal and return
// 1 if equal and 0 else
int node3d::operator==(const node3d &right) const
{
  if (fabs(x - right.x) > ZERO) return 0;
  if (fabs(y - right.y) > ZERO) return 0;
  if (fabs(z - right.z) > ZERO) return 0;

  return 1;
}
// Perform binary comparison to determine whether the current
// node is "larger" than the right node.
// If the current node is "larger" than the right
// return 1 and 0 else.
int node3d::operator>(const node3d &right) const
{
  if (x > right.x + ZERO) return 1;
  if (x < right.x - ZERO) return 0;
  
  if (y > right.y + ZERO) return 1;
  if (y < right.y - ZERO) return 0;
  
  if (z > right.z + ZERO) return 1;
  if (z < right.z - ZERO) return 0;

  return 0;
}
int node3d::operator>=(const node3d &right) const
{
  if (x > right.x + ZERO) return 1;
  if (x < right.x - ZERO) return 0;
  
  if (y > right.y + ZERO) return 1;
  if (y < right.y - ZERO) return 0;
  
  if (z > right.z + ZERO) return 1;
  if (z < right.z - ZERO) return 0;

  return 1;
}
// Perform binary comparison to determine whether the current
// node is "smaller" than the right node.
// If the current node is "smaller" than the right
// return 1 and 0 else.
int node3d::operator<(const node3d &right) const
{
  if (x > right.x + ZERO) return 0;
  if (x < right.x - ZERO) return 1;
  
  if (y > right.y + ZERO) return 0;
  if (y < right.y - ZERO) return 1;
  
  if (z > right.z + ZERO) return 0;
  if (z < right.z - ZERO) return 1;

  return 0;  
}
int node3d::operator<=(const node3d &right) const
{
  if (x > right.x + ZERO) return 0;
  if (x < right.x - ZERO) return 1;
  
  if (y > right.y + ZERO) return 0;
  if (y < right.y - ZERO) return 1;
  
  if (z > right.z + ZERO) return 0;
  if (z < right.z - ZERO) return 1;

  return 1;  
}

// Overload the assignment operator
const node3d &node3d::operator=(const node3d &right)
{
  if (&right != this) {
    x = right.x;
    y = right.y;
    z = right.z;

    id = right.id;
    type = right.type;
  }

  return *this;
}

// computing the distance between two nodes
double Distance(node3d nd0, node3d nd1)
{
  double dd;
  dd = (nd0.GetX() - nd1.GetX()) * (nd0.GetX() - nd1.GetX()) +
    (nd0.GetY() - nd1.GetY()) * (nd0.GetY() - nd1.GetY()) +
    (nd0.GetZ() - nd1.GetZ()) * (nd0.GetZ() - nd1.GetZ());
  
  return sqrt(dd);
}

double Distance(node3d *nd, double x, double y, double z)
{
  double dd;
  dd = (nd->GetX() - x) * (nd->GetX() - x) +
    (nd->GetY() - y) * (nd->GetY() - y) +
    (nd->GetZ() - z) * (nd->GetZ() - z);
  
  return sqrt(dd);
}

double Distance(node3d *nd0, node3d *nd1)
{
  double dd;
  
  dd = (nd0->GetX() - nd1->GetX()) * (nd0->GetX() - nd1->GetX()) +
    (nd0->GetY() - nd1->GetY()) * (nd0->GetY() - nd1->GetY()) +
    (nd0->GetZ() - nd1->GetZ()) * (nd0->GetZ() - nd1->GetZ());
  
  return sqrt(dd);
}

double DistanceSquare(node3d *nd)
{
  double dd;

  dd = nd->GetX() * nd->GetX() +
    nd->GetY() * nd->GetY() +
    nd->GetZ() * nd->GetZ();
  
  return dd;
}

void node3d::print()
{
  cout << "id " << id << ":  ( " << x << ", " << y << ", " << z << ") " << endl;
}
