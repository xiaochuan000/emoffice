#ifndef XMESH_TOOLS_QUICKFIND_H
#define XMESH_TOOLS_QUICKFIND_H
#include <xmesh_global.h>
#include <xmesh_vector.h>
#include <xmesh_trimesh_face.h>
// #include 


// classes: Box:
// Box has the fundamental geometrical data 
// Box should keep a list of all the triangles it has
// Also it keeps the link to its children.
//  children[0]  -x -y -z
//  children[1]  -x -y +z
//  children[2]  -x +y -z
//  children[3]  -x +y +z
//  children[4]  +x -y -z
//  children[5]  +x -y +z
//  children[6]  +x +y -z
//  children[7]  +x +y +z

namespace xMesh{
	class Box;
	class MLGroup;
			
	class Box
	{
		private: 
			Real lim_[6]; //xmin xmax ymin ymax zmin zmax
		public:
			Box();
			Box(const Real,const Real,const Real,const Real,const Real,const Real);
			
			void setLimit(const Real,const Real,const Real,const Real,const Real,const Real);
			void setLimit(const int, const Real);
			Real getLimit(const int)const;	
			Real getMidPoint(const int)const;
			bool checkInbox(const vector)const;
			bool checkIntersect(const Box)const;
			bool checkIntersect(const tri_face* fc)const;
			
			void setBoxLim(const int n,tri_face**); //Check all the trangles to determine the boxlimit
			Real getSize(const int)const;
			
	};
	
	class MLGroup
	{
		private:
			int nFace_;
			tri_face** fcArray_;
			MLGroup* child_[8];
			Box  box_;
			Real minSize_;
			bool subgrid_[3];
		public:
			MLGroup();
// 			~MLGroup();
			void freeMemory();
			void setBoxLimit(const Real,const Real,const Real,const Real,const Real,const Real);
			void Initialize(const int, tri_face**, bool hardcopy=true );
			void MakeChild(Real=0.0);
			void setBoxLimit();
			Real getMinSize()const;
			void setMinSize(const Real);
			
			tri_face* findTriangle(const vector )const;
			bool isLeaf()const;
			void Display()const;
	};
}


#endif