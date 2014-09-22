#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkAnalyzeImageIO.h"
#include "itkImageIOBase.h"

#include "itkConnectedThresholdImageFilter.h"
#include "itkImageRegionIterator.h"
#include "itkBinaryThinningImageFilter3D.h"
#include "itkRescaleIntensityImageFilter.h"

#include <iostream>
#include <stdlib.h>   // for atoi()
using namespace std;

int main(int argc, char* argv[])
{
  // Verify the number of parameters in the command line
  if( argc <= 2 )
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " inputImageFile outputImageFile" << std::endl;
    return EXIT_FAILURE;
  }

  char* infilename  = argv[1];
  char* outfilename = argv[2];

  const   unsigned int Dimension = 3;
  typedef unsigned char PixelType;   
  typedef itk::Image< PixelType, Dimension > ImageType;

  // Read image
  typedef itk::ImageFileReader< ImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( infilename );
  try
  {
    reader->Update();
  }
  catch (itk::ExceptionObject &ex)
  {
    std::cout << ex << std::endl;
    return EXIT_FAILURE;
  }
  cout << infilename << " sucessfully read." << endl;

  // Define the thinning filter
  typedef itk::BinaryThinningImageFilter3D< ImageType, ImageType > ThinningFilterType;
  ThinningFilterType::Pointer thinningFilter = ThinningFilterType::New();
  thinningFilter->SetInput( reader->GetOutput() );
  thinningFilter->Update();

  	// Rescale the image so that it can be seen (the output is 0 and 1, we want 0 and 255)
	typedef itk::RescaleIntensityImageFilter< ImageType, ImageType > RescaleType;
	RescaleType::Pointer rescaler = RescaleType::New();
	rescaler->SetInput(thinningFilter->GetOutput() );
	rescaler->SetOutputMinimum(0);
	rescaler->SetOutputMaximum(255);
	rescaler->Update();


  // output to file
  typedef itk::ImageFileWriter< ImageType > WriterType;
  typedef itk::AnalyzeImageIO AnaIOType;
  AnaIOType::Pointer anaIO = AnaIOType::New();
  anaIO->SetPixelType(itk::ImageIOBase::SCALAR);
  
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( rescaler->GetOutput() );
  writer->SetFileName( outfilename );
  writer->SetImageIO(anaIO);

  try
  {
    writer->Update();
  }
  catch (itk::ExceptionObject &ex)
  {
    std::cout << ex << std::endl;
    return EXIT_FAILURE;
  }
  cout << outfilename << " sucessfully written." << endl;

  cout << "Program terminated normally." << endl;
  return EXIT_SUCCESS;
}


