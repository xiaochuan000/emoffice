#include <xmesh_trimesh_node.h>
#include <xmesh_trimesh_edge.h>
#include <xmesh_vector.h>
#include <xmesh_trimesh_face.h>
#include <xmesh_trimesh_sort.h>
#include <math.h>
#include <set>
#include <map>

namespace xMesh{
	bool checkAntiParallel(const vector a,const vector b)
	{

		vector n=a*b/(a.norm()*b.norm());
		if(n.norm()>TOL_CHECKPARALLEL)
			return false;
// 		std::cout<<dotP(a,b)/(a.norm()*b.norm())<<std::endl;
		if(dotP(a,b)<0.0)
			return true;
		else if(dotP(a,b)>0.0)
			return false;
		else
			return false;
	}
	bool checkParallel(const vector a,const vector b)
	{

		vector n=a*b/(a.norm()*b.norm());
		if(n.norm()>TOL_CHECKPARALLEL)
			return false;
// 		std::cout<<dotP(a,b)/(a.norm()*b.norm())<<std::endl;
		if(dotP(a,b)<0.0)
			return false;
		else if(dotP(a,b)>0.0)
			return true;
		else
			return false;
	}
	tri_face::tri_face(){
		setnEdge(3);
		InitEdge();
		setEdge(0,NULL);
		setEdge(1,NULL);
		setEdge(2,NULL);
		flag_=0;//by default
		normal_=true;
	}
	tri_face::tri_face(const tri_face& right): base_face(right){
		normal_=right.normal_;
		flag_=right.flag_;
	}
	tri_face::tri_face(tri_edge* edge0,tri_edge* edge1,tri_edge* edge2)
	{
		setEdge(0,edge0);
		setEdge(1,edge1);
		setEdge(2,edge2);
		
		vector Node0[3];
		vector Node1[3];
		for(int i=0;i<3;i++)
			Node0[i]=getEdge(i)->getNode(0)->getVector();
		for(int i=0;i<3;i++)
			Node1[i]=getEdge(i)->getNode(1)->getVector();
		
		
		for(int i=0;i<3;i++)
		{
			int indexNext=(i+1)%3;
			int indexPrev=(i+2)%3;
			
			if( (Node0[i] == Node0[indexPrev] || Node0[i] == Node1[indexPrev]) &&
			  (Node1[i] == Node0[indexNext] || Node1[i] == Node1[indexNext]))
						  order_[i]=true;
			else if	( (Node1[i] == Node0[indexPrev] || Node1[i] == Node1[indexPrev]) &&
				(Node0[i] == Node0[indexNext] || Node0[i] == Node1[indexNext]))
							order_[i]=false;
		}
		normal_=true;
		flag_=0;
	}
	void tri_face::setEdge3(tri_edge* edge0,tri_edge* edge1,tri_edge* edge2)
	{
		setEdge(0,edge0);
		setEdge(1,edge1);
		setEdge(2,edge2);
		
		vector Node0[3];
		vector Node1[3];
		for(int i=0;i<3;i++)
			Node0[i]=getEdge(i)->getNode(0)->getVector();
		for(int i=0;i<3;i++)
			Node1[i]=getEdge(i)->getNode(1)->getVector();
		
		
		for(int i=0;i<3;i++)
		{
			int indexNext=(i+1)%3;
			int indexPrev=(i+2)%3;
			
			if( (Node0[i] == Node0[indexPrev] || Node0[i] == Node1[indexPrev]) &&
						  (Node1[i] == Node0[indexNext] || Node1[i] == Node1[indexNext]))
				order_[i]=true;
			else if	( (Node1[i] == Node0[indexPrev] || Node1[i] == Node1[indexPrev]) &&
							(Node0[i] == Node0[indexNext] || Node0[i] == Node1[indexNext]))
				order_[i]=false;
		}
		
	}
	tri_node* tri_face::getNode(int i)const
	{
		int index=(i+1)%3;
		if(order_[index])
			return static_cast<tri_node*> (getEdge(index)->getNode(1));
		else
			return static_cast<tri_node*> (getEdge(index)->getNode(0));
	}
	vector tri_face::getCenter()const
	{
		vector result(0.0,0.0,0.0);
		for(int i=0;i<3;i++)
			result=result+getEdge(i)->getMidPoint();
		return result*(1.0/3.0);
	}
	Real tri_face::getAspectRatio()const
	{
		std::set<Real> angleMap;
		angleMap.clear();
		for(int i=0;i<3;i++)
			angleMap.insert(getAngleRad(i));
		Real minAngle= *(angleMap.begin());
		Real maxAngle= *(angleMap.rbegin());
		return 0.0;		
	}
	Real tri_face::getAngleRad(int i) const
	{
		vector a=getEdge((i+1)%3)->getVector();
		vector b=getEdge((i+2)%3)->getVector();
		Real Asin=(a*b).norm()/(a.norm()*b.norm());
		return asin(Asin);
	}
	Real tri_face::getAngleDeg(int i)const
	{
		return 180.0*getAngleDeg(i)/xmeshPI;
	}
	
