#ifndef XMESH_TRIMESH_FACE_H
#define XMESH_TRIMESH_FACE_H
#include <xmesh_global.h>
#include <xmesh_trimesh_declaration.h>
#include <xmesh_base_face.h>


//Convention:
//             0
//            / \
//           2   1
//          /     \
//        1 ---0---2
//  Direction: 
//       Edge: 0   Node1 -> Node2
//       Edge: 1   Node2 -> Node0
//       Edge: 2   Node0 -> Node1

namespace xMesh{
	class tri_face:public base_face{
		private:
			bool order_[3];
			int flag_;
			bool normal_; //true or false, determine the calculation of normal if false,
			int cnt_[2];
		public:
			tri_face();
			tri_face(const tri_face& right);
			
			tri_face(tri_edge* ,tri_edge*,tri_edge*);
			void setEdge3(tri_edge* ,tri_edge*,tri_edge*);
			void setNormal(bool);
			bool getNormalFlag()const;
			vector getCenter()const; 
			tri_node* getNode(int)const;
			bool getOrder(int i)const;
			//Mesh Quality 
			Real getAspectRatio()const;
			Real getAngleRad(int i)const;
			Real getAngleDeg(int i)const;
			Real getInnerRadius()const;
			Real getOuterRadius()const;
			Real getArea()const;
			vector getNormal()const;
			void reverseDirection();
			void setFlag(int i);
			int getFlag()const;
			int getLocalNodeNum(const tri_node*)const;
			int getLocalEdgeNum(const tri_edge*)const;
			void getTriNodes3(int* exp)const ;
					
			void print()const;
			bool isInside(const vector n)const;
			Real distanceCenter(const vector nn) const;
			Real distanceEdge(const vector nn) const;
			void checkEdge() ;
			int findEdgeIndex(tri_edge* input)const;
                        tri_edge* getTriEdge(int i)const;
			void getBary(const vector ,Real*)const;
			void setCnt(int ,int);
			int getCnt(int=0)const;
			
			tri_node* getThirdNode(const tri_edge* edge)const;
	};
	
	void printTri(tri_face* fc);
	bool checkAntiParallel(const vector a,const vector b);
	bool checkParallel(const vector a,const vector b);
}
#endif
