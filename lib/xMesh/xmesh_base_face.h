#ifndef XMESH_BASE_FACE_H
#define XMESH_BASE_FACE_H
#include <xmesh_global.h>
namespace xMesh{
	class base_face{
		private:
			int nEdge_;
			base_edge** edgePtr_;
			int id_;
		public:
			base_face();
			base_face(const int n, base_edge** =NULL);
			base_face(const base_face&);
			~base_face();
			void 	setId(int);
			int 	getId(void )const;
			void 	setnEdge(int);
			int 	getnEdge()const;
			void 	InitEdge();
			void 	setEdge(int,base_edge*);
			base_edge* getEdge(int i)const;
			
			virtual void print() const;
			int findEdgeIndex(base_edge*)const;
	};
}
#endif
