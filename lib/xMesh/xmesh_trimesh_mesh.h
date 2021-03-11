#ifndef XMESH_TRIMESH_MESH_H
#define XMESH_TRIMESH_MESH_H
#include <xmesh_global.h>
#include <xmesh_trimesh_declaration.h>
#include <xmesh_trimesh_sort.h>
#include <set>
#include <vector>
#include <list>
#include <iostream>
#include <string>
namespace xMesh{
	typedef std::list<tri_face*> ListFace;
	enum TriNormalDirection{RH,LH,NA};
	class tri_mesh
	{
		private:
			bool verbose_;
			int nTri_;
			int nEdge_;
			int nNode_;
			tri_face* tri_;
			tri_edge* edge_;
			tri_node* node_;
			
			std::set<tri_node*,tri_sort> treeNodePtr_;
			std::set<tri_edge*,tri_sort> treeEdgePtr_;
			std::set<tri_face*,tri_sort> treeFacePtr_;
			std::string name_;
			TriNormalDirection* normal_;
			ListFace * nodeToFace_;
			Real unit_;
		public:
			tri_mesh();
			~tri_mesh();
			
			void freeMemory();
			void setName(const char*);
			void setName(const std::string&);
                        const char* getName()const{return name_.c_str();}
//                         std::string getName()const{return name_;}
			//Create 
			int importFromTriFile(char *);
			int importFromTriFileById(char *);
			void exportToTriFile(char* =NULL,int=5)const;
			void importFromFEMABCFile(char* fname);
// 			void buildFromTris(int nTri,tri_face* tri);
			void reinitialize(int ,int,int);
			
			void setVerbose(bool r);
			//Access 
			tri_face* getTriPtr(int i=0)const;
			tri_edge* getEdgePtr(int i=0)const;
			tri_node* getNodePtr(int i=0)const;
			tri_node* findNode(  tri_node* input);
			tri_face* findTri(  tri_face* input);
			tri_edge* findEdge(  tri_edge* input);
			int getnNode()const;
			int getnEdge()const;
			int getnTri()const;
			tri_face& getTri(int i);
			tri_edge& getEdge(int i);
			tri_node& getNode(int i);
			TriNormalDirection getNormal(int i)const;
			Real getUnit()const;
			std::vector<int> getFlagVector()const;
			
			//Manually operation
			void setTriPtr(tri_face* ); //using of this function should be avoid;
			void setEdgePtr(tri_edge* ); //using of this function should be avoid;
			void setNodePtr(tri_node* ); //using of this function should be avoid;
			
			void setTri(tri_face* ); //using of this function should be avoid;
			void setEdge(tri_edge* ); //using of this function should be avoid;
			void setNode(tri_node* ); //using of this function should be avoid;
			
			
			
			//Operation:
			const tri_face* findMatchedFace(const tri_face* input)const;
			const tri_face* findMatchedFaceByNode(const vector inputNode,const tri_face* seed=NULL) const;
			const tri_face* findMatchedFace(const vector inputNode,const tri_face* seed=NULL) const;
			const tri_face* findMatchedFaceBruteForce(const vector inputNode) const;
			std::list<const tri_face*> getNeighbourTriangles(const tri_face* fc)const;
			bool regularize();
			
			
			//internal function
			void buildNodeTree();
			void buildEdgeTree();
			void buildFaceTree();
			void ImportByTri(const int _nFace,const tri_face** face_external);
			
			//summary
			void printSummary(std::ostream&);
	};
}
#endif
