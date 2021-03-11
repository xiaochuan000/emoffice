#include <xmesh_trimesh_face.h>
#include <xmesh_trimesh_node.h>
#include <xmesh_trimesh_edge.h>
#include <xmesh_trimesh_sort.h>
#include <xmesh_trimesh_mesh.h>
#include <xmesh_vector.h>
#include <set>
#include <map>
#include <fstream>
static unsigned int tick=0;
namespace xMesh{
	void updateMark(){
		tick++;
		switch(tick%4){
			case 0:
				std::cout<<"-\r"<<std::flush;
				break;
			case 1:
				std::cout<<"\\\r"<<std::flush;
				break;
			case 2:
				std::cout<<"|\r"<<std::flush;
				break;
			case 3:
				std::cout<<"/\r"<<std::flush;
				break;
		}
	}
				
	int tri_mesh::importFromTriFile(char* fname)
	{
		char buf[0x200];
		sprintf(buf,"%s.tri",fname);
		std::ifstream foo;
		foo.open(buf);
		
		if(!foo.is_open())
			return -1;
		Real unit;
		foo>>unit;
		unit_=unit;
		assert(fabs(unit)>0.0);
		foo>>nNode_;
		node_=new tri_node[nNode_];
		nodeToFace_=new ListFace[nNode_];
		if(verbose_)
			std::cout<<"Begin to import Nodes...\n";
		int step=nNode_/100+1;
		for(int i=0;i<nNode_;i++)
		{
			if( verbose_ && i%(step)==0)
				updateMark();
			Real x,y,z;
			foo>>x>>y>>z;
			x*=unit; 
			y*=unit;
			z*=unit;
			node_[i].setCoordinate(x,y,z);
			node_[i].setId(i);
			nodeToFace_[i].clear();
		}
		foo>>nTri_;
		tri_=new tri_face[nTri_];
		normal_=new TriNormalDirection [nTri_];
		for(int i=0;i<nTri_;i++)
			normal_[i]=RH;
		std::set<tri_edge> edgeMap;
		edgeMap.clear();
		int n[3];
		int cntEdge=0;
		int *tmpTri=new int[nTri_*3];
		if(verbose_)
			std::cout<<"Begin to import Triangles...\n";
		step=nTri_/100+1;
		for(int i=0;i<nTri_;i++)
		{
			if(verbose_ && i%(step)==0)
				updateMark();
			for(int j=0;j<3;j++){
				foo>>n[j];
			}
			for(int j=0;j<3;j++){
				//for i-th edge;
				int iNode0=(j+1)%3;
				int iNode1=(j+2)%3;
				tri_edge iEdge(&(node_[n[iNode0]]),&(node_[n[iNode1]]));
				std::set<tri_edge>::iterator itMap=edgeMap.find(iEdge);
				if(itMap==edgeMap.end()){
					iEdge.setId(cntEdge);
                                 	edgeMap.insert(iEdge);
					tmpTri[i*3+j]=cntEdge;
					cntEdge++;
				}
				else
				{
					tmpTri[i*3+j]=itMap->getId();
                                 
				}
			}
		}
		foo.close();
		nEdge_=cntEdge;
		edge_=new tri_edge[cntEdge];
		std::set<tri_edge>::iterator it=edgeMap.begin();
		if(verbose_)
			std::cout<<"Convert Edge tree....\n";
		for(;it!=edgeMap.end();it++){
                        int index=it->getId();
			edge_[index]=*it;
                        edge_[index].setNTri(2);
		}
                for(int i=0;i<cntEdge;i++){
                        assert(edge_[i].getId()>=0);
                }
		if(verbose_)
			std::cout<<"Convert Triangles....\n"<<std::flush;
		step= nTri_/100+1;
		for(int i=0;i<nTri_;i++){
			tri_[i].setEdge3( &(edge_[tmpTri[i*3]]),&(edge_[tmpTri[i*3+1]]),&(edge_[tmpTri[i*3+2]]));
			tri_[i].setId(i);
			if(verbose_ && i%(step)==0)
				updateMark();
			for(int j=0;j<3;j++){
				tri_node* nd=static_cast<tri_node*> (tri_[i].getNode(j));
				int ndIndex=nd->getId();
				bool insert=true;
				ListFace::iterator itFace=nodeToFace_[ndIndex].begin();
				for(;itFace!=nodeToFace_[ndIndex].end();itFace++){
					if( *(*itFace) == (tri_[i])){
						insert=false;
						break;
					}
				}
				if(insert)
					nodeToFace_[ndIndex].push_back( &(tri_[i]));
				xMesh::tri_edge* ed=tri_[i].getTriEdge(j);
				ed->addTriangle(&(tri_[i]));
			}
		}
		delete[] tmpTri;
		
		
		sprintf(buf,"%s.flg",fname);
		foo.open(buf);
		if(foo.is_open()){
			for(int i=0;i<nTri_;i++){
				int tmp;
				foo>>tmp;
				tri_[i].setFlag(tmp);
		
			}
			foo.close();
		}
		sprintf(buf,"%s.normal",fname);
		
		foo.open(buf);
		int nn=0;
		if(foo.is_open()){
			for(int i=0;i<nTri_;i++){
				int tmp;
				foo>>tmp;
				if(tmp==0){
					normal_[i]=LH;
					tri_[i].setNormal(false);
					nn++;
				}
			}
			foo.close();
		}
		std::cout<<"LH triangles:"<<nn<<std::endl;
		return 0;
	}
	int tri_mesh::importFromTriFileById(char* fname)
	{
		typedef std::set<tri_edge,tri_sort_byId> TRIEDGEMAP;
		char buf[0x200];
		sprintf(buf,"%s.tri",fname);
		std::ifstream foo;
		foo.open(buf);
		
		if(!foo.is_open())
			return -1;
		Real unit;
		foo>>unit;
		assert(fabs(unit)>0.0);
		foo>>nNode_;
		node_=new tri_node[nNode_];
		nodeToFace_=new ListFace[nNode_];
		for(int i=0;i<nNode_;i++)
		{
			Real x,y,z;
			foo>>x>>y>>z;
			x*=unit; 
			y*=unit;
			z*=unit;
			node_[i].setCoordinate(x,y,z);
			node_[i].setId(i);
			nodeToFace_[i].clear();
		}
		foo>>nTri_;
		tri_=new tri_face[nTri_];
		normal_=new TriNormalDirection [nTri_];
		for(int i=0;i<nTri_;i++)
			normal_[i]=RH;
		TRIEDGEMAP edgeMap;
		edgeMap.clear();
		int n[3];
		int cntEdge=0;
		int *tmpTri=new int[nTri_*3];
		for(int i=0;i<nTri_;i++)
		{
			for(int j=0;j<3;j++){
				foo>>n[j];
			}
			for(int j=0;j<3;j++){
				//for i-th edge;
				int iNode0=(j+1)%3;
				int iNode1=(j+2)%3;
				tri_edge iEdge(&(node_[n[iNode0]]),&(node_[n[iNode1]]));
				TRIEDGEMAP::iterator itMap=edgeMap.find(iEdge);
				if(itMap==edgeMap.end()){
					iEdge.setId(cntEdge);
                                 	edgeMap.insert(iEdge);
					tmpTri[i*3+j]=cntEdge;
					cntEdge++;
				}
				else
				{
					tmpTri[i*3+j]=itMap->getId();
                                 
				}
			}
		}
		foo.close();
		nEdge_=cntEdge;
		edge_=new tri_edge[cntEdge];
		TRIEDGEMAP::iterator it=edgeMap.begin();
		for(;it!=edgeMap.end();it++){
                        int index=it->getId();
			edge_[index]=*it;
                        edge_[index].setNTri(2);
		}
                for(int i=0;i<cntEdge;i++){
                        assert(edge_[i].getId()>=0);
                }
		for(int i=0;i<nTri_;i++){
			tri_[i].setEdge3( &(edge_[tmpTri[i*3]]),&(edge_[tmpTri[i*3+1]]),&(edge_[tmpTri[i*3+2]]));
			tri_[i].setId(i);
			for(int j=0;j<3;j++){
				tri_node* nd=static_cast<tri_node*> (tri_[i].getNode(j));
				int ndIndex=nd->getId();
				bool insert=true;
				ListFace::iterator itFace=nodeToFace_[ndIndex].begin();
				for(;itFace!=nodeToFace_[ndIndex].end();itFace++){
					if( *(*itFace) == (tri_[i])){
						insert=false;
						break;
					}
				}
				if(insert)
					nodeToFace_[ndIndex].push_back( &(tri_[i]));
				xMesh::tri_edge* ed=tri_[i].getTriEdge(j);
				ed->addTriangle(&(tri_[i]));
			}
		}
		delete[] tmpTri;
		
		
		sprintf(buf,"%s.flg",fname);
		foo.open(buf);
		if(foo.is_open()){
			for(int i=0;i<nTri_;i++){
				int tmp;
				foo>>tmp;
				tri_[i].setFlag(tmp);
		
			}
			foo.close();
		}
		sprintf(buf,"%s.normal",fname);
		int nn=0;
		foo.open(buf);
		if(foo.is_open()){
			for(int i=0;i<nTri_;i++){
				int tmp;
				foo>>tmp;
				if(tmp==0){
					normal_[i]=LH;nn++;
					tri_[i].setNormal(false);
				}
			}
			foo.close();
		}
		std::cout<<"Number of LH Triangles: "<<nn<<std::endl;
		return 0;

	}
	void tri_mesh::exportToTriFile(char* fname,int precision)const
	{
		std::ofstream fout;
		char buf[0x200];
		if(fname==NULL)
			sprintf(buf,"%s.tri",name_.c_str());
		else
			sprintf(buf,"%s.tri",fname);
		fout.open(buf);
		fout.precision(precision);
		fout<<1.0<<"\t"<<nNode_<<"\n";
		for(int i=0;i<nNode_;i++)
			fout<<std::scientific<<node_[i].getx()<<"\t"<<node_[i].gety()<<"\t"
					<<node_[i].getz()<<"\n";
		fout<<nTri_<<"\n";
		for(int i=0;i<nTri_;i++){
			for (int j=0;j<3;j++){
				fout<<tri_[i].getNode(j)->getId()<<"\t";
			}	
			fout<<"\n";
		}
		fout.close();
		
		
		if(fname==NULL)
			sprintf(buf,"%s.flg",name_.c_str());
		else
			sprintf(buf,"%s.flg",fname);
		fout.open(buf);
		for(int i=0;i<nTri_;i++){
			fout<<tri_[i].getFlag()<<std::endl;
		}
		fout.close();
		
		if(fname==NULL)
			sprintf(buf,"%s.normal",name_.c_str());
		else
			sprintf(buf,"%s.normal",fname);
		fout.open(buf);
		for(int i=0;i<nTri_;i++){
			if(normal_[i]!=LH)
				fout<<1<<std::endl;
			else
				fout<<-1<<std::endl;
			
		}
		fout.close();
		
	}
// 	void tri_mesh::importFromFEMABCFile(char* fname)
// 	{
// 		char buf[0x200];
// 		std::ifstream foo,foo_flag;
// 		sprintf(buf,"%s.domain",fname);
// 		foo.open(buf);
// 		if(foo.is_open()==false)
// 		{
// 			std::cerr<<"Error! "<<buf<<" cannot be opened!\n";
// 			exit(-1);
// 		}
// 		foo>>nDomain;
// 		foo.close();
// 		domainIndex.resize(nDomain);
// 		//Get the total number of node,edge and triangles;
// 		EM_Mesh::base_node** nodePtr=new EM_Mesh::base_node*[nDomain];
// 		int *numNode=new int[nDomain];
// 		std::vector<int>* triPtr=new std::vector<int>[nDomain];
// 		std::vector<int>* triFlagId=new std::vector<int>[nDomain];
// 		
// 		std::set<base_node,node_CoordComp> nodeTreeTemp;
// 		std::set<tri_edge,edge_CoordComp> edgeTreeTemp;
// 		int cnt=0;
// 		for(int i=0;i<nDomain;i++)
// 		{
// 			sprintf(buf,"%s_domain%dBI.tri",fname,i);
// 			foo.open(buf);
// 			sprintf(buf,"%s_domain%dBI.flg",fname,i);
// 			foo_flag.open(buf);
// 			bool flag=true;
// 			if(foo_flag.is_open()==false)
// 				flag=false;
// 			Real iunit; int inNode,inTri;
// 			foo>>iunit>>inNode;
// 			numNode[i]=inNode;
// 			nodePtr[i]=new EM_Mesh::base_node[inNode];
// 			for(int j=0;j<inNode;j++)
// 			{
// 				Real x,y,z;
// 				foo>>x>>y>>z;
// 				x=x*iunit;y=y*iunit;z=z*iunit;
// 				nodePtr[i][j].setCoord(x,y,z);
// 				nodeTreeTemp.insert(nodePtr[i][j]);
// 			}
// 			foo>>inTri;
// 			triPtr[i].resize(inTri*3);
// 			triFlagId[i].resize(inTri);
// 			for(int j=0;j<inTri;j++)
// 			{
// 				if(flag)
// 					foo_flag>>triFlagId[i][j];
// 				else
// 					triFlagId[i][j]=DEFAULT_ID;
// 				int in[3];
// // 				foo>>triPtr[i][j*3]>>triPtr[i][j*3+1]>>triPtr[i][j*3+2];
// 				foo>>in[0]>>in[1]>>in[2];
// 				triPtr[i][j*3]=in[0];
// 				triPtr[i][j*3+1]=in[1];
// 				triPtr[i][j*3+2]=in[2];
// 				
// 				for(int k=0;k<3;k++)
// 				{
// 					base_node* n1=&(nodePtr[i][in[(k+1)%3]]);
// 					base_node* n2=&(nodePtr[i][in[(k+2)%3]]);
// 					assert(n1!=NULL&&n2!=NULL);
// 					tri_edge iedge(n1,n2);
// 					edgeTreeTemp.insert(iedge);
// 				}				
// 			}
// 			foo.close();
// 			if(flag)
// 				foo_flag.close();
// 			domainIndex[i]=cnt;
// 			cnt+=inTri;
// 		}
// 		nFace=cnt;
// 		nNode=nodeTreeTemp.size();
// 		nEdge=edgeTreeTemp.size();
// 		nodeTreeTemp.clear();
// 		edgeTreeTemp.clear();
// 		
// 		
// 		node=new base_node [nNode];
// 		edge=new tri_edge[nEdge];
// 		face=new tri_face[nFace];
// 		nodeToFace=new std::list<tri_face*> [nNode];
// 		int icntFace=0,icntNode=0,icntEdge=0;
// 		for(int i=0;i<nDomain;i++)
// 		{
// 			for(int j=0;j<numNode[i];j++)
// 			{
// 				std::set<base_node*,node_CoordComp>::iterator it=nodeTreeCoord.find(&(nodePtr[i][j]));
// 				if(it==nodeTreeCoord.end())
// 				{
// 					node[icntNode]= nodePtr[i][j];
// 					node[icntNode].setId(icntNode);
// 					nodeTreeCoord.insert(&(node[icntNode]));
// 					icntNode++;
// 				}
// 			}
// 			for(unsigned int j=0;j<(triPtr[i].size())/3;j++)
// 			{
// 				tri_edge* ie[3];
// 				for(int k=0;k<3;k++)
// 				{
// 					tri_edge iedge(&(nodePtr[i][triPtr[i][j*3+(k+1)%3]]),&(nodePtr[i][triPtr[i][j*3+(k+2)%3]]));
// 					std::set<tri_edge*,edge_CoordComp>::iterator it=edgeTreeCoord.find(&iedge); //WXC: bug, this is to comply with different convention.
// 					if(it==edgeTreeCoord.end())
// 					{
// // 						edge[icntEdge]=**it;
// 						edge[icntEdge]=tri_edge(icntEdge,*(nodeTreeCoord.find( &(nodePtr[i][triPtr[i][j*3+(k+1)%3]]))),*(nodeTreeCoord.find( &(nodePtr[i][triPtr[i][j*3+(k+2)%3]]))));
// // 						edge[icntEdge].setId(icntEdge);
// 						edgeTreeCoord.insert(&edge[icntEdge]);
// 						ie[k]=&edge[icntEdge];
// 						icntEdge++;
// 					}
// 					else
// 					{
// 						ie[k]= *it;
// 					}
// 					face[icntFace].setEdge(k,ie[k]);
// 				}
// 				face[icntFace].checkEdge();
// 				face[icntFace].setId(icntFace);
// 				face[icntFace].setBC(triFlagId[i][j]);
// 				for(int j=0;j<3;j++)
// 				{
// 					int idNode=face[icntFace].getNode(j)->getId();
// 					nodeToFace[idNode].push_back(&(face[icntFace]));
// 				}
// 				icntFace++;
// 			}
// 		}
// 		
// 		for(int n=0;n<nDomain;n++)
// 		{
// 			delete[] nodePtr[n];
// 			
// 		}
// 		delete[] nodePtr;
// // 		delete[]nodePtr;
// 		delete[] triPtr;
// 		delete[] triFlagId;
// 	}
	void tri_mesh::ImportByTri(const int _nFace,const tri_face** face_external)
	{
		freeMemory();
		nTri_=_nFace;
		std::map<tri_node,int,tri_sort> nodeTreeTemp;
		int cntNode=0;
		int *nTriTemp=new int[_nFace*3];
		for(int i=0;i<_nFace;i++)
		{
			for(int j=0;j<3;j++)
			{
				tri_node inode= * ((face_external[i]->getNode(j)));
				std::map<tri_node,int,tri_sort>::iterator it=nodeTreeTemp.find(inode);
				if(it==nodeTreeTemp.end())
				{
// 					inode.setId(cntNode);
					nodeTreeTemp.insert(std::pair<tri_node,int>(inode,cntNode));
					nTriTemp[i*3+j]=cntNode;
					cntNode++;
				}
				else
				{
					nTriTemp[i*3+j]=it->second;
				}
			}
		}
		nNode_=nodeTreeTemp.size();
		node_=new tri_node[nNode_];
		for(std::map<tri_node,int,tri_sort>::iterator it=nodeTreeTemp.begin();
				  it!=nodeTreeTemp.end();it++)
		{
			node_[it->second]=it->first;
			node_[it->second].setId(it->second);
		}
		for(int i=0;i<nNode_;i++)
		{
			treeNodePtr_.insert(&(node_[i]));
		}
		
		
		
		//Create the edge tree
		std::set<tri_edge,tri_sort> edgeTreeTemp;
		for(int i=0;i<nTri_;i++)
		{
			for(int j=0;j<3;j++)
			{
				tri_edge iedge(&(node_[nTriTemp[j+i*3]]),&(node_[nTriTemp[(j+1)%3+i*3]]));
				edgeTreeTemp.insert(iedge);
			}
		}
		nEdge_=edgeTreeTemp.size();
		edgeTreeTemp.clear();
		
		
		tri_=new tri_face[nTri_];
		treeEdgePtr_.clear();
		int cntEdge=0;
		for(int i=0;i<nTri_;i++)
		{
			tri_edge iEdge[3];
			for(int j=0;j<3;j++)
			{
				
				iEdge[j]= tri_edge(&(node_[nTriTemp[(j+1)%3+i*3]]),&(node_[nTriTemp[(j+2)%3+i*3]]));
				std::set<tri_edge*,tri_sort>::iterator itSet= treeEdgePtr_.find(&iEdge[j]);
				if( itSet== treeEdgePtr_.end())
				{
					edge_[cntEdge]=iEdge[j];	
					edge_[cntEdge].setId(cntEdge);
					
					treeEdgePtr_.insert(&(edge_[cntEdge]));
					edge_[cntEdge].addTriangle(&(tri_[i]));
					tri_[i].setEdge(j,&(edge_[cntEdge]));
					cntEdge++;
				}
				else
				{
					(*itSet)->addTriangle(&(tri_[i]));
					tri_[i].setEdge(j,*itSet);
				}
			}
// 			tri_[i].setBC(face_external[i]->getBC());
			tri_[i].checkEdge();
		}
		delete nTriTemp;	
	}
}
