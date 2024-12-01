#include <iostream>
#include <itkMacro.h>
#include <itkMetaDataDictionary.h>
#include <string>
#include <vector>
#include "itkImage.h"
#include "itkImageSeriesReader.h"
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkImageFileWriter.h"


int main (int argc, char *argv[]) {
  /*if(argc < 2){
    std::cerr << "Usage: " << argv[0] << " DicomDirectory " << std::endl;
    return EXIT_FAILURE;
  }

  using PixelType = signed short;
  constexpr unsigned int Dimension =3;

  using ImageType = itk::Image<PixelType,Dimension>;
  
  using ReaderType = itk::ImageSeriesReader<ImageType>;

  auto reader = ReaderType::New();

  using ImageIOType = itk::GDCMImageIO;

  auto dicomIO = ImageIOType::New();

  reader->SetImageIO(dicomIO);

  using NamesGeneratorType = itk::GDCMSeriesFileNames;

  auto nameGenerator = NamesGeneratorType::New();

  nameGenerator->SetInputDirectory(argv[1]);

  using FileNamesContainer = std::vector<std::string>;
  FileNamesContainer fileNames = nameGenerator->GetInputFileNames();

  reader->SetFileNames(fileNames);

  // We trigger the reader by invoking the Update() method. This
  // invocation should normally be done inside a try/catch block given
  // that it may eventually throw exceptions.
  try
  {
    reader->Update();
  }
  catch (const itk::ExceptionObject & ex)
  {
    std::cout << ex << std::endl;
    return EXIT_FAILURE;
  }

  using DirectoryType = itk::MetaDataDictionary;

  const DirectoryType & dictionary = dicomIO->GetMetaDataDictionary();

  using MetaDataStringType = itk::MetaDataObject<std::string>;

  auto itr = dictionary.Begin();
  auto end = dictionary.End();

 while (itr != end)
  {
    itk::MetaDataObjectBase::Pointer entry = itr->second;

    MetaDataStringType::Pointer entryvalue = dynamic_cast<MetaDataStringType *>(entry.GetPointer());

    if (entryvalue)
    {
      std::string tagkey = itr->first;
      std::string tagvalue = entryvalue->GetMetaDataObjectValue();
      std::cout << tagkey << " = " << tagvalue << std::endl;
    }

    ++itr;
  }*/

  //###########

  /*if (argc < 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " [DicomDirectory  [outputFileName  [seriesName]]]";
    std::cerr << "\nIf DicomDirectory is not specified, current directory is used\n";
  }
  std::string dirName = "."; // current directory by default
  if (argc > 1)
  {
    dirName = argv[1];
  }

  using PixelType = signed short;
  constexpr unsigned int Dimension = 3;
  using ImageType = itk::Image<PixelType, Dimension>;

  using NamesGeneratorType = itk::GDCMSeriesFileNames;
  auto nameGenerator = NamesGeneratorType::New();


  nameGenerator->SetUseSeriesDetails(true);
  nameGenerator->AddSeriesRestriction("0008|0021");
  nameGenerator->SetGlobalWarningDisplay(false);
  nameGenerator->SetDirectory(dirName);

  try {

    using SeriesIdContainer = std::vector<std::string>;
    const SeriesIdContainer & seriesUID = nameGenerator->GetSeriesUIDs();
    auto seriesItr = seriesUID.begin();
    auto seriesEnd = seriesUID.end();

    if(seriesItr != seriesEnd){
      std::cout << "The directory: ";
      std::cout << dirName << std::endl;
      std::cout << "Contains the following DICOM Series: ";
      std::cout << std::endl;
    }else{
      std::cout << "No DICOMs in: " << dirName << std::endl;
      return EXIT_SUCCESS;
    }

    while (seriesItr != seriesEnd)
    {
      std::cout << seriesItr->c_str() << std::endl;
      ++seriesItr;
    }

    seriesItr = seriesUID.begin();
    while(seriesItr != seriesUID.end()){
      std::string seriesIdentifier;
      if (argc > 3) // If seriesIdentifier given convert only that
      {
        seriesIdentifier = argv[3];
        seriesItr = seriesUID.end();
      }
      else // otherwise convert everything
      {
        seriesIdentifier = seriesItr->c_str();
        seriesItr++;
      }
      std::cout << "\nReading: ";
      std::cout << seriesIdentifier << std::endl;

      using FileNamesContainer = std::vector<std::string>;
      FileNamesContainer fileNames = nameGenerator->GetFileNames(seriesIdentifier);
      using ReaderType = itk::ImageSeriesReader<ImageType>;
      auto reader = ReaderType::New();
      using ImageIOType = itk::GDCMImageIO;
      auto dicomIO = ImageIOType::New();
      reader->SetImageIO(dicomIO);
      reader->SetFileNames(fileNames);
      reader->ForceOrthogonalDirectionOff();

      std::string outFileName;
      if (argc > 2)
      {
        outFileName = argv[2];
      }
      else
      {
        outFileName = dirName + std::string("/") + seriesIdentifier + ".nrrd";
      }
      std::cout << "Writing: " << outFileName << std::endl;
      try
      {
        itk::WriteImage(reader->GetOutput(), outFileName, true); // compression
      }
      catch (const itk::ExceptionObject & ex)
      {
        std::cout << ex << std::endl;
        continue;
      }

    }
  
  } catch (const itk::ExceptionObject & ex) {
    std::cout << ex << std::endl;
    return EXIT_FAILURE;
  }*/


  //########
  if (argc != 3)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << "<InputFileName> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(argv[1]);

  try
  {
    itk::WriteImage(input, argv[2]);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }
  return 0;
}
