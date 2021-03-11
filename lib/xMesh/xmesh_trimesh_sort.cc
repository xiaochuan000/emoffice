#include <xmesh_vector.h>
#include <xmesh_trimesh_node.h>
#include <xmesh_trimesh_sort.h>
#include <xmesh_trimesh_face.h>
#include <algorithm>
#include <set>
#include <algorithm>
#include <iostream>
namespace xMesh{
	bool operator ==(const tri_edge& a,const tri_edge& b){
// 		std::cout<<"Comparison ==called!\n"<<std::flush;
		assert(a.getNNode()==2);
		assert(b.getNNode()==2);
		
		if(a.getNode(0)->getVector() == b.getNode(0)->getVector() &&
				 a.getNode(1)->getVector() == b.getNode(1)->getVector()	 )
			return true;
		if(a.getNode(1)->getVector() == b.getNode(0)->getVector() &&
				 a.getNode(0)->getVector() == b.getNode(1)->getVector()	 )
			return true;
		return false;
	}
	
	bool operator <(const tri_edge& a,const tri_edge& b){
// 		std::cout<<"Comparison called!\n"<<std::flush;
		if(a==b)
			return false;
		
		vector amin=a.getNode(0)->getVector();
		vector amax=a.getNode(1)->getVector();
		if(amin>amax)
			std::swap<vector>(amin,amax);
		
		vector bmin=b.getNode(0)->getVector();
		vector bmax=b.getNode(1)->getVector();
		if(bmin>bmax)
			std::swap<vector>(bmin,bmax);
		if(amin<bmin)
			return true;
		if(amin>bmin)
			return false;
		if(amax<bmax)
			return true;
		if(amax>bmax)
			return false;
		return false;
		
	}
	bool tri_sort::operator()(const tri_edge& a,const tri_edge& b){
		return a<b;
	}
	bool tri_sort::operator()(const tri_edge* a,const tri_edge* b){
		return  (*a)< (*b);
	}
	bool tri_sort_byId::operator()(const tri_edge& a,const tri_edge& b){
		int ida[2],idb[2];
		ida[0]=a.getNode(0)->getId();
		ida[1]=a.getNode(1)->getId();
		idb[0]=b.getNode(0)->getId();
		idb[1]=b.getNode(1)->getId();
		
		if(ida[0]==idb[0] &&ida[1]==idb[1]){
			return false;
		}
		if(ida[1]==idb[0] &&ida[0]==idb[1]){
			return false;
		}
		if(std::min<int>(ida[0],ida[1])<std::min<int>(idb[0],idb[1]))
			return true;
		if(std::min<int>(ida[0],ida[1])>std::min<int>(idb[0],idb[1]))
			return false;
		
		if(std::max<int>(ida[0],ida[1])<std::max<int>(idb[0],idb[1]))
			return true;
		if(std::max<int>(ida[0],ida[1])>std::max<int>(idb[0],idb[1]))
			return false;

		return false;
	}
	bool tri_sort_byId::operator()(const tri_edge* a,const tri_edge* b){
		int ida[2],idb[2];
		ida[0]=a->getNode(0)->getId();
		ida[1]=a->getNode(1)->getId();
		idb[0]=b->getNode(0)->getId();
		idb[1]=b->getNode(1)->getId();
		
		if(ida[0]==idb[0] &&ida[1]==idb[1]){
			return false;
		}
		if(ida[1]==idb[0] &&ida[0]==idb[1]){
			return false;
		}
		if(std::min<int>(ida[0],ida[1])<std::min<int>(idb[0],idb[1]))
			return true;
		if(std::min<int>(ida[0],ida[1])>std::min<int>(idb[0],idb[1]))
			return false;
		
		if(std::max<int>(ida[0],ida[1])<std::max<int>(idb[0],idb[1]))
			return true;
		if(std::max<int>(ida[0],ida[1])>std::max<int>(idb[0],idb[1]))
			return false;

		return false;
	}
	bool operator ==(const tri_node& a,const tri_node& b){
		vector distance=a.getVector()-b.getVector();
		
		if(distance.norm()<TOLERANCE_NODE)
			return true;
		return false;
	}
	bool operator <(const tri_node& a,const tri_node& b){
		if(a==b)
			return false;
		vector aa=a.getVector();
		vector bb=b.getVector();
		if(aa.getx()<bb.getx())
			return true;
		else if(aa.getx()>bb.getx()) 
			return false;
		else if(aa.gety()<bb.gety())
			return true;
		else if(aa.gety()>bb.gety()) 
			return false;
		else if(aa.getz()<bb.getz())
			return true;
		else if(aa.getz()>bb.getz()) 
			return false;
		return false;
	}
	bool tri_sort::operator()(const tri_node& a,const tri_node& b)
	{
		return a<b;
	}
	bool tri_sort::operator()(const tri_node* a,const tri_node* b)
	{
		return (*a)<(*b);
	}
	bool operator ==(const tri_face& a,const tri_face& b){
		std::set<vector> nodeA,nodeB;
		nodeA.clear();
		nodeB.clear();
		for(int i=0;i<3;i++)
			nodeA.insert( (a.getNode(i))->getVector());
		for(int i=0;i<3;i++)
			nodeB.insert( (b.getNode(i))->getVector());
		assert(nodeA.size()==3);//otherwise it is not a legal triangle;
		assert(nodeB.size()==3);//otherwise it is not a legal triangle;
		std::set<vector>::iterator itA=nodeA.begin();
		std::set<vector>::iterator itB=nodeB.begin();
		
		for(int i=0;i<3;i++){
			if(!( (*itA)==(*itB)))
				return false;
			itA++;
			itB++;
		}
		//return true only if all the three nodes are equal to each other respectively
		return true;
	}
	
	bool operator <(const tri_face& a,const tri_face& b){
		if(a==b) return false;
		vector aa,bb;
		aa=a.getCenter();
		bb=b.getCenter();
		return aa<bb;
	}
	bool tri_sort::operator()(const tri_face& a,const tri_face& b)
	{
		return a<b;
	}
	bool tri_sort::operator()(const tri_face* a,const tri_face* b)
	{
		return (*a)<(*b);
	}
}
