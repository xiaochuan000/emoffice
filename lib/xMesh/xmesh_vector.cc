#include <xmesh_vector.h>
#include <math.h>
#include <fstream>
namespace xMesh
{
	Real Length(const vector a)
	{
		return a.norm();
	}
	vector::vector()
	{
		for(int i=0;i<3;i++)
			component[i]=0.0;
	}
	vector::vector(const vector& right)
	{
		for(int i=0;i<3;i++)
			component[i]=right.component[i];
	}
	Real vector::norm() const
	{
		Real result=0.0;
		for(int i=0;i<3;i++)
			result+=component[i]*component[i];
		return sqrt(result);
	}
	vector& vector::operator=(const vector& right)
	{
	#pragma unroll
		for(int i=0;i<3;i++)
			component[i]=right.component[i];
		return *this;
	}
	vector& vector::operator=(const Real a)
	{
		
		for(int i=0;i<3;i++)
			component[i]=a;
		return *this;
	}
	vector vector::operator+(const vector& right)const 
	{
		vector result;
		for(int i=0;i<3;i++)
			result.component[i]=component[i]+right.component[i];
		return result;
	}
	vector vector::operator-(const vector& right)const 
	{
		vector result;
		for(int i=0;i<3;i++)
			result.component[i]=component[i]-right.component[i];
		return result;
	}
	
	vector vector::operator*(const vector& right)const 
	{
		vector result;
		for(int i=0;i<3;i++)
			result.component[i]= (component[(i+1)%3]*right.component[(i+2)%3] - component[(i+2)%3]*right.component[(i+1)%3]);
		return result;
	}
	cvector vector::operator*(const cvector& right)const 
	{
		cvector result;
		for(int i=0;i<3;i++)
			result.component[i]= (component[(i+1)%3]*right.component[(i+2)%3] - component[(i+2)%3]*right.component[(i+1)%3]);
		return result;
	}
	vector vector::operator*(Real k)const 
	{
		vector result;
		for(int i=0;i<3;i++)
			result.component[i]=component[i]*k;
		return result;
	}
	cvector vector::operator*(Complex k)const 
	{
		cvector result;
		for(int i=0;i<3;i++)
			result.component[i]=component[i]*k;
		return result;
	}
	vector vector::operator/(Real k)const 
	{
		vector result;
		for(int i=0;i<3;i++)
			result.component[i]=component[i]/k;
		return result;
	}

	Real dotP(const vector a,const vector b)
	{
		Real result=0.0;
		result=a.x()*b.x()+a.y()*b.y()+a.z()*b.z();
		return result;
	}
	
	void vector::reset() 
	{
		for(int i=0;i<3;i++)
			component[i]=0.0;
	}
	void vector::normalize()
	{
		Real Norm=norm();
		assert(Norm>0.0);
		for(int i=0;i<3;i++)
			component[i]/=Norm;
	}
	/////////////////////////////////////////////////////////////////
	cvector::cvector()
	{
		component[0]=0.0;
		component[1]=0.0;
		component[2]=0.0;
	}
	cvector::cvector(const cvector& right)
	{
// 		x=right.x;
// 		y=right.y;
// 		z=right.z;
		for(int i=0;i<3;i++)
			component[i]=right.component[i];
	}
	cvector::cvector(const vector& right)
	{
// 		for(int i=0;i<3;i++)
	/*	component[0]=right.x();
		component[1]=right.y();
		component[2]=right.z();
	*/
		for(int i=0;i<3;i++)
			component[i]=right.component[i];
	}
	cvector& cvector::operator=(const cvector& right)
	{
		
		for(int i=0;i<3;i++)
			component[i]=right.component[i];
		return *this;
	}
	cvector& cvector::operator=(const vector& right)
	{
		
		for(int i=0;i<3;i++)
			component[i]=right.component[i];
		return *this;
	}
	cvector& cvector::operator=(const Complex a)
	{
		
		for(int i=0;i<3;i++)
			component[i]=a;
		return *this;
	}

	cvector cvector::operator+(const cvector& right)const
	{
		cvector result;
// 		result.x=x+right.x;
// 		result.y=y+right.y;
// 		result.z=z+right.z;
		for(int i=0;i<3;i++)
			result.component[i]=component[i]+right.component[i];
		return result;
	}
	cvector cvector::operator-(const cvector& right)const
	{
		cvector result;
		for(int i=0;i<3;i++)
			result.component[i]=component[i]-right.component[i];
		return result;
	}
	cvector cvector::operator*(const cvector& right)const
	{
		cvector result;
/*		result.x=y*right.z-z*right.y;
		result.y=z*right.x-x*right.z;
		result.z=x*right.y-y*right.x;
	*/	
		for(int i=0;i<3;i++)
			result.component[i]=(component[(i+1)%3]*right.component[(i+2)%3])-(component[(i+2)%3]*right.component[(i+1)%3]);

		return result;
	}
	cvector cvector::operator*(const Complex k)const
	{
		cvector result;
		result.reset();
		for(int i=0;i<3;i++)
			result.component[i]=component[i]*k;
		return result;
	}
	cvector cvector::operator*(const Real k)const
	{
		cvector result;
		result.reset();
		for(int i=0;i<3;i++)
			result.component[i]=component[i]*k;
		return result;
	}
	cvector cvector::operator/(const Complex k)const
	{
		cvector result;
		for(int i=0;i<3;i++)
			result.component[i]=component[i]/k;
		return result;
	}
	bool operator==(const cvector a,const cvector b)
	{
		
		if(a.x()==b.x() 
				 && a.y()==b.y() 
				 && a.z()==b.z())
			return true;
		cvector diff=a-b;
		
		if(diff.norm()<ZERO_GEOMETRY)
			return true;
		return false;
	}

	Real cvector::norm() const
	{
		return sqrt( (component[0]*conj(component[0])+component[1]*conj(component[1])+component[2]*conj(component[2])).real());
	}
	Complex dotP(const cvector a,const cvector b)
	{
		Complex result(0.0,0.0);
// 		for(int i=0;i<3;i++)
// 			result=result+a.component[i]*conj(b.component[i]);
		// 		
		result=a.x()*conj(b.x())+a.y()*conj(b.y())+a.z()*conj(b.z());
		return result;
	}
	void cvector::reset() 
	{
		for (int i=0;i<3;i++)
			component[i]=Complex (0.0,0.0);
	}
	void vector::reverse()
	{
		for(int i=0;i<3;i++)
			component[i]=-component[i];
	}
	std::ostream& operator<< (std::ostream &outputFile, const vector &reg)
	{
		outputFile<< reg.getx()<<"\t"<< reg.gety()<<"\t"<< reg.getz()<<"\t";
		return outputFile;
	}
	void vector::print()const
	{
		std::cout<<getx()<<"\t"<<gety()<<"\t"<<getz()<<"\n";
	}
}
