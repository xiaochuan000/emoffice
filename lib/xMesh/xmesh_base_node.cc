#include <xmesh_base_node.h>
// #include "xmesh_vector.h"
#include <xmesh_constants.h>
namespace xMesh
{
// 	bool operator==(const base_node& a, const base_node& b)
// 	{
// 		return a.vec_==b.vec_;
// 	}
	base_node::base_node(){
		id_=NOT_NUMBERED;
		vec_=vector(0.0,0.0,0.0);
	}
	base_node::base_node(const base_node& right){
		id_=right.id_;
		vec_=right.vec_;
	}
	base_node& base_node::operator=(const base_node& right){
		id_=right.id_;
		vec_=right.vec_;
		return *this;
	}
	void base_node::setId(const int i){
		id_=i;
	}
	int base_node::getId()const{
		return id_;
	}
	void base_node::setVector(const vector v){
		vec_=v;
	}
	void base_node::setCoordinate(double x,double y,double z){
		vec_=vector(x,y,z);
	}	
	vector base_node::getVector() const{
		return vec_;
	}
	Real base_node::getx()const{
		return vec_.getx();
	}
	Real base_node::gety()const{
		return vec_.gety();
	}

	Real base_node::getz()const{
		return vec_.getz();
	}
	Real& base_node::x(){
		return vec_.x();
	}
	Real& base_node::y(){
		return vec_.y();
	}
	Real& base_node::z(){
		return vec_.z();
	}

}
