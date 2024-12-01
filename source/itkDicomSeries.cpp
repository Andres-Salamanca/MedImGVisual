#include "itkImageSeriesReader.h"
#include "itkGDCMImageIO.h"
#include "itkImageToVTKImageFilter.h"

#include "vtkSmartPointer.h"
#include "vtkImageViewer2.h"
#include "vtkRenderWindowInteractor.h"
#include "itkImageSeriesReader.h"
#include "itkGDCMSeriesFileNames.h"
#include <vtkRenderer.h>
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <DICOM folder>" << std::endl;
        return EXIT_FAILURE;
    }
  std::cout << "hola \n";
    // Define ITK types
    constexpr unsigned int Dimension = 3;
    using PixelType = signed short; // Adjust as per your DICOM data
    using ImageType = itk::Image<PixelType, Dimension>;

    // Read DICOM series
    auto reader = itk::ImageSeriesReader<ImageType>::New();
    auto dicomIO = itk::GDCMImageIO::New();
    reader->SetImageIO(dicomIO);

    // Set DICOM directory
    using NamesGeneratorType = itk::GDCMSeriesFileNames;
    auto nameGenerator = NamesGeneratorType::New();
    nameGenerator->SetDirectory(argv[1]);
    reader->SetFileNames(nameGenerator->GetInputFileNames());

    try {
        reader->Update();
    } catch (itk::ExceptionObject &error) {
        std::cerr << "Error: " << error << std::endl;
        return EXIT_FAILURE;
    }

    // Convert ITK image to VTK image
    using ConnectorType = itk::ImageToVTKImageFilter<ImageType>;
    auto connector = ConnectorType::New();
    connector->SetInput(reader->GetOutput());

    try {
        connector->Update();
    } catch (itk::ExceptionObject &error) {
        std::cerr << "Error: " << error << std::endl;
        return EXIT_FAILURE;
    }
  vtkImageData * myvtkImageData = connector->GetOutput();
  myvtkImageData->Print(std::cout);
    // Visualize using VTK
    auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
    viewer->SetInputData(connector->GetOutput());

    auto renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    viewer->SetupInteractor(renderWindowInteractor);

    viewer->Render();
    viewer->GetRenderer()->ResetCamera();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}

