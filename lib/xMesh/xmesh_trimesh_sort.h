#ifndef XMESH_TRIMESH_SORT_H
#define XMESH_TRIMESH_SORT_H
#include <xmesh_global.h>
#include <xmesh_trimesh_declaration.h>
#include <xmesh_trimesh_edge.h>

namespace xMesh{
	const double TOLERANCE_NODE=1.e-5;
	
	bool operator<(const tri_node&,const tri_node&);
	bool operator==(const tri_node&,const tri_node&);
	bool operator<(const tri_edge&,const tri_edge&);
	bool operator==(const tri_edge&,const tri_edge&);
	bool operator<(const tri_face&,const tri_face&);
	bool operator==(const tri_face&,const tri_face&);
	class tri_sort{
		public:
			bool operator()(const tri_edge& ,const tri_edge&);
			bool operator()(const tri_edge* ,const tri_edge*);
			bool operator()(const tri_node& ,const tri_node&);
			bool operator()(const tri_node* ,const tri_node*);
			bool operator()(const tri_face& ,const tri_face&);
			bool operator()(const tri_face* ,const tri_face*);
	};
	class tri_sort_byId{
		public:
			bool operator()(const tri_edge& ,const tri_edge&);
			bool operator()(const tri_edge* ,const tri_edge*);
	};
}
#endif
