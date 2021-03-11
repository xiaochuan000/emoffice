#include <xmesh_trimesh_node.h>

namespace xMesh{
	tri_node::tri_node() :base_node()
	{
		flag=-1;
		triList.clear();
		edgeList.clear();
	}
	tri_node::tri_node(const tri_node& right): base_node(right){
		flag=right.flag;
		triList=right.triList;
		edgeList=right.edgeList;
		
	}
}
