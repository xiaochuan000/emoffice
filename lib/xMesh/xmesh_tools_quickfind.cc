#include "xmesh_tools_quickfind.h"
#include <float.h>
#include "xmesh_trimesh_node.h"
#include <string.h>
#include <list>
#include <map>
//#define STRICK_CHECK
namespace xMesh{
	typedef std::list<tri_face*> FCLIST;
	Box::Box()
	{
		for(int i=0;i<6;i++)
		{
			if(i%2==0)
				lim_[i]=MAX_DOUBLEFLOAT;
			else
				lim_[i]=-MAX_DOUBLEFLOAT;
		}
	}
	Box::Box(const Real xmin,const Real xmax,
			 const Real ymin,const Real ymax,
	         const Real zmin,const Real zmax)
	{
		lim_[0]=xmin;
		lim_[1]=xmax;
		lim_[2]=ymin;
		lim_[3]=ymax;
		lim_[4]=zmin;
		lim_[5]=zmax;
	}
	Real Box::getMidPoint(const int n)const
	{
		if(n>=0 && n<3)
			return (lim_[2*n] + lim_[2*n+1]) /2.0;
		return 0.0;
	}
	void Box::setLimit(const int n,const Real ii)
	{
		if(n>=0 && n<6)
			lim_[n]=ii;
	}
	void Box::setLimit(const Real xmin,const Real xmax,
					   const Real ymin,const Real ymax,
						const Real zmin,const Real zmax)
	{
		lim_[0]=xmin;
		lim_[1]=xmax;
		lim_[2]=ymin;
		lim_[3]=ymax;
		lim_[4]=zmin;
		lim_[5]=zmax;
	}
	Real Box::getLimit(int i)const
	{
		if(i<0 ||i>=6) return 0.0;	
		return lim_[i%6];
	}
	bool Box::checkInbox(const vector v)const
	{
		Real x,y,z;
		x= v.getx();
		y= v.gety();
		z= v.getz();
		if(  x>= (lim_[0]- TOLERANCE) &&  x<= (lim_[1]+ TOLERANCE) && 
			 y>= (lim_[2]- TOLERANCE) &&  y<= (lim_[3]+ TOLERANCE) && 
			 z>= (lim_[4]- TOLERANCE) &&  z<= (lim_[5]+ TOLERANCE))
		{
			return true;
		}
		else
			return false;
				   
	}
	bool Box::checkIntersect(const Box right)const
	{
		vector v[8];
		v[0].setvtr(right.lim_[0],right.lim_[2],right.lim_[4]);
		v[1].setvtr(right.lim_[0],right.lim_[2],right.lim_[5]);
		v[2].setvtr(right.lim_[0],right.lim_[3],right.lim_[4]);
		v[3].setvtr(right.lim_[0],right.lim_[3],right.lim_[5]);
		v[4].setvtr(right.lim_[1],right.lim_[2],right.lim_[4]);
		v[5].setvtr(right.lim_[1],right.lim_[2],right.lim_[5]);
		v[6].setvtr(right.lim_[1],right.lim_[3],right.lim_[4]);
		v[7].setvtr(right.lim_[1],right.lim_[3],right.lim_[5]);
		for(int i=0;i<8;i++)
		{
			if(checkInbox(v[i]))
				return true;
		}
		
		v[0].setvtr(lim_[0],lim_[2],lim_[4]);
		v[1].setvtr(lim_[0],lim_[2],lim_[5]);
		v[2].setvtr(lim_[0],lim_[3],lim_[4]);
		v[3].setvtr(lim_[0],lim_[3],lim_[5]);
		v[4].setvtr(lim_[1],lim_[2],lim_[4]);
		v[5].setvtr(lim_[1],lim_[2],lim_[5]);
		v[6].setvtr(lim_[1],lim_[3],lim_[4]);
		v[7].setvtr(lim_[1],lim_[3],lim_[5]);
		for(int i=0;i<8;i++)
		{
			if(right.checkInbox(v[i]))
				return true;
		}
		return false;
	}
	
