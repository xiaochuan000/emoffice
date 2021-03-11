#ifndef XMESH_BASE_EDGE_H
#define XMESH_BASE_EDGE_H
#include <xmesh_global.h>
namespace xMesh{
	class base_edge{
		private:
			int nNode_;
			base_node** nodePtr_;
			int id_;
		public:
			base_edge();
			~base_edge();
			base_edge(const base_edge& right);
			base_edge& operator=(const base_edge& right);
			void setnNode(const int);
			void InitNode();
			void setNode(const int,  base_node*);
			base_node* getNode(int )const;
			int getNNode()const;
			void setId(const int);
			int getId()const;
			
			/////////////////////////////
			//auxiliary functions
			virtual Real getLength()const;
			//get the vector pointing  node[0] -> node[nNode-1]
			vector getEdgeVector()const;
			//Given a node ptr, find the localId of this node, 
			//will return -1 if it is not found in this edge;
			int findLocalId(const base_node*)const;
			vector getMidPoint()const;

			//Some virtual function to be implemented by derived classes.
			virtual vector getVector ()const;
			virtual Real  getDistance(const vector nn) const;
			
	};
}  
#endif
