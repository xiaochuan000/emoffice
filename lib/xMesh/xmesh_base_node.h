
#ifndef XMESH_BASE_NODE_H
#define XMESH_BASE_NODE_H
#include <xmesh_global.h>
#include <xmesh_vector.h>
namespace xMesh
{
	bool operator==(const base_node&, const base_node&);
	class base_node
	{
		friend bool operator==(const base_node&, const base_node&);
		private:
			int id_;
			vector vec_;
		public:
			base_node();
			base_node(const base_node&);
			base_node& operator=(const base_node&);
			
			void setId(int);
			int getId()const;
			
			void setVector(vector);
			vector getVector()const;
			
			void setCoordinate(double x,double y,double z);
			
			Real getx()const;
			Real gety()const;
			Real getz()const;
			Real& x();
			Real& y();
			Real& z();
			
			
	};
}

#endif