	bool Box::checkIntersect(const tri_face* fc)const
	{
		Box ibox;
		for(int i=0;i<3;i++){
			ibox.lim_[0]= fc->getNode(i)->getx()<ibox.lim_[0] ?  fc->getNode(i)->getx(): ibox.lim_[0];
			ibox.lim_[1]= fc->getNode(i)->getx()>ibox.lim_[1] ?  fc->getNode(i)->getx(): ibox.lim_[1];
			ibox.lim_[2]= fc->getNode(i)->gety()<ibox.lim_[2] ?  fc->getNode(i)->gety(): ibox.lim_[2];
			ibox.lim_[3]= fc->getNode(i)->gety()>ibox.lim_[3] ?  fc->getNode(i)->gety(): ibox.lim_[3];
			ibox.lim_[4]= fc->getNode(i)->getz()<ibox.lim_[4] ?  fc->getNode(i)->getz(): ibox.lim_[4];
			ibox.lim_[5]= fc->getNode(i)->getz()>ibox.lim_[5] ?  fc->getNode(i)->getz(): ibox.lim_[5];
		}
		bool res=checkIntersect(ibox);
		return res;
	}
	void Box::setBoxLim(const int n,tri_face** fcArray)
	{
		if(n<=0) return;
		//First reset the limit
		lim_[0]=fcArray[0]->getNode(0)->getx();
		lim_[1]=fcArray[0]->getNode(0)->getx();
		lim_[2]=fcArray[0]->getNode(0)->gety();
		lim_[3]=fcArray[0]->getNode(0)->gety();
		lim_[4]=fcArray[0]->getNode(0)->getz();
		lim_[5]=fcArray[0]->getNode(0)->getz();
		Real tmpLim[3];
		for(int i=0;i<n;i++) //for each triangle
		{
			for(int j=0;j<3;j++) //for each node
			{
				tmpLim[0]=fcArray[i]->getNode(j)->getx();
				tmpLim[1]=fcArray[i]->getNode(j)->gety();
				tmpLim[2]=fcArray[i]->getNode(j)->getz();
				for(int k=0;k<3;k++)
				{
					lim_[k*2] = tmpLim[k]<lim_[k*2] ? tmpLim[k]:lim_[k*2] ;
					lim_[k*2+1] = tmpLim[k]>lim_[k*2+1] ? tmpLim[k]:lim_[k*2+1] ;
				}
			}
		}
	}
	Real Box::getSize(const int i)const
	{
		if(i==0)
			return (lim_[1]-lim_[0])<0.0? 0.0:(lim_[1]-lim_[0]);
		else if (i==1)
			return (lim_[3]-lim_[2])<0.0? 0.0:(lim_[3]-lim_[2]);
		else if (i==2)
			return (lim_[5]-lim_[4])<0.0? 0.0:(lim_[5]-lim_[4]);
		return 0.0;
	}

	MLGroup::MLGroup()
	{
		nFace_=0;
		fcArray_=NULL;
		for(int i=0;i<8;i++)child_[i]=NULL;
		minSize_=0.0;
		for(int i=0;i<3;i++) subgrid_[i]=false;
	}
	void MLGroup::Initialize(const int n, tri_face** ff,bool hardcopy)
	{
		
		nFace_=n;
		if(fcArray_!=NULL)
			delete[] fcArray_;
		if(hardcopy){
			fcArray_=new tri_face*[nFace_];
			memcpy((void*)fcArray_,(void*) ff,sizeof(tri_face*)*nFace_);
		}
		else{
			fcArray_=ff;
		}
// 		box_.setBoxLim(nFace_,fcArray_);
	}
	void MLGroup::setBoxLimit()
	{
		box_.setBoxLim(nFace_,fcArray_);
	}
	Real MLGroup::getMinSize()const
	{
		return minSize_;
	}
	void MLGroup::setMinSize(const Real ii)
	{
		minSize_=ii;
	}
	
