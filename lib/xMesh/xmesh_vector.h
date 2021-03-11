#ifndef XMESH_VECTOR_H
#define XMESH_VECTOR_H
#include <xmesh_constants.h>
#include <xmesh_global.h>

#include <CGAL/Cartesian_d.h>
#include <CGAL/point_generators_d.h>
#include <CGAL/Kd_tree.h>
#include <CGAL/Fuzzy_sphere.h>
#include <CGAL/Fuzzy_iso_box.h>
#include <CGAL/Search_traits_d.h>

namespace xMesh
{
	
	typedef CGAL::Cartesian_d<Real> K;
	typedef K::Point_d Point_d;
	class vector;
	class cvector;
	bool operator<(const vector& a,const vector& b);
	bool operator>(const vector& a,const vector& b);
	bool operator==(const vector& a,const vector& b);
	class vector
	{
		friend class cvector;
		friend bool operator< (const vector& a,const vector& b);
		friend bool operator== (const vector& a,const vector& b);
// 		friend bool operator<(const vector a,const vector b);
		private:
			Real component[3];
		public:
			
			vector();
			vector(float a,float b,float c){component[0]=a;component[1]=b;component[2]=c;}
			vector(double a,double b,double c){component[0]=a;component[1]=b;component[2]=c;}
			vector(const vector& right);
			vector& operator =(const vector& right);
			vector& operator =(const Real);
			
			void setvtr(const float a,const float b,const float c){component[0]=a;component[1]=b;component[2]=c;}
			void setvtr(const double a,const double b,const double c){component[0]=a;component[1]=b;component[2]=c;}
			vector operator +(const vector& right) const ;
			vector operator -(const vector& right) const ;
			vector operator *(const vector& right) const ;
			cvector operator *(const cvector& right) const ;
			vector operator *(Real)             const ;
			cvector operator *(Complex)             const ;
			vector operator /(Real) const;
			
			Real norm()const ;
			void normalize();
			void reset();
			Real x()const{return component[0];}
			Real y()const{return component[1];}
			Real z()const{return component[2];}
			Real getx()const{return component[0];}
			Real gety()const{return component[1];}
			Real getz()const{return component[2];}
			Real& x(){return component[0];}
			Real& y(){return component[1];}
			Real& z(){return component[2];}
			Real magnitude()const{return norm();}
			void reverse();
			void print()const;			
	};
	std::ostream& operator<< (std::ostream &outputFile, const vector &reg);
	Real dotP(const vector,const vector);
	Real Length(const vector a);
	class cvector
	{
	    friend class vector;
		private:
			Complex component[3];
		public:
// 			Complex x,y,z;
			
			cvector();
			cvector(const cvector& right);
			cvector(const vector& right);
			cvector(const std::complex<float>  a, const std::complex<float>  b, const std::complex<float>  c) {component[0]=a;component[1]=b;component[2]=c;}
			cvector(const std::complex<double> a, const std::complex<double> b, const std::complex<double> c) {component[0]=a;component[1]=b;component[2]=c;}
			cvector& operator =(const cvector& right);
			cvector& operator =(const vector& right);
			cvector& operator =(const Complex);
			
			
			void setcvtr(const std::complex<float>  a, const std::complex<float>  b, const std::complex<float>  c){component[0]=a;component[1]=b;component[2]=c;}
			void setcvtr(const std::complex<double> a, const std::complex<double> b, const std::complex<double> c){component[0]=a;component[1]=b;component[2]=c;}
			cvector operator +(const cvector& right)const;
			cvector operator -(const cvector& right)const;
			cvector operator *(const cvector& right)const;
			cvector operator *(const Complex)const;
			cvector operator *(const Real)const;
			cvector operator /(const Complex )const;
			
			Real norm()const ;
			void reset();
			Complex& x(){return component[0];}
			Complex& y(){return component[1];}
			Complex& z(){return component[2];}
			Complex x()const {return component[0];}
			Complex y()const {return component[1];}
			Complex z()const {return component[2];}
			Complex getx()const{return component[0];}
			Complex gety()const{return component[1];}
			Complex getz()const{return component[2];}
// 			friend Complex dotP(const cvector a,const cvector b)
			
			
			
	};
	Complex dotP(const cvector,const cvector);


	bool operator==(const cvector& a,const cvector& b);
}
#endif
