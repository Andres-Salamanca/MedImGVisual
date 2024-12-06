#include "FileReader.hpp"
#include <vtkDICOMImageReader.h>



namespace MeIm {

class DICOMReader : public FileReader {
public:
    std::pair<vtkSmartPointer<vtkImageData>, vtkSmartPointer<vtkAlgorithm> > ReadData(const std::string& dirPath) override {

        vtkNew<vtkDICOMImageReader> reader;
        reader->SetDirectoryName(dirPath.c_str());
        reader->Update();
        vtkSmartPointer<vtkAlgorithm> readers = reader;
        return std::make_pair(reader->GetOutput(), readers);

    }
};


}