	void MLGroup::MakeChild(Real minsize)
	{
		if(minsize>0.0)
			minSize_=minsize;
		Real size[3];
		int numberChild=1;
		for(int j=0;j<3;j++){
			subgrid_[j]=false;
			size[j]=box_.getSize(j);
			if(size[j] > minSize_){
				subgrid_[j]=true;
				numberChild*=2;
			}
		}
		if(numberChild==1)
			return;// no need to MakeChild again
		//child[0]  -X -Y -Z;
		//child[1]  -X -Y +Z;
		//child[2]  -X +Y -Z;
		//child[3]  -X +Y +Z;
		//child[4]  +X -Y -Z;
		//child[5]  +X -Y +Z;
		//child[6]  +X +Y -Z;
		//child[7]  +X +Y +Z;
		
	 	//if subgrid_[0]==false, only child[0,1,2,3] is valid;
		//if subgrid_[1]==false, only child[0,1,4,5] is valid;
		//if subgrid_[2]==false, only child[0,2,4,6] is valid;
		//Child Box  -x  -y  -z
		
		//Create the children's boxes.
		FCLIST fcList[8];
		for(int i=0;i<8;i++){
			child_[i]=NULL;
			fcList[i].clear();
		}
		Real tmpLimit[6];
		//child_[0]  -X -Y -Z;
		if(true){
			child_[0]=new MLGroup;
			tmpLimit[0]= box_.getLimit(0);
			tmpLimit[1]= subgrid_[0] ? box_.getMidPoint(0):box_.getLimit(1);
			tmpLimit[2]= box_.getLimit(2);
			tmpLimit[3]= subgrid_[1] ? box_.getMidPoint(1):box_.getLimit(3);
			tmpLimit[4]= box_.getLimit(4);
			tmpLimit[5]= subgrid_[2] ? box_.getMidPoint(2):box_.getLimit(5);
			for(int i=0;i<6;i++)
				child_[0]->box_.setLimit(i,tmpLimit[i]);
		}
		//child_[1]  -X -Y +Z;
		if(subgrid_[2]){
			child_[1]=new MLGroup;
			tmpLimit[0]= box_.getLimit(0);
			tmpLimit[1]= subgrid_[0] ? box_.getMidPoint(0):box_.getLimit(1);
			
			tmpLimit[2]= box_.getLimit(2);
			tmpLimit[3]= subgrid_[1] ? box_.getMidPoint(1):box_.getLimit(3);
			
			tmpLimit[4]= subgrid_[2] ? box_.getMidPoint(2):box_.getLimit(4);
			tmpLimit[5]= box_.getLimit(5);
			for(int i=0;i<6;i++)
				child_[1]->box_.setLimit(i,tmpLimit[i]);
		}
		//child_[2]  -X +Y -Z;
		if(subgrid_[1]){
			child_[2]=new MLGroup;
			tmpLimit[0]= box_.getLimit(0);
			tmpLimit[1]= subgrid_[0] ? box_.getMidPoint(0):box_.getLimit(1);
			
			tmpLimit[2]= subgrid_[1] ? box_.getMidPoint(1):box_.getLimit(2);
			tmpLimit[3]= box_.getLimit(3);
			
			tmpLimit[4]= box_.getLimit(4);
			tmpLimit[5]= subgrid_[2] ? box_.getMidPoint(2):box_.getLimit(5);
			for(int i=0;i<6;i++)
				child_[2]->box_.setLimit(i,tmpLimit[i]);
		}
		
		//child_[3]  -X +Y +Z;
		if(subgrid_[1]&&subgrid_[2]){
			child_[3]=new MLGroup;
			tmpLimit[0]= box_.getLimit(0);
			tmpLimit[1]= subgrid_[0] ? box_.getMidPoint(0):box_.getLimit(1);
			
			tmpLimit[2]= subgrid_[1] ? box_.getMidPoint(1):box_.getLimit(2);
			tmpLimit[3]= box_.getLimit(3);
			
			tmpLimit[4]= subgrid_[2] ? box_.getMidPoint(2):box_.getLimit(4);
			tmpLimit[5]= box_.getLimit(5);
			for(int i=0;i<6;i++)
				child_[3]->box_.setLimit(i,tmpLimit[i]);
		}
		//child_[4]  +X -Y -Z;
		if(subgrid_[0]){
			child_[4]=new MLGroup;
			tmpLimit[0]= subgrid_[0] ? box_.getMidPoint(0):box_.getLimit(0);
			tmpLimit[1]= box_.getLimit(1);
			
			tmpLimit[2]= box_.getLimit(2);
			tmpLimit[3]= subgrid_[1] ? box_.getMidPoint(1):box_.getLimit(3);
			
			tmpLimit[4]= box_.getLimit(4);
			tmpLimit[5]= subgrid_[2] ? box_.getMidPoint(2):box_.getLimit(5);
			for(int i=0;i<6;i++)
				child_[4]->box_.setLimit(i,tmpLimit[i]);
		}
		
		//child_[5]  +X -Y +Z;
		if(subgrid_[0]&&subgrid_[2]){
			child_[5]=new MLGroup;
			tmpLimit[0]= subgrid_[0] ? box_.getMidPoint(0):box_.getLimit(0);
			tmpLimit[1]= box_.getLimit(1);
			
			tmpLimit[2]= box_.getLimit(2);
			tmpLimit[3]= subgrid_[1] ? box_.getMidPoint(1):box_.getLimit(3);
			
			tmpLimit[4]= subgrid_[2] ? box_.getMidPoint(2):box_.getLimit(4);
			tmpLimit[5]= box_.getLimit(5);
			for(int i=0;i<6;i++)
				child_[5]->box_.setLimit(i,tmpLimit[i]);
		}
		//child_[6]  +X +Y -Z;
		if(subgrid_[0]&&subgrid_[1]){
			child_[6]=new MLGroup;
			tmpLimit[0]= subgrid_[0] ? box_.getMidPoint(0):box_.getLimit(0);
			tmpLimit[1]= box_.getLimit(1);
			
			tmpLimit[2]= subgrid_[1] ? box_.getMidPoint(1):box_.getLimit(2);
			tmpLimit[3]= box_.getLimit(3);
			
			tmpLimit[4]= box_.getLimit(4);
			tmpLimit[5]= subgrid_[2] ? box_.getMidPoint(2):box_.getLimit(5);
			for(int i=0;i<6;i++)
				child_[6]->box_.setLimit(i,tmpLimit[i]);
		}
		//child_[7]  +X +Y +Z;
		if(subgrid_[0]&&subgrid_[1]&&subgrid_[2]){
			child_[7]=new MLGroup;
			tmpLimit[0]= subgrid_[0] ? box_.getMidPoint(0):box_.getLimit(0);
			tmpLimit[1]= box_.getLimit(1);
			
			tmpLimit[2]= subgrid_[1] ? box_.getMidPoint(1):box_.getLimit(2);
			tmpLimit[3]= box_.getLimit(3);
			
			tmpLimit[4]= subgrid_[2] ? box_.getMidPoint(2):box_.getLimit(4);
			tmpLimit[5]= box_.getLimit(5);
			for(int i=0;i<6;i++)
				child_[7]->box_.setLimit(i,tmpLimit[i]);
		}
		for(int i=0;i<nFace_;i++){
			tri_face* fcPtr=fcArray_[i];
			for(int j=0;j<8;j++){
				if(child_[j]==NULL)
					continue;
				if( child_[j]->box_.checkIntersect(fcPtr)){
					fcList[j].push_back(fcPtr);
				}
			}
		}
		
		for(int j=0;j<8;j++){
			if(child_[j]==NULL)
				continue;
			int nnface= fcList[j].size();
			if(nnface==0){ //This sub block is empty
				delete child_[j];
				child_[j]=NULL;
				continue;  
			}
			tri_face** tmpFaceArray=new tri_face*[nnface];
			int cnt=0;
			for(FCLIST::iterator it= fcList[j].begin();it!=fcList[j].end();it++){
				tmpFaceArray[cnt]=*it;
				cnt++;
			}
			child_[j]->Initialize(nnface,tmpFaceArray,false);
		}
		
		
		//TODO 
		//check whether we can delete the memory for non-leave groups
		nFace_=0;
		delete[] fcArray_;
		fcArray_=NULL;		
		
		for(int j=0;j<8;j++){
			if(child_[j]==NULL)
				continue;
			child_[j]->MakeChild(minSize_);
		}
		
		

	}
	void MLGroup::setBoxLimit(const Real xmin,const Real xmax,
							  const Real ymin,const Real ymax,
		 					const Real zmin,const Real zmax)
	{
		box_.setLimit(xmin,xmax,ymin,ymax,zmin,zmax);
	}
	tri_face* MLGroup::findTriangle(const vector v)const
	{
		tri_face* result=NULL;
		bool inbox;
// #ifdef STRICK_CHECK
// 		if(!box_.checkInbox(v) && STRICT_CHECK){
// 			std::cerr<<" MLGroup fail to find the vector :"<< v.getx()<<" "<< v.gety()<<" "<< v.getz()<<"\n";
// 			std::cerr<<"Because the vector is out of the bound box of this group!\n";
// 			for(int i=0;i<6;i++)
// 				std::cerr<<box_.getLimit(i)<<"\n";
// 			
// 			return NULL;
// 		}
// #else
		
		inbox=box_.checkInbox(v);
		if(!inbox)
			return NULL;
// #endif
		assert( (isLeaf() && fcArray_!=NULL)|| ( !isLeaf() && fcArray_==NULL));
		if(isLeaf())
		{
			Real distance=MAX_DOUBLEFLOAT;
			tri_face* nearstFace=fcArray_[0];
			for(int i=0;i<nFace_;i++){
				if(fcArray_[i]->isInside(v))
					return fcArray_[i]; 
				if(fcArray_[i]->distanceEdge(v) < distance)
				{
					nearstFace=fcArray_[i];
					distance=fcArray_[i]->distanceEdge(v);
				}
			}
#if 1	
			std::cerr<<" MLGroup fail to find the vector :"<< v.getx()<<" "<< v.gety()<<" "<< v.getz()<<"\n";
			result= NULL;
#else
			result=nearstFace;
#endif
			return result;
		} 
		else
		{
			//TODO debug here
			int subGrid=0;
			if(v.getx() > box_.getMidPoint(0) &&subgrid_[0])
				subGrid+=4;
			if(v.gety() > box_.getMidPoint(1)&&subgrid_[1])
				subGrid+=2;
			if(v.getz() > box_.getMidPoint(2)&&subgrid_[2])
				subGrid+=1;
			if(child_[subGrid]!=NULL) //ordinary case
				result= child_[subGrid]->findTriangle(v);
			else
			{ //in this case, the observation point is having some error.
			        return NULL;
				MLGroup* chosen=NULL;
				Real distan=MAX_DOUBLEFLOAT;
				std::map<Real,tri_face*> tmpTree;
				tmpTree.clear();
					
				for(int ii=0;ii<8;ii++)
				{
					if(child_[ii]==NULL)
						continue;
					tri_face* tt=child_[ii]->findTriangle(v);
					std::pair<Real,tri_face*> pr=std::pair<Real,tri_face*>(tt->distanceEdge(v),tt);
					tmpTree.insert(pr);					
// 					if(chosen==NULL)
// 					{
// 						chosen=child_[ii];
// 						distan=chosen->findDist(v);						
// 					}
// 					else{
// 						if(chosen->findDist(v) < distan){
// 							chosen=child_[ii];
// 							distan=chosen->findDist(v);
// 						}
// 					}
				}
				result=tmpTree.begin()->second;
			}
			return result;
		}
		return result;
	}
	bool MLGroup::isLeaf()const
	{
		return !(subgrid_[0]||subgrid_[1]||subgrid_[2]);
	}
	void MLGroup::freeMemory()
	{
		if(fcArray_!=NULL){
			nFace_=0;
			delete[] fcArray_;
			fcArray_=NULL;
		}
		for(int i=0;i<8;i++){
			if(child_[i]!=NULL){
				child_[i]->freeMemory();
				delete child_[i];
				child_[i]=NULL;
			}
		}
		
	}
// 	MLGroup::~MLGroup()
// 	{
// 		freeMemory();
// 		for(int i=0;i<8;i++){
// 			if(child_[i]!=NULL){
// 				delete child_[i];
// 				child_[i]=NULL;
// 			}
// 		}
// 	}
	void MLGroup::Display()const
	{
	}
}