	Real tri_face::getInnerRadius()const
	{
		Real sumL=0.0;
		for(int i=0;i<3;i++)
			sumL+=getEdge(i)->getLength();
		Real area=0.0;
		area=getArea();
		return 2.0*area/sumL;
	}
	Real tri_face::getOuterRadius()const
	{
		Real ang[3];
		for(int i=0;i<3;i++)
			ang[i]=getAngleRad(i);
		Real sinAngleSum=0.0;
		for(int i=0;i<3;i++)
			sinAngleSum+=sin(-ang[i]+ang[(i+1)%3]+ang[(i+2)%3]);
		Real Rsq=2*getArea()/sinAngleSum;
		return sqrt(Rsq);
	}
	Real tri_face::getArea()const
	{
		Real s=0.0;
		Real a[3];
		for(int i=0;i<3;i++){
			a[i]=getEdge(i)->getLength();
			s+= a[i];
		}
		s/=2.0;
		return sqrt(s*(s-a[0])*(s-a[1])*(s-a[2]));
	}
	void tri_face::reverseDirection()
	{
		for(int i=0;i<3;i++)
			order_[i]=!order_[i];
	}
	vector tri_face::getNormal()const
	{
		//Convention: right hand 
		//edge 0 x edge 1
		vector e0=getEdge(0)->getVector();
		vector e1=getEdge(1)->getVector();
		if(order_[0]==false)
			e0.reverse();
		if(order_[1]==false)
			e1.reverse();
		vector result=e0*e1;
		//std::cout<<"!!!";
#ifdef STRICT
		assert(result.norm()>0.0);
#endif
		if(result.norm()>0.0) //If not satisfied, illegal triangle (line) is encountered!\n"
			result.normalize();
		return result;
	}
	
	void tri_face::print()const
	{
		std::cout<<"tri_face::print()\n";
	}
	
	
	
