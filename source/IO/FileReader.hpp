#ifndef FILE_READER_H
#define FILE_READER_H
#include <string>
#include <utility>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkAlgorithm.h>
namespace MeIm {

class FileReader{
  public:
    virtual std::pair<vtkSmartPointer<vtkImageData>, vtkSmartPointer<vtkAlgorithm> > ReadData(const std::string &FilePath)=0;
    virtual ~FileReader()=default;
};

}



#endif // !DEBUG
