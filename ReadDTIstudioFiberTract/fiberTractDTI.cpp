// <author>Eric Chen</author>
// <email>chenpingjun1990@outlook.com</email>
// <date>2014-07-02</date>

#include "afx.h"
#include "FiberStructure.h"

struct 
{
	char sFiberFileTag[8]; // file tag = FiberDat
	int nFiberNr; // total number of fibers
	int nFiberLenMax; // max-length of fibers
	float fFiberLenMean; // mean-length of fibers
	int nImgWidth; // image dimension
	int nImgHeight;
	int nImgSlices;
	float fPixelSizeWidth; // voxel size
	float fPixelSizeHeight;
	float fSliceThickness;
	unsigned char enumSliceOrientation; // slice orientation
	unsigned char enumSliceSequencing; // slice sequencing
	char sVersion[8]; // version number
} stFiberFileHeader; //


int main(int argc, char* argv[])
{
	// open MRIstudio saved fiber save
	CFile fileIn;
	if (!fileIn.Open(_T("08SelectedFiber.dat"), CFile::modeRead)) 
	{
		printf("File open error:\n"); 
		return FALSE; 
	}

	// check reading fiber file header is ok
	if (fileIn.Read(&stFiberFileHeader, sizeof(stFiberFileHeader)) < sizeof(stFiberFileHeader)) 
	{
		printf("In File read error\n");
		fileIn.Close();
		return FALSE;
	} 
	
	// test this is Fiber data or not using the fiber file tag
	// the tag must be "FiberDat"
	if (strncmp(stFiberFileHeader.sFiberFileTag, "FiberDat", 8) != 0) 
	{ 
		printf("Not a proper fiber-data file!");
		fileIn.Close();
		return FALSE;
	}

	// create an file to save the fiber information
	FILE *fileOut;
	fileOut = fopen("08FiberResult.txt","w"); 

	// move file pointer 128, where fiber-data starts;
	fileIn.Seek(128,CFile::begin);

	// save the total fiber number 
	int fiberNumber = stFiberFileHeader.nFiberNr;
	fprintf(fileOut, "Fiber Numbers: %d\n", fiberNumber);


	FIBER f1;                   // used for saving a single fiber
	RGB_TRIPLE rgbT;            // used for saving color information 
	for (int i=0; i<stFiberFileHeader.nFiberNr; i++) 
	{
		fprintf(fileOut, "Fiber:%6d\t", i+1);
		fileIn.Read(&(f1.nLength), sizeof(int));      // read length
		fileIn.Read(&(f1.nSelStatus), sizeof(BYTE));  // read sel-status
		fileIn.Read(&rgbT, sizeof(RGB_TRIPLE));       // read color
		fileIn.Read(&(f1.nSelBeginIdx), sizeof(int)); // read fiber-sel-start
		fileIn.Read(&(f1.nSelEndIdx), sizeof(int));   // read fiber-sel-end

		// save the number of points of a particular fiber tract
		fprintf(fileOut, "Length:%4d\n", f1.nLength); 

		// read fiber-chain data
		f1.pxyzChain = new XYZ_TRIPLE[f1.nLength];
		fileIn.Read(f1.pxyzChain, sizeof(XYZ_TRIPLE)*f1.nLength);

		for (int i = 0; i < f1.nLength; i++)
		{
			fprintf(fileOut, "%-10.2f %-10.2f %-10.2f\n",
				f1.pxyzChain[i].x, f1.pxyzChain[i].y, f1.pxyzChain[i].z);
		}
		fprintf(fileOut, "\n");
		delete []f1.pxyzChain;
	}

	fileIn.Close();
	fclose(fileOut);
//	fileOut.close();

	return 0;
}
