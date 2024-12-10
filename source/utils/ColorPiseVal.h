#ifndef COLORPISEVAL_H
#define COLORPISEVAL_H

#include <vector>
struct colorValues{
  double r=0;
  double g=0;
  double b=0;
  double midpoint=0;
  double sharp=0;
};

struct opacityValues{
  
  double a = 1;
  double midpoint =0;
  double sharp=0;

};

struct VolumePrope{
  int value; // hu value
  colorValues colorOpt;
  opacityValues opaOpt;
};

class inilizeProperties{
public:
  std::vector<VolumePrope>Bone;
  std::vector<VolumePrope>Skin;
  std::vector<VolumePrope>Muscle;
  std::vector<VolumePrope>Lung;
  inilizeProperties();
};



#endif // COLORPISEVAL_H

