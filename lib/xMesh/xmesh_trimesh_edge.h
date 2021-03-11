#ifndef XMESH_TRIMESH_EDGE
#define XMESH_TRIMESH_EDGE
#include <xmesh_global.h>
#include <xmesh_trimesh_declaration.h>
#include <xmesh_base_edge.h>
namespace xMesh{
	class tri_edge: public base_edge{
		private:
			int 		cnt_[2];
			int 		localCnt_[2];
			tri_face**	tri_;
			int		nTri_;	
		public:
			tri_edge();
			tri_edge(const tri_edge&);
                        tri_edge& operator=(const tri_edge&);
			tri_edge(base_node*,base_node*);
			~tri_edge();
			
			//find the distance of a vector to this edge, 
			Real 	distanceExt(const vector)const;
			Real 	distance(const vector)const;
			vector 	getVector()const;
			
			void 	setNTri(int=2);
			int 	getNTri()const;
			void	setTri(int i,tri_face*);
			tri_face*	getTri(int) const;
			tri_face* 	findOtherTriangle(const tri_face*)const;
			Real  	getDistance(const vector nn) const;
			void addTriangle( tri_face* );
			vector getMidPoint()const;
			void  setCnt(int i,int j );
			int getCnt(int i=0)const;
			int bindTriangle( tri_face*, tri_face*);
	};
	void printEdge(tri_edge* iedgep);

}
#endif
