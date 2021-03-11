#include <xmesh_vector.h>
#include <xmesh_base_node.h>
#include <xmesh_base_edge.h>
#include <xmesh_constants.h>
#include <string.h>
#include <iostream>
namespace xMesh{
	base_edge::base_edge(){
		nNode_=0;
		nodePtr_=NULL;
		id_=NOT_NUMBERED;
	}
	base_edge::~base_edge(){
		if(nodePtr_!=NULL)
			delete[] nodePtr_;
	}
	base_edge::base_edge(const base_edge& right)
	{
		id_=right.id_;
		nNode_=right.nNode_;
//		if(nodePtr_!=NULL)
//			delete[] nodePtr_;
		nodePtr_=new base_node*[nNode_];
		for(int i=0;i<nNode_;i++)
			nodePtr_[i]=right.nodePtr_[i];
	}
	int base_edge::getNNode()const
	{
		return nNode_;
	}
	base_edge& base_edge::operator=(const base_edge& right)
	{
		id_=right.id_;
		if(nodePtr_!=NULL&&nodePtr_!=NULL&& nNode_!=right.nNode_)
			delete[] nodePtr_;
		if(nNode_!=right.nNode_){
			nNode_=right.nNode_;
			nodePtr_=new base_node*[nNode_];
		}
		for(int i=0;i<nNode_;i++)
			nodePtr_[i]=right.nodePtr_[i];
		return *this;
	}
		
	void base_edge::setnNode(const int n){
		nNode_=n;
	}
	void  base_edge::InitNode(){
		if(nodePtr_!=NULL && nNode_!=0)
		{
			delete[] nodePtr_;
		}
		nodePtr_=new base_node*[nNode_];
		for(int i=0;i<nNode_;i++)
			nodePtr_[i]=NULL;
		
	}
	void base_edge::setNode(const int i,  base_node* nd){
		nodePtr_[i]=nd;
	}
	void base_edge::setId(const int i){
		id_=i;
	}
			
	int base_edge::getId()const{
		return id_;
	}
	base_node* base_edge::getNode(int i)const{
		return nodePtr_[i];
	}	
	/////////////////////////////
	//auxiliary functions
	
	vector base_edge::getEdgeVector()const{
		return nodePtr_[nNode_-1]->getVector()-nodePtr_[0]->getVector();
	}
	Real base_edge::getLength()const{
		Real result=0.0;
		for(int i=0;i<nNode_-1;i++){
			result+= (nodePtr_[i]->getVector()-nodePtr_[i+1]->getVector()).norm();
		}
		return result;
	}
	vector base_edge::getMidPoint()const{
		return (nodePtr_[0]->getVector()+nodePtr_[1]->getVector())*0.5;
	}
	vector base_edge::getVector()const{
		std::cerr<<"Error base_edge::getVector() should never be called!\nIt must be implemented in the derived class\n";
		return vector(0.0,0.0,0.0);
	}
	Real  base_edge::getDistance(const vector nn) const{
		std::cerr<<"Error base_edge::getDistance() should never be called!\nIt must be implemented in the derived class\n";
		return 0.0;
	}
}
