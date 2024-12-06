

#include <iostream>
#include <string.h>
#include <string>
#include "../utils/Enums.hpp"
namespace MeIm {

class ArgParser{
  public:

  struct Options{
    std::string fileName;
    double opacityWindow = 4096;
    double opacityLevel = 2048;
    BlendType blendType = BlendType::MIP;
    int clip = 0;
    double reductionFactor = 1.0;
    double frameRate = 10.0;
    FileType fileType;
  };

  Options Parse(int argc, char* argv[]){

    Options opts;

    for(int i=1 ;i<argc;i++){

      if(!strcmp(argv[i], "-DICOM")){
        opts.fileName = argv[++i];
        opts.fileType = FileType::DICOM;

      }
      else if (!strcmp(argv[i], "-VTI")) {
        opts.fileName = argv[++i];
        opts.fileType = FileType::VTI;
      }
      else if (!strcmp(argv[i], "-MHA")) {
        opts.fileName = argv[++i];
        opts.fileType = FileType::MHA;
      }
      else if (!strcmp(argv[i], "-CT_Muscle")){
        opts.blendType = BlendType::CT_Muscle;

      }
      else if (!strcmp(argv[i], "-CT_Bone")){

        opts.blendType = BlendType::CT_Bone;
      }
      else if (!strcmp(argv[i], "-CT_Skin")){
        opts.blendType = BlendType::CT_Skin;
      }
      else if (!strcmp(argv[i], "-CT_Lung")) {
        opts.blendType = BlendType::CT_Lung;
      }
      else if (!strcmp(argv[i], "-FrameRate")) {
        opts.frameRate = atof(argv[++i]);
        if (opts.frameRate < 0.01 || opts.frameRate > 60.0)
        {
          std::cout << "Invalid frame rate - use a number between 0.01 and 60.0"
                    << std::endl;
          std::cout << "Using default frame rate of 10 frames per second."
                    << std::endl;
          opts.frameRate = 10.0;
        }
      }
      else if(!strcmp(argv[i], "-ReductionFactor")){

      opts.reductionFactor = atof(argv[++i]);
      if (opts.reductionFactor <= 0.0 || opts.reductionFactor >= 1.0)
      {
        std::cout << "Invalid reduction factor - use a number between 0 and 1 "
                     "(exclusive)"
                  << std::endl;
        std::cout << "Using the default of no reduction." << std::endl;
        opts.reductionFactor = 1.0;
      }
      }
      else {
        std::cout << "Unrecognized option: " << argv[i] << std::endl;
        std::cout << std::endl;
        exit(EXIT_FAILURE);
      }

    }

    return opts;

  }

};

}

