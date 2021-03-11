
#include <xmesh_trimesh_face.h>
#include <xmesh_trimesh_node.h>
#include <xmesh_trimesh_edge.h>
#include <xmesh_trimesh_sort.h>
#include <xmesh_trimesh_mesh.h>
#include <xmesh_vector.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <set>
#include <map>
#include <vector>
namespace xMesh{
	
	tri_mesh::tri_mesh()
	{
		nTri_=0;
		nEdge_=0;
		nNode_=0;
		tri_=NULL;
		node_=NULL;
		edge_=NULL;
		normal_=NULL;
		nodeToFace_=NULL;
		verbose_=false;
	}
	tri_mesh::~tri_mesh()
	{
		freeMemory();
	}
	void tri_mesh::setName(const char* fname)
	{
		name_=fname;
	}
	void tri_mesh::setName(const std::string& fname)
	{
		name_=fname;
	}
	void tri_mesh::freeMemory()
	{
		if(tri_!=NULL){
			delete[] tri_;
			tri_=NULL;
		}
		if(node_!=NULL){
			delete[] node_;
			node_=NULL;
		}
		if(edge_!=NULL){
			delete[] edge_;
			edge_=NULL;
		}
		if(normal_!=NULL){
			delete[] normal_;
			normal_=NULL;
		}
		if(nodeToFace_!=NULL)
		{
			delete[]nodeToFace_;
			nodeToFace_=NULL;
		}
	}
	
	tri_node* tri_mesh::getNodePtr(int i)const
	{
		return &(node_[i]);
	}
	tri_face* tri_mesh::getTriPtr(int i)const
	{
		return &(tri_[i]);
	}
	tri_edge* tri_mesh::getEdgePtr(int i)const
	{
		return &(edge_[i]);
	}
	tri_node* tri_mesh::findNode( tri_node* input)
	{
		std::set<tri_node*,tri_sort>::iterator it=treeNodePtr_.find(input);
		if(it==treeNodePtr_.end())
			return NULL;
		else 
			return *it;
	}	
	tri_face* tri_mesh::findTri(  tri_face* input)
	{
		std::set<tri_face*,tri_sort>::iterator it=treeFacePtr_.find(input);
		if(it==treeFacePtr_.end())
			return NULL;
		else 
			return *it;
	}	
	tri_edge* tri_mesh::findEdge(  tri_edge* input)
	{
		std::set<tri_edge*,tri_sort>::iterator it=treeEdgePtr_.find(input);
		if(it==treeEdgePtr_.end())
			return NULL;
		else 
			return *it;
	}		
	const tri_face* tri_mesh::findMatchedFace(const tri_face* input)const
	{
		vector ctr;
		ctr=(input->getNode(0)->getVector()+input->getNode(1)->getVector()+input->getNode(2)->getVector()) /3.0;
		const tri_face* result=findMatchedFace(ctr);
		
#ifdef VERBOSE_CHECK
		bool check[3]={false,false,false};
		bool check2[3]={false,false,false};
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(check2[j])
					continue;
				if( *(result->getNode(j))==*(input->getNode(i)))
				{
					check[i]=true;
					check2[j]=true;
					break;
				}
			}
		}
		for(int i=0;i<3;i++)
		{
			assert(check[i]);
			assert(check2[i]);
		}
			
