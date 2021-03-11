	BoxTri::BoxTri()
{
	xlim_[0]=MAX_DOUBLEFLOAT;
	xlim_[1]=-MAX_DOUBLEFLOAT;
	ylim_[0]=MAX_DOUBLEFLOAT;
	ylim_[1]=-MAX_DOUBLEFLOAT;
	zlim_[0]=MAX_DOUBLEFLOAT;
	zlim_[1]=-MAX_DOUBLEFLOAT;
	for(int i=0;i<8;i++)
		child_[i]=NULL;
	nFace_=0;
	face_=NULL;
	flag_=UNINIT;
	for(int i=0;i<3;i++){
		subgrid[i]=false;
		minBoxSize[i]=0.0;
	}
}
	void BoxTri::setMinBoxSize(int flag, Real r)
{
	if(flag|1 !=0)
		minBoxSize[0]=r;
	if(flag|2 !=0)
		minBoxSize[1]=r;
	if(flag|4 !=0)
		minBoxSize[2]=r;
}
	void BoxTri::Initialize(int nFace, tri_face** facePtr)
{
		//check the validation:
	if(minBoxSize[0]==0.0 ||minBoxSize[1]==0.0 ||minBoxSize[2]==0.0){
		std::cerr<<"Error! illegal minimum box size detected!\n";
		return;
	}
		
		//Step 1 get the bounding box for all the faces. 
	for(int i=0;i<nFace;i++){
		for(int j=0;j<3;j++){
			vector iv=facePtr[i]->getNode(j)->getVector();
			xlim_[0]= iv.getx()< xlim_[0]? iv.getx(): xlim_[0];
			xlim_[1]= iv.getx()> xlim_[1]? iv.getx(): xlim_[1];
			ylim_[0]= iv.gety()< ylim_[0]? iv.gety(): ylim_[0];
			ylim_[1]= iv.gety()> ylim_[1]? iv.gety(): ylim_[1];
			zlim_[0]= iv.getz()< zlim_[0]? iv.getz(): zlim_[0];
			zlim_[1]= iv.getz()> zlim_[1]? iv.getz(): zlim_[1];
		}
	}
		//Step 1 finished.
		
		// Count the number of face for each sub block
	int faceCount[8]={0,0,0,0,0,0,0,0};
	Real coordMid[3]={(xlim_[0]+xlim_[1])*0.5,(ylim_[0]+ylim_[1])*0.5,(zlim_[0]+zlim_[1])*0.5};
		//Step 2
	for(int i=0;i<nFace;i++){
		bool isIn=false;
		isIn=CheckInsideBox(facePtr[i],xlim_[0],coordMid[0],ylim_[0],coordMid[1],zlim_[0],coordMid[2]);
				
			
	}
		
}

	//This function check if the triangle should be included inside this box
	bool CheckInsideBox(const tri_face* fcPtr, const Real xmin,const Real xmax, const Real ymin,const Real ymax, const Real zmin,const Real zmax)
{
				//if any of the node is inside this box, return true!
		
	for(int i=0;i<3;i++){
		vector v=fcPtr->getNode(i)->getVector();
		if( isInsideBox( &v,xmin, xmax,ymin,ymax,zmin,zmax)){
			return true;
		}
	}
		
		//Then we check if the bounding box of the 
		
		//Form the box of triangle, 
		
	double triboxX[2],triboxY[2],triboxZ[2];
	triboxX[0]=fcPtr->getNode(0)->getx();
	triboxX[1]=fcPtr->getNode(0)->getx();
	triboxY[0]=fcPtr->getNode(0)->gety();
	triboxY[1]=fcPtr->getNode(0)->gety();
	triboxZ[0]=fcPtr->getNode(0)->getz();
	triboxZ[1]=fcPtr->getNode(0)->getz();
	for(int i=1;i<3;i++)
	{
		triboxX[0]=fcPtr->getNode(0)->getx() < triboxX[0]?fcPtr->getNode(0)->getx(): triboxX[0];
		triboxX[1]=fcPtr->getNode(0)->getx() > triboxX[1]?fcPtr->getNode(0)->getx(): triboxX[1];
		triboxY[0]=fcPtr->getNode(0)->gety() < triboxY[0]?fcPtr->getNode(0)->gety(): triboxY[0];
		triboxY[1]=fcPtr->getNode(0)->gety() > triboxY[1]?fcPtr->getNode(0)->gety(): triboxY[1];
		triboxZ[0]=fcPtr->getNode(0)->getz() < triboxZ[0]?fcPtr->getNode(0)->getz(): triboxZ[0];
		triboxZ[1]=fcPtr->getNode(0)->getz() > triboxZ[1]?fcPtr->getNode(0)->getz(): triboxZ[1];			
	}
	vector vv[8];
	vv[0].setvtr(triboxX[0],triboxY[0],triboxZ[0]);
	vv[1].setvtr(triboxX[0],triboxY[0],triboxZ[1]);
	vv[2].setvtr(triboxX[0],triboxY[1],triboxZ[0]);
	vv[3].setvtr(triboxX[0],triboxY[1],triboxZ[1]);
	vv[4].setvtr(triboxX[1],triboxY[0],triboxZ[0]);
	vv[5].setvtr(triboxX[1],triboxY[0],triboxZ[1]);
	vv[6].setvtr(triboxX[1],triboxY[1],triboxZ[0]);
	vv[7].setvtr(triboxX[1],triboxY[1],triboxZ[1]);
	for(int i=0;i<8;i++)
	{
		if(isInsideBox(&(vv[i]),xmin, xmax,ymin,ymax,zmin,zmax)){
			return true;
		}
	}
		
	vv[0].setvtr(xmin,ymin,zmin);
	vv[1].setvtr(xmin,ymin,zmax);
	vv[2].setvtr(xmin,ymax,zmin);
	vv[3].setvtr(xmin,ymax,zmax);
	vv[4].setvtr(xmax,ymin,zmin);
	vv[5].setvtr(xmax,ymin,zmax);
	vv[6].setvtr(xmax,ymax,zmin);
	vv[7].setvtr(xmax,ymax,zmax);
	for(int i=0;i<8;i++)
	{
		if(isInsideBox(&(vv[i]),triboxX[0], triboxX[1],triboxY[0],triboxY[1],triboxZ[0],triboxZ[1])){
			return true;
		}
	}
	return false;
}
	bool BoxTri::isInsideBox(const vector* v)const
{
	if(v->getx() < xlim_[1]+ TOLERANCE &&  v->getx() > xlim_[0]-TOLERANCE &&
		  v->gety() < ylim_[1]+TOLERANCE &&v->gety() > ylim_[0]-TOLERANCE &&
		  v->getz() < zlim_[1]+TOLERANCE &&v->getz() > zlim_[0]-TOLERANCE 
	  )
		return true;
	else
		return false;
}
	bool isInsideBox(const vector* v,const Real xmin, const Real xmax, const Real ymin, const Real ymax, const Real zmin, const Real zmax)
{
	if(v->getx() < xmax+ TOLERANCE &&  v->getx() > xmin-TOLERANCE &&
		  v->gety() < ymax+TOLERANCE &&v->gety() > ymin-TOLERANCE &&
		  v->getz() < zmax+TOLERANCE &&v->getz() > zmin-TOLERANCE 
	  )
		return true;
	else
		return false;
}