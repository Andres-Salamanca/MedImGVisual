#include "FileReader.hpp"
#include <utility>
#include <vtkAlgorithm.h>
#include <vtkMetaImageReader.h>
#include <vtkSmartPointer.h>


namespace MeIm {

class MHAReader : public FileReader {
public:
    std::pair<vtkSmartPointer<vtkImageData>, vtkSmartPointer<vtkAlgorithm> > ReadData(const std::string& filePath) override {
        vtkNew<vtkMetaImageReader> reader;
        reader->SetFileName(filePath.c_str());
        reader->Update();
        vtkSmartPointer<vtkAlgorithm> readers = reader;
        return std::make_pair(reader->GetOutput(), readers);

    }
};

}
