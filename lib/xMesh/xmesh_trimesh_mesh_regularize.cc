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
#include <queue>
namespace xMesh{
	typedef std::set<xMesh::tri_face*,xMesh::tri_sort> FaceQueue;
	bool tri_mesh::regularize()
	{
		std::cout<<"Warning: bool tri_mesh::regularize() has not been tested!\n";
		if(nNode_==0 ||nEdge_==0||nTri_==0)
			return false; //false means failed.
		//take the first triangle as the basis 
		short* edgeFlag=new short[nEdge_];
		for(int i=0;i<nEdge_;i++)
			edgeFlag[i]=0;
		
		
		for(int i=0;i<nTri_;i++)
			normal_[i]=NA;
		
		
		FaceQueue currentQueue;
		FaceQueue nextQueue;
		currentQueue.clear();
		nextQueue.clear();
		currentQueue.insert(&(tri_[0]));
		normal_[0]=RH;
		while(currentQueue.size()>0){
			FaceQueue::iterator itCurQ=currentQueue.begin();
			nextQueue.clear();
			for(;itCurQ!=currentQueue.end();itCurQ++){
				tri_face* thisTri=(*itCurQ);
				if(normal_[thisTri->getId()]==RH){
					
					for(int i=0;i<3;i++){
						tri_edge* ied=static_cast<tri_edge*> (thisTri->getEdge(i));
						int index=ied->getId();
	// 					short iflag=edgeFlag[index];
						if(edgeFlag[index]==0){ //Unmarked edge
							if(thisTri->getOrder(i)==true){
								edgeFlag[index]=1;
								tri_face* other=ied->findOtherTriangle(thisTri);
								nextQueue.insert(other);
								int indexOther=other->findEdgeIndex(ied);
								assert(indexOther>=0);
								
								if(other->getOrder(indexOther)==true)
									normal_[other->getId()]=LH;
								else
									normal_[other->getId()]=RH;
								nextQueue.insert(other);
							}
							else{
								edgeFlag[index]=-1;
								tri_face* other=ied->findOtherTriangle(thisTri);
								nextQueue.insert(other);
								int indexOther=other->findEdgeIndex(ied);
								assert(indexOther>=0);
								
								if(other->getOrder(indexOther)==true)
									normal_[other->getId()]=RH;
								else
									normal_[other->getId()]=LH;
								nextQueue.insert(other);
							}
						}
						
					}
					
				}
				else{
					for(int i=0;i<3;i++){
						tri_edge* ied=static_cast<tri_edge*> (thisTri->getEdge(i));
						int index=ied->getId();
	// 					short iflag=edgeFlag[index];
						if(edgeFlag[index]==0){ //Unmarked edge
							if(thisTri->getOrder(i)==true){
								edgeFlag[index]=-1;
								tri_face* other=ied->findOtherTriangle(thisTri);
								nextQueue.insert(other);
								int indexOther=other->findEdgeIndex(ied);
								assert(indexOther>=0);
								
								if(other->getOrder(indexOther)==true)
									normal_[other->getId()]=RH;
								else
									normal_[other->getId()]=LH;
								nextQueue.insert(other);
							}
							else{
								edgeFlag[index]=1;
								tri_face* other=ied->findOtherTriangle(thisTri);
								nextQueue.insert(other);
								int indexOther=other->findEdgeIndex(ied);
								assert(indexOther>=0);
								
								if(other->getOrder(indexOther)==true)
									normal_[other->getId()]=LH;
								else
									normal_[other->getId()]=RH;
								nextQueue.insert(other);
							}
						}
						
					}
				}
			}
			currentQueue=nextQueue;
		}
	
	//create the flag
	 return false;	
	}
}
