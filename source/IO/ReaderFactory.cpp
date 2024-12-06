#include "../utils/Enums.hpp"
#include <memory>
#include <vtkSmartPointer.h>
#include "DICOMReader.cpp"
#include "VTIReader.cpp"
#include "MHAReader.cpp"
namespace MeIm {

class ReaderFactory{
public:


    static std::unique_ptr<FileReader> CreateReader(FileType ft) {
        switch (ft) {
      case FileType::DICOM:
            return std::make_unique<DICOMReader>();
      case FileType::VTI:
            return std::make_unique<VTIReader>();

      case FileType::MHA:
            return std::make_unique<MHAReader>();
        default:
            throw std::invalid_argument("Unsupported file type!");
        }
    }


};

}
