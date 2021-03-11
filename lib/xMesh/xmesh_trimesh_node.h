#ifndef XMESH_TRIMESH_NODE_H
#define XMESH_TRIMESH_NODE_H
#include <xmesh_global.h>
#include <xmesh_trimesh_declaration.h>
#include <xmesh_base_node.h>
#include <list>
namespace xMesh{
	class tri_node:public base_node
	{
		int flag;
		std::list<tri_face*> triList;
		std::list<tri_edge*> edgeList;
		
		public:
			tri_node();
			tri_node(const tri_node& right);
			
			
	};
}
#endif
