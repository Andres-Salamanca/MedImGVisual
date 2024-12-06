#ifndef ENUMS_H
#define ENUMS_H

namespace MeIm {

  enum class FileType{
    DICOM,
    VTI,
    MHA
  };

  enum class BlendType{
    MIP,
    CT_Skin,
    CT_Bone,
    CT_Muscle,
    RGB_Composite,
    CT_Lung
  };

}

#endif // ENUMS_H