#endif
		return result;
		
	}
	
	const tri_face* tri_mesh::findMatchedFaceByNode(const vector inputNode,const tri_face* seed) const
	{
		//The goal of this function is the same as findMatchedFace, except for the way I am using to find the neighbouring triangles. In this case, I am using the node as a way to find the neighbouring triangels.
		bool forDebug=false;
		Real TOL_FINDMATCH=0.1;
		
		const tri_face* thisTri;
		if(seed==NULL)
			thisTri=&(tri_[0]);
		else
			thisTri=seed;
		const tri_face* backTraceTriangle=NULL;
		bool found=false;
		do
		{
			if(forDebug)
				thisTri->print();
			found=thisTri->isInside(inputNode);
			if(found==false)
			{
				Real minDistance=MAX_DOUBLEFLOAT;
				const tri_face* triMin=NULL;
				
				std::list<const tri_face*> neighbourTriangles = getNeighbourTriangles(thisTri);
				neighbourTriangles.push_back(thisTri); //Also count this triangle
				assert(neighbourTriangles.size()>1);
				std::list<const tri_face*>::iterator it=neighbourTriangles.begin();
				std::map<Real,const tri_face*> neighbourMap;
				neighbourMap.clear();
				for(;it!=neighbourTriangles.end();it++)
				{
					Real dist= (*it)->distanceEdge(inputNode);
					neighbourMap.insert(std::pair<Real,const tri_face*>(dist,*it));
				}

				triMin=neighbourMap.begin()->second;
				minDistance=neighbourMap.begin()->first;
				if(triMin==thisTri && minDistance>0.0 && minDistance< TOL_FINDMATCH* triMin->getOuterRadius()) //
					return thisTri;
				assert(triMin!=backTraceTriangle);
				backTraceTriangle=thisTri;
				assert(triMin!=NULL);
				thisTri=triMin;
			}
		}while( found==false);
		return thisTri;

	}
	const tri_face* tri_mesh::findMatchedFace(const vector inputNode,const tri_face* seed) const
	{
		bool forDebug=false;

		const tri_face* thisTri;
		if(seed==NULL)
			thisTri=&(tri_[0]);
		else
			thisTri=seed;
		
		const tri_face* backTraceTriangle=NULL;
		bool found=false;
		do
		{
			if(forDebug)
				thisTri->print();
			found=thisTri->isInside(inputNode);
			if(found==false)
			{
				Real minDistance=MAX_DOUBLEFLOAT;
				const tri_face* triMin=NULL;
				for(int i=0;i<3;i++)
				{
					
					const tri_face* nextTri=(static_cast<tri_edge*>(thisTri->getEdge(i)))->findOtherTriangle(thisTri);
					if (nextTri==NULL)
						continue;

					if(forDebug)
						nextTri->print();
					if(nextTri->isInside(inputNode))
					{
						triMin=nextTri;
						break;
					}
					
					Real distance= nextTri->distanceEdge(inputNode);
// 					Real distance= nextTri->distanceCenter(inputNode);
					if(distance<minDistance&&nextTri!=backTraceTriangle)
					{
						minDistance=distance;
						triMin=nextTri;
					}
				}
				backTraceTriangle=thisTri;
				assert(triMin!=NULL);
				thisTri=triMin;
			}
		}while( found==false);
		return thisTri;
	}
	
	std::list<const tri_face*> tri_mesh::getNeighbourTriangles(const tri_face* fc)const{
		std::list<const tri_face*> result;
		result.clear();
		for(int j=0;j<3;j++){
			int iNodeId=fc->getNode(j)->getId();
			std::list<tri_face*>::iterator it=nodeToFace_[iNodeId].begin();
			for(;it!=nodeToFace_[iNodeId].end();it++){
				if(*it !=fc){
					result.push_back(*it);
				}
			}
		}
		return result;
	}	
	
	void tri_mesh::buildNodeTree()
	{
		treeNodePtr_.clear();
		for(int i=0;i<nNode_;i++){
			treeNodePtr_.insert(&(node_[i]));
		}
	}
	
	void tri_mesh::buildEdgeTree()
	{
		treeEdgePtr_.clear();
		for(int i=0;i<nEdge_;i++){
			treeEdgePtr_.insert(&(edge_[i]));
		}
	}
	void tri_mesh::buildFaceTree()
	{
		treeFacePtr_.clear();
		for(int i=0;i<nEdge_;i++){
			treeFacePtr_.insert(&(tri_[i]));
		}
	}
	int 	tri_mesh::getnNode()const{return nNode_;}
	int 	tri_mesh::getnEdge()const{return nEdge_;}
	int 	tri_mesh::getnTri()const{return nTri_;}
	
	void tri_mesh::setTriPtr(tri_face* input)
	{
		tri_=input;
	}
	void tri_mesh::setNodePtr(tri_node* input)
	{
		node_=input;
	}
	void tri_mesh::setEdgePtr(tri_edge* input)
	{
		edge_=input;
	}	
	void tri_mesh::reinitialize(int nNode,int nEdge,int nTri)
	{
		freeMemory();
		nNode_=nNode;
		nEdge_=nEdge;
		nTri_=nTri;
		node_=new tri_node[nNode_];
		edge_=new tri_edge[nEdge_];
		tri_=new tri_face[nTri_];
		
	}
	tri_face& tri_mesh::getTri(int i)
	{
		assert(i>=0 && i<nTri_);
		return tri_[i];
	}
	tri_edge& tri_mesh::getEdge(int i)		
	{
		assert(i>=0 && i<nEdge_);
		return edge_[i];
	}
	tri_node& tri_mesh::getNode(int i)
	{
		assert(i>=0 && i<nNode_);
		return node_[i];
	}
	void tri_mesh::printSummary(std::ostream& out)
	{
		out<<"*****************Summary of Triangle Mesh ************************\n";
		out<<"Number of Node:\t"<<nNode_<<"\n";
		out<<"Number of Edge:\t"<<nEdge_<<"\n";
		out<<"Number of Tri:\t"<<nTri_<<"\n";
		
	}
	TriNormalDirection tri_mesh::getNormal(int i)const
	{
		return normal_[i];
	}
	const tri_face* tri_mesh::findMatchedFaceBruteForce(const vector inputNode) const
	{
		for(int i=0;i<nTri_;i++){
			tri_face* thisface= &(tri_[i]);
			bool test=thisface->isInside(inputNode);
			if(test){
				return thisface;
			}
		}
		return NULL;
	}
	void tri_mesh::setVerbose(bool r)
	{
		verbose_=r;
		if(r)
			std::cout<<"Verbose mode is set!\n";
		else
			std::cout<<"Verbose mode is disabled!\n";
	}
	Real tri_mesh::getUnit()const
	{
		return unit_;
	}
	std::vector<int> tri_mesh::getFlagVector()const
	{
	  std::set<int> res;
	  res.clear();
	  std::vector<int> result;
	  result.clear();
	  for(int i=0;i<nTri_;i++){
	    res.insert(tri_[i].getFlag());
	  }
	  result.resize(res.size());
	  std::set<int>::iterator ii=res.begin();
	  int cnt=0;
	  for(;ii!=res.end();ii++)
	  {
	    result[cnt]= (*ii);
	    cnt++;
	  }
	  return result;
	}
	
}
