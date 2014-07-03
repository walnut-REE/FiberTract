// maximum number of ROI files
#define		MAX_ROI_FILE_Nr		16

#define		BYTE	unsigned char
#define		WORD	unsigned short
#define		DWORD	unsigned int


// vector data type
typedef struct tagXYZ_TRIPLE
{
	float x, y, z;
}XYZ_TRIPLE;


// R-G-B data type
typedef struct tagRGB_TRIPLE
{
	BYTE r, g, b;
}RGB_TRIPLE;


//==================================================================
// Data structure
//==================================================================
// fiber data
typedef struct tagFIBER
{
	int			nLength;			// fiber length
	XYZ_TRIPLE*	pxyzChain;			// pointer of fiber data chain
	BYTE		nSelStatus;			// fiber has been selected (>= 1) or deselected (== 0).
	int			nSelBeginIdx;		// start index of the selected fiber-segment
	int			nSelEndIdx;			// end index of the selected fiber-segment
	int			nSelCnt;			// number of being selected by ROI
	XYZ_TRIPLE	xyzPtSeed;			// seed point
	XYZ_TRIPLE	xyzPtROI;			// ROI point where the fiber been selected
}FIBER;


// parameter
typedef struct tagFACT_Para
{
	// image dimension
	int		nImgWidth;			// image dimension
	int		nImgHeight;
	int		nImgSlices;

	// FOV or pixel size
	float	fFovWidth;			// FOV
	float	fFovHeight;
	float	fPixelSizeWidth;	// Pixel size
	float	fPixelSizeHeight;
	float	fSliceThickness;

	int		nSliceOrientation;	// slice orientation
	int		nSliceSequencing;	// slice sequencing

	// input file name
	char*	szImgVecFile;		// principal vector image 
	char*	szImgAniFile;		// anisotropy image 

	bool	bSwapBytes;			
	bool	bFlipVecX, bFlipVecY, bFlipVecZ;

	// tracking threshold values
	float	fStartFA;
	float	fStopFA;
	float	fTurnDeg;
	int		nFiberLenMin;					// minimum fiber length

	// fiber selection by ROI
	char*	szBinRoiFile[MAX_ROI_FILE_Nr];				// binary ROI files
	int		nBinRoiOp[MAX_ROI_FILE_Nr];					// binary operation

	// Optional Output files name
	char*	szFiberAllFile;
	char*	szFiberSelFile;

	char*	szFiberAllTxtFile;
	char*	szFiberSelTxtFile;

	// Optional Fiber Color
	bool	bFiberColorAll;
	bool	bFiberColorSel;
	RGB_TRIPLE	rgbFiberColorAll;
	RGB_TRIPLE	rgbFiberColorSel;
	int		nNotUsed;
}FACT_PARA;


// DTI maps
typedef struct tagFACT_Map
{
	FACT_PARA*	pstFactPara;				// image parameters

	float*		pfAniImg;					// original FA map
	XYZ_TRIPLE*	pxyzVecImg;					// original Vector image

	FIBER*		pstFiberAry;				// fiber data array
	int**		pnFiberIdxAry;				// fiber data index of each voxel 
	int*		pnFiberCntAry;				// number of fibers through each voxel

	// fiber data statistics
	long		lFiberNrTotal;				// number of fibers in the fiber data array (array size)
	long		lFiberLenMax;				// maximum length of all fibers
	float		fFiberLenMean;				// mean length of all fibers
	float		fFiberLenStdDev;			// standard derivation of fiber length
}FACT_MAP;

