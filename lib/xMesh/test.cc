#include "xmesh_trimesh_mesh.h"
#include <fstream>
#include <iostream>
using namespace xMesh;
void showUsage(){
	std::cout<<"Usage: bin prjName\n";
	
}
int main(int argc,char* argv[])
{
	showUsage();
	if(argc!=2)
		return -1;
	char buf[0x200];
	char* prjName=argv[1];
	
	tri_mesh* mesh=new tri_mesh;
	mesh->importFromTriFile(prjName);
			
	sprintf(buf,"out");
	mesh->exportToTriFile(buf);
	
	delete mesh;
	 
}
