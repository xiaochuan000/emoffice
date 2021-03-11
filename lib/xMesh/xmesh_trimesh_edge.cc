#include "xmesh_trimesh_edge.h"
#include "xmesh_vector.h"
#include "xmesh_base_node.h"
#include <xmesh_trimesh_node.h>

#include <xmesh_trimesh_face.h>
#include <xmesh_trimesh_sort.h>
namespace xMesh{
	tri_edge::tri_edge(){
		setnNode(2);
		InitNode();
		setNode(0,NULL);
		setNode(1,NULL);
		//this function should not be called, because the nodes of the edge is not initialized.
		cnt_[0]=cnt_[1]=localCnt_[0]=localCnt_[1]=-1;
		nTri_=0;
		tri_=NULL;
	}
        tri_edge& tri_edge::operator=(const tri_edge& right)  
        {
                base_edge::operator=(right);
                nTri_=right.nTri_;
                for(int i=0;i<nTri_;i++)
                        tri_[i]=right.tri_[i];
                return *this;
        }
	tri_edge::tri_edge(const tri_edge& right): base_edge(right){
		
		cnt_[0]=right.cnt_[0];
		cnt_[1]=right.cnt_[1];
		localCnt_[0]=right.localCnt_[0];
		localCnt_[1]=right.localCnt_[1];
		nTri_=right.nTri_;
                if(nTri_!=0)
                        tri_=new tri_face*[nTri_];
                else
                        tri_=NULL;
		for(int i=0;i<nTri_;i++)
			tri_[i]=right.tri_[i];
	}
	tri_edge::~tri_edge(){
		if(nTri_>0 && tri_!=NULL)
			delete[] tri_;
	}
	tri_edge::tri_edge(base_node* a,base_node* b){
		setnNode(2);
		InitNode();
		setNode(0,a);
		setNode(1,b);
		
		cnt_[0]=cnt_[1]=localCnt_[0]=localCnt_[1]=0;
		nTri_=0;
		tri_=NULL;
	}
	vector tri_edge::getVector()const{
		return getNode(1)->getVector()-getNode(0)->getVector();
	}
	Real tri_edge::distanceExt(const vector a)const
	{
		vector thisVec=getVector();
		vector aToThis=a-getNode(0)->getVector();
		Real Height=  (aToThis*thisVec).norm()/ thisVec.norm();
		
		return Height;
	}
	Real tri_edge::distance(const vector a)const
	{
		vector aToNode0=a-getNode(0)->getVector();
		vector aToNode1=a-getNode(1)->getVector();
		vector thisVec=getVector();
		Real dotA0This=dotP(aToNode0,thisVec);
		Real dotA1This=dotP(aToNode1,thisVec);
		
		Real flag= dotA0This *dotA1This;
		if(flag>=0.0)
		{
			if(dotA0This>=0.0 &&dotA1This>=0.0)
				return aToNode1.norm();
			else if (dotA0This<=0.0 &&dotA1This<=0.0)
				return aToNode0.norm();
		}
		return 	distanceExt(a);
	}
	void tri_edge::setNTri(int n)
	{
		if(n!=nTri_){
			if(nTri_!=0 && tri_!=NULL)
				delete[] tri_;
			nTri_=n;
			tri_=new tri_face* [nTri_];
			for(int i=0;i<nTri_;i++)
				tri_[i]=NULL;
		}
	}
	void tri_edge::setTri(int n,tri_face* f)
	{
		if(n<nTri_ &&n>=0)
                        tri_[n]=f;
                else{
                        tri_face** tmp=new tri_face*[n+1];
                        for(int i=0;i<nTri_;i++)
                                tmp[i]=tri_[i];
                        tmp[n]=f;
                        delete[] tri_;
                        tri_=tmp;
                        nTri_=n+1;
                }
	}
	tri_face* tri_edge::getTri(int n)const
	{
                if(n<nTri_ &&n>=0)
                        return tri_[n];
                else
                        return NULL;
	}
	tri_face* tri_edge::findOtherTriangle(const tri_face* input)const
	{
		if((*input)==*(tri_[0]))
			return tri_[1];
		if((*input)==*(tri_[1]))
			return tri_[0];
// 		assert(false);
		return NULL;
	}
	Real 	tri_edge::getDistance(const vector nn) const
	{
// 		Real distance;
		vector L[2];
		L[0]=nn- getNode(0)->getVector();
		L[1]=nn- getNode(1)->getVector();
		vector ll=getVector();
		Real flag= dotP(L[0],ll) * dotP(L[1],ll) ;
		if(flag<=0) //use height
		{
			Real sin0=(L[0] * getVector()).norm() /(L[0].norm() * getLength());
			return L[0].norm()* sin0;
		}
		else
		{
			Real l0=L[0].norm();
			Real l1=L[1].norm();
			return l0<l1?l0:l1;
		}
		
		return MAX_DOUBLEFLOAT;
	}
	void tri_edge::addTriangle( tri_face* input)
	{
		for(int i=0;i<nTri_;i++)
		{
			if(tri_[i]==NULL)
			{
				tri_[i]=input;
				return;
			}
			if(*(tri_[i])==*input)
			{
				return;
			}
		}
		std::cout<<"error!\n";
	}
	vector tri_edge::getMidPoint()const
	{
		vector result=(getNode(0)->getVector()+getNode(1)->getVector())*0.5;
		return result;
	}
	int tri_edge::getCnt(int i)const{
		return cnt_[i];
	}
	void tri_edge::setCnt(int i,int j){
		cnt_[i]=j;
	}
	int tri_edge::getNTri()const{
		return nTri_;
	}
	int tri_edge::bindTriangle( tri_face* tria, tri_face* trib)
	{
		int flag[2]={0,0};
		if(tria!=NULL){
			for(int i=0;i<3;i++){
				if(   (getNode(0)->getVector())== tria->getNode(i)->getVector() &&
					(getNode(1)->getVector())== tria->getNode((i+1)%3)->getVector()
				)
				{
					setTri(0,tria);
					flag[0]=-1;
					break;
				}
				else if(   (getNode(1)->getVector())== tria->getNode(i)->getVector() &&
								(getNode(0)->getVector())== tria->getNode((i+1)%3)->getVector()
					)
				{
					setTri(1,tria);
					flag[0]=1;
					break;
				}
			}
		}
		if(trib!=NULL){
			for(int i=0;i<3;i++){
				if(   (getNode(0)->getVector())== trib->getNode(i)->getVector() &&
							(getNode(1)->getVector())== trib->getNode((i+1)%3)->getVector()
				)
				{
					setTri(0,trib);
					flag[1]=-1;
					break;
				}
				else if(   (getNode(1)->getVector())== trib->getNode(i)->getVector() &&
								(getNode(0)->getVector())== trib->getNode((i+1)%3)->getVector()
				)
				{
					setTri(1,trib);
					flag[1]=1;
					break;
				}
			}
		}
		if(tria!=NULL && trib!=NULL){
			if(flag[0]*flag[1]>=0){
				std::cout<<"Warning: binding is problematic...\n";
				printEdge(this);
				printTri(tria);
				printTri(trib);
				return -1;
			}		
		}
		else if(tria!=NULL){
			if(flag[0]==0){
				std::cout<<"Warning: binding is problematic...\n";	
				printEdge(this);
				printTri(tria);
				return -2;
			}
		}
		else if(trib!=NULL){
			if(flag[1]==0){
				std::cout<<"Warning: binding is problematic...\n";	
				printEdge(this);
				printTri(trib);
				return -3;
			}
		}
		return 0;
	}
	void printEdge(tri_edge* iedgep)
	{
		std::cout<<"Print Edge:\n";
		std::cout<<"("<<iedgep->getNode(0)->getx() <<","<< iedgep->getNode(0)->gety()<<","<< iedgep->getNode(0)->getz()<<")"<<"\t\t"<<"("
				<< iedgep->getNode(1)->getx() <<","<< iedgep->getNode(1)->gety()<<","<< iedgep->getNode(1)->getz()<<")"<<"\n";
	}
}
