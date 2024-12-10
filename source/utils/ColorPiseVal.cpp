#include "ColorPiseVal.h"
#include <vector>


inilizeProperties::inilizeProperties(){
  VolumePrope pointMuscle1;
  pointMuscle1.value = -3024;
  pointMuscle1.colorOpt = {  0, 0, 0, 0.5, 0.0};
  pointMuscle1.opaOpt = {0, 0.5, 0.0};
  
  VolumePrope pointMuscle2;
  pointMuscle2.value= -155;
  pointMuscle2.colorOpt = {.55, .25, .15, 0.5, .92};
  pointMuscle2.opaOpt = { 0, 0.5, 0.92};

  VolumePrope pointMuscle3;
  pointMuscle3.value= 217;
  pointMuscle3.colorOpt = {.88, .60, .29, 0.33, 0.45};
  pointMuscle3.opaOpt = { .68, 0.33, 0.45};

  VolumePrope pointMuscle4;
  pointMuscle4.value= 420;
  pointMuscle4.colorOpt = {1, .94, .95, 0.5, 0.0};
  pointMuscle4.opaOpt = { .83, 0.5, 0.0};

  VolumePrope pointMuscle5;
  pointMuscle5.value= 3071;
  pointMuscle5.colorOpt = { .83, .66, 1, 0.5, 0.0};
  pointMuscle5.opaOpt = {.80, 0.5, 0.0};

  Muscle.push_back(pointMuscle1);
  Muscle.push_back(pointMuscle2);
  Muscle.push_back(pointMuscle3);
  Muscle.push_back(pointMuscle4);
  Muscle.push_back(pointMuscle5);

  VolumePrope pointBone1;
  pointBone1.value = -3024;
  pointBone1.colorOpt = {  0, 0, 0, 0.5, 0.0};
  pointBone1.opaOpt = {0, 0.5, 0.0};

  VolumePrope pointBone2;
  pointBone2.value = -16;
  pointBone2.colorOpt = {0.73, 0.25, 0.30, 0.49, .61};
  pointBone2.opaOpt = {0, .49, .61};

  VolumePrope pointBone3;
  pointBone3.value = 641;
  pointBone3.colorOpt = { .90, .82, .56, .5, 0.0};
  pointBone3.opaOpt = { .72, .5, 0.0};

  VolumePrope pointBone4;
  pointBone4.value = 3071;
  pointBone4.colorOpt = {1, 1, 1, .5, 0.0};
  pointBone4.opaOpt = {.71, 0.5, 0.0};

  Bone.push_back(pointBone1);
  Bone.push_back(pointBone2);
  Bone.push_back(pointBone3);
  Bone.push_back(pointBone4);

  VolumePrope pointSkin1;
  pointSkin1.value = -3024;
  pointSkin1.colorOpt = {0, 0, 0, 0.5, 0.0};
  pointSkin1.opaOpt = {0, 0.5, 0.0};

  VolumePrope pointSkin2;
  pointSkin2.value = -1000;
  pointSkin2.colorOpt = {.62, .36, .18, 0.5, 0.0};
  pointSkin2.opaOpt = { 0, 0.5, 0.0};

  VolumePrope pointSkin3;
  pointSkin3.value = -500;
  pointSkin3.colorOpt = {.88, .60, .29, 0.33, 0.45};
  pointSkin3.opaOpt = {1.0, 0.33, 0.45};

  VolumePrope pointSkin4;
  pointSkin4.value = 3071;
  pointSkin4.colorOpt = {.83, .66, 1, 0.5, 0.0};
  pointSkin4.opaOpt = {1.0, 0.5, 0.0};

  Skin.push_back(pointSkin1);
  Skin.push_back(pointSkin2);
  Skin.push_back(pointSkin3);
  Skin.push_back(pointSkin4);

  VolumePrope pointLung1;
  pointLung1.value = -1000;
  pointLung1.colorOpt = { 0, 0, 0, 0.0, 0.0};
  pointLung1.opaOpt = {0.0};

  VolumePrope pointLung2;
  pointLung2.value = 0;
  pointLung2.colorOpt = { 0, 0, 0, 0.0, 0.0};
  pointLung2.opaOpt = {0.0};

  VolumePrope pointLung3;
  pointLung3.value = 2;
  pointLung3.colorOpt = { 0.8, 0.7, 0.5, 0.1, 0.6};
  pointLung3.opaOpt = {0.1};

  VolumePrope pointLung4;
  pointLung4.value = 5;
  pointLung4.colorOpt = {1.0, 0.8, 0.6, 0.2, 0.8};
  pointLung4.opaOpt = {0.3};


  VolumePrope pointLung5;
  pointLung5.value = 300;
  pointLung5.colorOpt = {1.0, 1.0, 1.0, 0.7, 0.8};
  pointLung5.opaOpt = {1.0};

  Lung.push_back(pointLung1);
  Lung.push_back(pointLung2);
  Lung.push_back(pointLung3);
  Lung.push_back(pointLung4);
  Lung.push_back(pointLung5);
}

