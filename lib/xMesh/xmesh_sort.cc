#include <xmesh_sort.h>
#include <xmesh_vector.h>
#include <xmesh_base_node.h>
#include <xmesh_base_edge.h>

namespace xMesh{
	bool operator==(const vector& a,const vector& b){
		if(a.x()==b.x()  && a.y()==b.y() && a.z()==b.z())
			return true;
		else
		{
#ifndef VECTOR_STRICK_EQUAL
		vector err=a-b;	
		if(err.norm()<TOLERANCE_SORT*1.733)
			return true;
#endif
		return false;
		}
	}
	bool operator<(const vector& a,const vector& b){
		if(a==b)
			return false;
		for(int i=0;i<3;i++)
		{
			if(a.component[i]<b.component[i]-0.0*TOLERANCE_SORT)
				return true;
			else if(a.component[i]>b.component[i]+0.0*TOLERANCE_SORT)
				return false;
		}		
		return false;
	}
	bool operator >(const vector& a,const vector& b){
		if(a==b)
			return false;
		if(a<b)
			return false;
		return true;
	}
	bool operator<(const base_node& a, const base_node& b){
		return a.getVector()<b.getVector();
	}
	bool operator==(const base_node& a, const base_node& b){
		return a.getVector()==b.getVector();
	}
	bool xmesh_sort::operator()(const base_node&a , const base_node&b){
		return a<b;
	}
	bool xmesh_sort::operator()(const base_node*a , const base_node*b){
		return a->getVector()<b->getVector();
	}
}
