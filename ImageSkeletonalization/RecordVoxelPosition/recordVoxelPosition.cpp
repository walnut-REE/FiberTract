#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkAnalyzeImageIO.h>
#include <itkImageIOBase.h>
#include <itkImageFileWriter.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: ";
		cerr << argv[0] << "inputImage" << endl;
		return 0;
	}

	const int DimSize = 3;
	typedef unsigned char PixelType;
	typedef itk::Image<PixelType, DimSize> ImageType;
	typedef itk::ImageFileReader<ImageType> ReaderType;

	// read in the image
	ReaderType::Pointer inputReader = ReaderType::New();
	inputReader->SetFileName(argv[1]);
	inputReader->Update();
	ImageType::Pointer inputImage = inputReader->GetOutput();
	itk::ImageRegionConstIterator<ImageType> inputIt(inputImage,
		inputImage->GetLargestPossibleRegion());
	inputIt.GoToBegin();

//	int GrayScale = 256;
//	vector<int> pixelSta(GrayScale);

	string imageFileName = argv[1];
	int dotPos = imageFileName.find(".");
	string statisticsFileName = imageFileName.substr(0, dotPos) + "Pos.txt";
	ofstream fout(statisticsFileName);

	while (!inputIt.IsAtEnd())
	{
		PixelType inputPixel = inputIt.Get();
		if (255 == inputPixel)
		{
			ImageType::IndexType index = inputIt.GetIndex();
			fout << index[0] << "\t" << index[1] << "\t" << index[2] << "\n";
//			pixelSta[inputPixel]++;
		}
		inputIt++;
	}



	//// write the pixel statistics into the txt file
	//for (int i = 1; i < pixelSta.size(); i++)
	//{
	//	fout << i << ":" << pixelSta[i] << std::endl;
	//}

//	pixelSta.clear();
	
	fout.close();
	return EXIT_SUCCESS;
}