	bool tri_face::isInside(const vector n)const //TOVERIFTY
	{
		base_node* localNode[3];
		localNode[0]=getEdge(0)->getNode(0);
		localNode[1]=getEdge(0)->getNode(1);
		if(*(localNode[0]) == *(getEdge(1)->getNode(0)) || *(localNode[1]) == *(getEdge(1)->getNode(0)))
			localNode[2]=getEdge(1)->getNode(1);
		else
			localNode[2]=getEdge(1)->getNode(0);
		vector vv[3];
	
		//at one vertex ;
		
		vv[0]= localNode[0]->getVector() - n;
		vv[1]= localNode[1]->getVector() - n;
		vv[2]= localNode[2]->getVector() - n;

#if 0	
		if(vv[0].norm()<TOL_CHECKISINSIDE ||vv[1].norm()<TOL_CHECKISINSIDE ||vv[2].norm()<TOL_CHECKISINSIDE)
			return false; 
#else
		if(vv[0].norm()<TOL_CHECKISINSIDE ||vv[1].norm()<TOL_CHECKISINSIDE ||vv[2].norm()<TOL_CHECKISINSIDE)
			return true; 
	
#endif
		vector cross[3];
		cross[0]=vv[0]*vv[1] /(vv[0].norm() *vv[1].norm());
		cross[1]=vv[1]*vv[2] /(vv[1].norm() *vv[2].norm());
		cross[2]=vv[2]*vv[0] /(vv[2].norm() *vv[0].norm());

		if(checkAntiParallel(vv[0],vv[1]) || checkAntiParallel(vv[2],vv[1]) ||checkAntiParallel(vv[0],vv[2]) )
			return true;
		if(checkParallel(vv[0],vv[1]) || checkParallel(vv[2],vv[1]) ||checkParallel(vv[0],vv[2]) )
			return false;
// #endif
		Real innerP[3];
		cross[0].normalize();
		cross[1].normalize();
		cross[2].normalize();
		
		innerP[0]=dotP(cross[0],cross[1]);
		innerP[1]=dotP(cross[1],cross[2]);
		innerP[2]=dotP(cross[2],cross[0]);
		Real sum= (innerP[0]+innerP[1]+innerP[2])/3.0;
		if(fabs(sum-1.0)<TOL_CHECKISINSIDE)
			return true;
		else
			return false;
	}
	
	
	Real tri_face::distanceCenter(const vector nn) const
	{
		//calculate the distance between the node and the geometrical center of triangle
		vector center(0.0,0.0,0.0);
		for(int i=0;i<3;i++)
			center= center+ getNode(i)->getVector();
		center=center /3.0;
		
		center=center-nn;
		return center.norm();
	}
	Real tri_face::distanceEdge(const vector nn) const
				 //find the distance of a point to the nearest edge of the triangles.
	{
		if(isInside(nn))
			return 0.0;
		
		Real distance=MAX_DOUBLEFLOAT;
		for( int i=0;i<3;i++)
		{
			Real d=getEdge(i)->getDistance(nn);
			if(d<distance)
				distance=d;
		}
		
		return distance;	
	}
	void tri_face::checkEdge() //if the edge direction is conformal, then set the edgeDirection flag to be true, else,set it to be false;
	{
		for(int i=0;i<3;i++)
		{
			if( ( *(getEdge(i)->getNode(1))  == *(getEdge((i+1)%3)->getNode(0)) 
						     || *(getEdge(i)->getNode(1)) == *(getEdge((i+1)%3)->getNode(1)) )
						     &&( *(getEdge(i)->getNode(0))  == *(getEdge((i+2)%3)->getNode(0)) 
						     || *(getEdge(i)->getNode(0)) == *(getEdge((i+2)%3)->getNode(1)) ))
			{
				order_[i]=true;
			}
			else
				order_[i]=false;
		}
	}
	bool tri_face::getOrder(int i)const
	{
		return order_[i];
	}
	int tri_face::findEdgeIndex(tri_edge* input)const
	{//TODO
	
		for(int i=0;i<getnEdge();i++)
		{
			tri_edge* ie;
			ie=static_cast<tri_edge*>(this->getEdge(i));
			if( (*input)== (* ie))
				return i;
		}
		return -1;
	}	
	void tri_face::setFlag(int i)
	{
		flag_=i;
	}
	int tri_face::getFlag()const{
		return flag_;
	}
        int tri_face::getLocalNodeNum(const tri_node* right)const{
                for(int i=0;i<3;i++){
                        if( (*right) == (*(getNode(i)))){
                                return i;
                        }
                }
                return -1;
        }
        int tri_face::getLocalEdgeNum(const tri_edge* right)const{
                for(int i=0;i<3;i++){
                        if( (*right) == (*(getTriEdge(i)))){
                                return i;
                        }
                }
                return -1;
        }
        tri_edge* tri_face::getTriEdge(int i)const
        {
                return static_cast<tri_edge*>(getEdge(i));
        }
	void tri_face::setNormal(bool n)
	{
		normal_=n;
	}
	bool tri_face::getNormalFlag()const
	{
		return normal_;
	}
	void tri_face::getTriNodes3(int* exp) const 
	{ 
		if (normal_){
			exp[0]=getNode(0)->getId();
			exp[1]=getNode(1)->getId();
			exp[2]=getNode(2)->getId();
		}
		else{
			exp[0]=getNode(0)->getId();
			exp[1]=getNode(2)->getId();
			exp[2]=getNode(1)->getId();
		}
	}
	void tri_face::getBary(const vector vr,Real* bary)const
	{
		Real area=getArea();
		for(int i=0;i<3;i++){
			vector v1=getNode((i+1)%3)->getVector()-vr;
			vector v2=getNode((i+2)%3)->getVector()-vr;
			vector v1xv2=v1*v2;
			bary[i]= v1xv2.norm()/(2.0*area);
		}
	}
	void tri_face::setCnt(int i,int j){
		cnt_[i]=j;
	}
	int tri_face::getCnt(int i)const{
		return cnt_[i];
	}
	tri_node* tri_face::getThirdNode(const tri_edge* edge)const
	{
		bool match=false;
		for(int i=0;i<3;i++){
			if( *edge == *(static_cast<tri_edge*> (getEdge(i)) ))
				match=true;
		}
		if(match==false){
			std::cout<<"Warning,tri_node* tri_face::getThirdNode(const tri_edge* edge)const \n";
			std::cout<<"The edge input is not in the triangles\n";
		}	
		tri_node* nd0=static_cast<tri_node*> (edge->getNode(0));
		tri_node* nd1=static_cast<tri_node*> (edge->getNode(1));
		for(int i=0;i<3;i++){
			tri_edge* ied;
			ied=static_cast<tri_edge*>  (this->getEdge(i));
			for(int j=0;j<2;j++){
				tri_node* ind=static_cast<tri_node*>( ied->getNode(j));
				if( !(*ind == *nd0) && !(*ind == *nd1)){
					return ind;
				}
			}
		}
		return NULL;
	}
	void printTri(tri_face* fc)
	{
		std::cout<<"Tri:\n";
		std::cout<<"("<<fc->getNode(0)->getx()<<","<<fc->getNode(0)->gety()<<","
				<<fc->getNode(0)->getz()<<")-("<<fc->getNode(1)->getx()<<","<<fc->getNode(1)->gety()<<","
				<<fc->getNode(1)->getz()<<")-("<<fc->getNode(2)->getx()<<","<<fc->getNode(2)->gety()<<","
				<<fc->getNode(2)->getz()<<")"<<std::endl<<std::endl;
	}
}
