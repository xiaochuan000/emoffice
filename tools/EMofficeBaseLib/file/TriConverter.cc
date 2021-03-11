#include<fstream>
#include<iostream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;
int a2b(const char*);
int b2a(const char*);
typedef double Real;
typedef int Integer;
int PRECISION=10;

char* outputName=NULL;
bool linenumber=false;
int main(int argc,char* argv[])
{
	cout<<"Usage:"<<argv[0]<<" filename opts\n";
	cout<<"opt:\t -l:\t adding line number (ascii only)\n";
	cout<<"opt:\t -o:\t o assign output name\n";
	if(argc<2) return -1;

 	char* prjName=argv[1];
	bool _a2b=false;//ascii to binary
	bool _b2a=false;//binary to ascii
	if(strcmp( &(prjName[strlen(prjName)-3]),"TRI")==0)
	{
		_b2a=true;
	}
	if(strcmp( &(prjName[strlen(prjName)-3]),"tri")==0)
        {
                _a2b=true;
        }
		


	char c;
	while((c=getopt(argc-1,&(argv[1]),"lbao:"))!=-1){
		switch(c){
			case 'l':
				linenumber=true;
				break;
			case 'a':
				cout<<"Forced binary -> ascii!\n";
				_b2a=true;_a2b=false;
				break;
			case 'b':
				cout<<"Forced ascii -> binary!\n";
				_a2b=true;_b2a=false;
				break;
			case 'o':
				outputName=new char[strlen(optarg)+1];
				sprintf(outputName,"%s",optarg);
				break;
			case '?':
				if(optopt=='o'){
					cout<<"option o need a parameter!\n";
				}
				else {
					cout<<"Unknown opt parameter "<<optopt<<endl;
				}
				return -1;
				
			default:
				abort();
		}
	}
		
		
	if(getenv("EMOFFICE_PRECISION")!=NULL){
		PRECISION= atoi(getenv("EMOFFICE_PRECISION"));
// 		cout<<"Precision set to "<<PRECISION<<endl;
	}
	if(_b2a&&_a2b){
		cout<<"Confused....\n";
		return -1;
	}
	if(_b2a){
		cout<<"binary to ascii!\n";
		b2a(prjName);
	}
	if(_a2b){
		cout<<"ascii to binary!\n";
		a2b(prjName);
	}
	if(outputName!=NULL)
		delete[] outputName;
	return 0;
}
int a2b(const char* filename)
{
	char buf[0x200];
	Real scale=1.0;
	Real tmpr[3];
	Integer itmp[3];
	Integer nNode=0;
	Integer nTri=0;
	if(outputName==NULL){
		sprintf(buf,"%s",filename);
		buf[strlen(buf)-3]='T';
		buf[strlen(buf)-2]='R';
		buf[strlen(buf)-1]='I';
	}
	else{
		sprintf(buf,"%s",outputName);
		cout<<"Output name: "<< buf<<endl;
	}
	ifstream fin;
	ofstream fout;
	fin.open(filename);
	if(fin.is_open()==false){
		cout<<"Error! "<<filename<<" cannot be opened!\n";
		exit(-1);
	}
	fout.open(buf,ios::binary);
// 	fout<<0<<"\0";
	fin>>scale;
	assert(scale!=0.0);
	fout.write((char*)(&scale),sizeof(Real));
	fin>>nNode;
	fout.write((char*)(&nNode),sizeof(Integer));

	for(int i=0;i<nNode;i++){
		fin>>tmpr[0]>>tmpr[1]>>tmpr[2];
		tmpr[0]*=scale;
		tmpr[1]*=scale;
		tmpr[2]*=scale;
		fout.write((char*)tmpr,sizeof(Real)*3);
	}
	fin>>nTri;
	fout.write((char*)(&nTri),sizeof(Integer));
	for(int i=0;i<nTri;i++){
		fin>>itmp[0]>>itmp[1]>>itmp[2];
		fout.write((char*)itmp,sizeof(Integer)*3);
	}
	fout.close();
	fin.close();	
	cout<<"Triangle conversion finished!\n";
}
int b2a(const char* filename)
{
	char buf[0x200];
	Real scale=1.0;
	Real tmpr[3];
	Integer itmp[3];
	Integer nNode=0;
	Integer nTri=0;
	char tmp;
// 	Integer 
	sprintf(buf,"%s",filename);
	if(outputName==NULL){
		sprintf(buf,"%s",filename);
		buf[strlen(buf)-3]='t';
		buf[strlen(buf)-2]='r';
		buf[strlen(buf)-1]='i';
	}
	else{
		sprintf(buf,"%s",outputName);
		cout<<"Output name: "<< buf<<endl;
	}
	ifstream fin;
	ofstream fout;
	fin.open(filename);
	fout.open(buf);
	if(fin.is_open()==false){
		cout<<"Error! "<<filename<<" cannot be opened!\n";
		exit(-1);
	}
	fin.read((char*)(&scale),sizeof(Real));
	fout.precision(PRECISION);
	fout<<scientific<<scale<<endl;
	fin.read((char*)(&nNode),sizeof(Integer));
	fout<<nNode<<endl;
	for(int i=0;i<nNode;i++){
		fin.read((char*)tmpr,sizeof(Real)*3);
		if(linenumber) 
			fout<<i<<"\t";
		fout<<tmpr[0]<<"\t"<<tmpr[1]<<"\t"<<tmpr[2]<<"\n";
	}
	fin.read((char*)(&nTri),sizeof(Integer));
	fout<<nTri<<endl;
	for(int i=0;i<nTri;i++){
		fin.read((char*)itmp,sizeof(Integer)*3);
		if(linenumber) 
			fout<<i<<"\t";		
		fout<<itmp[0]<<"\t"<<itmp[1]<<"\t"<<itmp[2]<<"\n";
	}
	
	fin.close();
	fout.close();
}
