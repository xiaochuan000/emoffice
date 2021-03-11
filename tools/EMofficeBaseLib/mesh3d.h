// MESH3D.H
// Definitions for common three dimensional geometric classes.
// They are: node3d, edge3d, tri3d, and tetra
#ifndef MESH3D_H
#define MESH3D_H

template <class T>
void ReArrange(int, T **, int);
class edge3d;
class node3d;
class tri3d;

#define NOT_ID_YET -100
#define VOLUME_NODE   0
#define SURFACE_NODE  1
#define EDGE_NODE     2
#define VERTEX_NODE   3

// types for triangles and edges
#define NONE          0
#define PEC           1
#define ABC           2
#define PMC           3

#define ZERO  1.0e-20

#define ASCENDING 1
#define DECENDING 0

#define PORIENT 0
#define NORIENT 1

class node3d {
  friend double Distance(node3d, node3d);
  friend double Distance(node3d *, node3d *);
  friend double Distance(node3d *, double, double, double);
  friend void ReArrangeNd(int, node3d **, int );
  friend double DistanceSquare(node3d *);
  
 private:
  double x, y, z;
  int id, type;
  char valid;

 public:
  node3d(double = 0.0, double = 0.0, double = 0.0); // constructor
  
  // set up procedures
  void   SetCoord(double = 0.0, double = 0.0, double = 0.0);
  void   SetId(int = 0);
  void   SetType(int = 0);
  void   SetValid(char cc) { valid = cc; };

  // get functions
  int    GetId();
  int    GetType();
  double GetX(), GetY(), GetZ();
  char GetValid() { return valid; }

  // overload operators
  const node3d &operator=(const node3d &);
  int   operator != (const node3d &) const;
  int   operator == (const node3d &) const;
  int   operator >  (const node3d &) const;
  int   operator <  (const node3d &) const;
  int   operator >= (const node3d &) const;
  int   operator <= (const node3d &) const;

  // print command
  void print();
};

// 
// The node numbering in tri3d is as follows
//                           0
//                          + +
//                         +   +
//                        +      +
//                       +        +
//                      1 + + + + + 2
// eg[0] = {1, 2}, eg[1] = {2, 0}, and eg[2] = {0, 1}
// Make a note of it and make sure in the implementation of the code, this convention is preserved.
//
class tri3d {
  friend double Area(tri3d);
  friend double Area(tri3d *);
  friend class edge3d;
  friend tri3d *GetNeighborTriPtr(tri3d *, int);
  friend int NodeInTri(node3d *, tri3d *);
  friend void GetCartesian(tri3d *, double, double, double, double *, double *, double *);
  friend void GetCartesian(tri3d *, double [], double *, double *, double *);
  friend double Distance(tri3d *, tri3d *);

 private:
  edge3d  *eg[3];
  int    n, *id;
  int    type;
  int num;
  char   done, orient;
  float  nx, ny, nz;

 public:
  tri3d(); // constructor

  // set up procedures
  
  
  void SetTri(edge3d *, edge3d *, edge3d *);
  void ReArrange();
  void SetN(int = 0);
  void SetId(int = 0, int = 0);
  void SetType(int = 0);
  void ComputeNormal();
  void NormalReverse();
  void setNum(int inputNum) { num = inputNum; }
  
  // get functions
  int GetId(int = 0);
  int GetType();
  node3d    *GetNodePtr(int = 0);
  edge3d    *GetEdgePtr(int = 0);
  void ResetDone();
  void SetDone();
  void GetValidEdges(int *);
  char IsDone();
  char GetOrient();
  void GetNormal(double *, double *, double *);
  void GetGradVtr(int, double *, double *, double *);
  void GetGradVtr(int, double, double *, double *, double *);
  void ComputeCenter(double *, double *, double *);
  double ComputeRadius();
  int getNum() { return num; }

  // overload operators
  const tri3d &operator=(const tri3d &);
  int     operator == (const tri3d &) const;
  int     operator >  (const tri3d &) const;
  int     operator <  (const tri3d &) const;
  int     operator >= (const tri3d &) const;
  int     operator <= (const tri3d &) const;

  // print command
  void print();
};

class edge3d {
  friend double Length(edge3d);
  friend double Length(edge3d *);
  friend int SameEdge(edge3d *, node3d *, node3d *);

 private:
  node3d *node[2];
  int  n, *id;
  int  type;
  int  nTri; // number of triangles that connect to this edge
  tri3d **triPtr; // pointers to the connecting triangles
	int negativeId;
 public:
  edge3d(); // constructor

  // set up procedures
  void   SetEdge(node3d *, node3d *);
  void   SetEdge_no_arrange(node3d *nd0, node3d *nd1) { 
    node[0] = nd0;
    node[1] = nd1;
  }
  void   SetN(int = 0);
  void   SetId(int, int);
  void   SetId(int );
  void   SetType(int = 0);
  void   InsertTriPtr(tri3d *);
  void   SetTriPtr(int = 0, tri3d * = 0);
  void   ResetTriNumber();
  void ReArrange();
  void SetNegativeId(int ii){negativeId=ii;}
  int  GetNegativeId(){return negativeId;}
  // get functions
  double GetX(), GetY(), GetZ();
  double GetLength();
  node3d *GetNodePtr(int = 0);
  int    GetTriNumber();
  tri3d  *GetTriPtr(int );
  int    GetN();
  int    GetId(int = 0);
  // overload operators
  const edge3d &operator=(const edge3d &);
  int    operator == (const edge3d &) const;
  int    operator >  (const edge3d &) const;
  int    operator <  (const edge3d &) const;
  int    operator >= (const edge3d &) const;
  int    operator <= (const edge3d &) const;

  // print command
  void print();
};

class tetra {
  friend double Volume(tetra);
  friend double Volume(tetra *);

 private:
  node3d *node[4];
  int    n, *id;

 public:
  tetra(); // constructor

  // set up procedures
  void   SetTetra(node3d *, node3d *, node3d *, node3d *);
  void   SetN(int = 0);
  void   SetId(int = 0, int = 0);

  // get functions
  node3d    *GetNodePtr(int = 0);
  int       GetId(int = 0);
  
  // overload operators
  const tetra &operator=(const tetra &);
};

#endif
