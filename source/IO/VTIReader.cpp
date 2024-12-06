#include "FileReader.hpp"
#include <vtkXMLImageDataReader.h>
namespace MeIm {
class VTIReader : public FileReader {
public:
    std::pair<vtkSmartPointer<vtkImageData>, vtkSmartPointer<vtkAlgorithm> > ReadData(const std::string& filePath) override {
        vtkNew<vtkXMLImageDataReader> reader;
        reader->SetFileName(filePath.c_str());
        reader->Update();
        vtkSmartPointer<vtkAlgorithm> readers = reader;
        return std::make_pair(reader->GetOutput(), readers);
    }
};
}
