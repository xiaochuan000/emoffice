// NODE3D.CC
// Member functions for classes node3d
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "mesh3d.h"

using namespace std;

// constructor
edge3d::edge3d(void )
{
  node[0] = node[1] = 0;
  // for loop-star mom, we don't need to number edges
  n = 0;
  id = 0;
  // initialization
  type = NONE;
  nTri = 0;
  triPtr = 0;
}

// set up procedures
void edge3d::SetEdge(node3d *nd0, node3d *nd1)
{
  // form the edge from the "smaller" node to the "bigger" node
  if ((*nd0) < (*nd1)) {
    node[0] = nd0;
    node[1] = nd1;
  } else {
    node[0] = nd1;
    node[1] = nd0;
  }
}

// set up procedures
void edge3d::ReArrange()
{
  if ((*(node[0])) > (*(node[1]))) {
    node3d *tmpNode = node[0];
    node[0] = node[1];
    node[1] = tmpNode;
  }
}

void edge3d::SetN(int nn) {
  if (n != nn) {
    if (id != 0) delete id;
    n = nn;
    id = new int[n];
  }
}

int edge3d::GetN() { return n; }

void edge3d::SetId(int nn, int idx)
{
  if (nn >= 0 && nn < n) {
    id[nn] = idx;
  }
}

int edge3d::GetId(int nn) { return id[nn]; }

void edge3d::SetId(int idx)
{
  if (n != 0)
    id[0] = idx;
}

void edge3d::SetType(int typeNum) { type = typeNum; }

void edge3d::InsertTriPtr(tri3d *tri)
{
  if (tri == 0) return;

  if (triPtr == 0) triPtr = new tri3d*[2];
  int i;
  for (i = 0; i < nTri; i ++)
    if (triPtr[i] == tri) return; // already there

  if (nTri >= 2) {
    tri3d **tmpPtr;

    tmpPtr = new tri3d*[nTri + 1];
    for (i = 0; i < nTri; i ++)
      tmpPtr[i] = triPtr[i]; // copy the existing ones to temp
    tmpPtr[nTri] = tri;
    nTri ++;
    delete[] triPtr;
    triPtr = tmpPtr;
  } else {
    triPtr[nTri] = tri;

    nTri ++;
  }
}

void edge3d::SetTriPtr(int id, tri3d *tri)
{
  if (id < 0 || id >= nTri) return;

  triPtr[id] = tri;
}

// get functions
double edge3d::GetX() {
  return node[1]->GetX() - node[0]->GetX();
}
double edge3d::GetY()
{
  return node[1]->GetY() - node[0]->GetY();
}
double edge3d::GetZ()
{
  return node[1]->GetZ() - node[0]->GetZ();
}
double edge3d::GetLength()
{
  return Length(this);
}
node3d *edge3d::GetNodePtr(int nn)
{
  if (nn != 0 && nn != 1) return 0;

  return node[nn];
}
int edge3d::GetTriNumber() { return nTri; }
tri3d *edge3d::GetTriPtr(int nn)
{
  if (nn < 0 || nn >= nTri) return 0;

  return triPtr[nn];
}

// overload operators
const edge3d &edge3d::operator=(const edge3d &right)
{
  if (&right != this) {
    int i;
    node[0] = right.node[0];
    node[1] = right.node[1];
    type = right.type;
    n = right.n;
    id = new int[n];
    for (i = 0; i < n; i ++)
      id[i] = right.id[i];
    nTri = right.nTri;
    triPtr = new tri3d*[nTri];
    for (i = 0; i < nTri; i ++)
      triPtr[i] = right.triPtr[i];
  }
  return *this;
}
int edge3d::operator==(const edge3d &right) const
{
  if (node[0] != right.node[0]) return 0;
  if (node[1] != right.node[1]) return 0;

  return 1;
}
int edge3d::operator>(const edge3d &right) const
{
  if ((*(node[0])) > (*(right.node[0]))) return 1;
  if ((*(node[0])) < (*(right.node[0]))) return 0;
  if ((*(node[1])) > (*(right.node[1]))) return 1;
  if ((*(node[1])) < (*(right.node[1]))) return 0;

  return 0;
}
int edge3d::operator>=(const edge3d &right) const
{
  if ((*(node[0])) > (*(right.node[0]))) return 1;
  if ((*(node[0])) < (*(right.node[0]))) return 0;
  if ((*(node[1])) > (*(right.node[1]))) return 1;
  if ((*(node[1])) < (*(right.node[1]))) return 0;

  return 1;
}
int edge3d::operator<(const edge3d &right) const
{
  if ((*(node[0])) > (*(right.node[0]))) return 0;
  if ((*(node[0])) < (*(right.node[0]))) return 1;
  if ((*(node[1])) > (*(right.node[1]))) return 0;
  if ((*(node[1])) < (*(right.node[1]))) return 1;

  return 0;
}
int edge3d::operator<=(const edge3d &right) const
{
  if ((*(node[0])) > (*(right.node[0]))) return 0;
  if ((*(node[0])) < (*(right.node[0]))) return 1;
  if ((*(node[1])) > (*(right.node[1]))) return 0;
  if ((*(node[1])) < (*(right.node[1]))) return 1;

  return 1;
}


double Length(edge3d eg)
{
  double dd;

  dd = eg.GetX() * eg.GetX() +
    eg.GetY() * eg.GetY() +
    eg.GetZ() * eg.GetZ();

  return sqrt(dd);
}

double Length(edge3d *eg)
{
  double dd;

  dd = eg->GetX() * eg->GetX() +
    eg->GetY() * eg->GetY() +
    eg->GetZ() * eg->GetZ();

  return sqrt(dd);
}

void edge3d::print()
{
  node[0]->print();
  node[1]->print();
  cout << endl;
}

int SameEdge(edge3d *eg, node3d *nd0, node3d *nd1)
{
  if (eg->node[0] != nd0 && eg->node[0] != nd1) return 0;
  if (eg->node[1] != nd0 && eg->node[1] != nd1) return 0;

  return 1;
}

void edge3d::ResetTriNumber()
{
  nTri = 0;
  delete[] triPtr;

  triPtr = 0;
}
