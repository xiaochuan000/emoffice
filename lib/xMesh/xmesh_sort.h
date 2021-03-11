#ifndef XMESH_SORT
#define XMESH_SORT
#include <xmesh_global.h>
namespace xMesh{
	bool operator==(const vector&, const vector&);
	bool operator>(const vector&, const vector&);
	bool operator<(const vector&, const vector&);
	bool operator<(const base_node&, const base_node&);
	bool operator==(const base_node&, const base_node&);
	
	class xmesh_sort{
		public:
		bool operator()(const base_node&, const base_node&);
		bool operator()(const base_node*, const base_node*);
	};
}
#endif
