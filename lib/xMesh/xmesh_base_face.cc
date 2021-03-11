#include <xmesh_base_node.h>
#include <xmesh_base_edge.h>

#include <xmesh_base_face.h>
#include <xmesh_constants.h>
#include <string.h>

namespace xMesh{
	base_face::base_face(){
		id_=NOT_NUMBERED;
		nEdge_=0;
		edgePtr_=NULL;
	}
	base_face::base_face(const base_face& right){
		id_=right.id_;
		nEdge_=right.nEdge_;
		edgePtr_=new base_edge*[nEdge_];
		memcpy(edgePtr_,right.edgePtr_,sizeof(base_edge*)*nEdge_);
	}
	base_face::base_face(const int n, base_edge** ed){
		id_=NOT_NUMBERED;
		if(n!=0 && ed!=NULL){
			nEdge_=n;
			edgePtr_=new base_edge*[nEdge_];
			memcpy(edgePtr_,ed,sizeof(base_edge*)*nEdge_);
		}
		else
		{
			nEdge_=0;
			edgePtr_=NULL;
		}
	}
	base_face::~base_face()
	{
		if(edgePtr_!=NULL)
			delete[] edgePtr_;
		
	}
	void base_face::setId(int i){
		id_=i;
	}
	int base_face::getId()const{
		return id_;
	}
	void base_face::setnEdge(int i){
		nEdge_=i;
	}
	int base_face::getnEdge()const{
		return nEdge_;
	}
	void base_face::InitEdge(){
		if(edgePtr_!=NULL)
			delete[] edgePtr_;
		edgePtr_=NULL;
		if(nEdge_!=0)
			edgePtr_=new base_edge*[nEdge_];
	}
	void base_face::setEdge(int i,base_edge* ed){
		assert(i>=0 &&i<nEdge_);
		edgePtr_[i]=ed;
	}
	base_edge* base_face::getEdge(int i)const{
		return edgePtr_[i];
	}
	void base_face::print()const
	{
		std::cout<<"base_face:: Print():\n";
	} 	
	
}
