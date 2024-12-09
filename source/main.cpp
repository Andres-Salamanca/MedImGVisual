#include "IO/ArgParser.cpp"
#include "IO/ReaderFactory.cpp"
#include "utils/Enums.hpp"
#include <iostream>
#include <qapplication.h>
#include <vtkCamera.h>
#include <vtkColorTransferFunction.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkImageData.h>
#include <vtkImageResample.h>
#include <vtkInteractorObserver.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPiecewiseFunction.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkImagePlaneWidget.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCellPicker.h>
#include <vtkInteractorStyleImage.h>
#include <QtWidgets/QApplication>
#include "GUI/mainwindow.h"
#include <QVTKOpenGLNativeWidget.h>
int main (int argc, char *argv[]) {


  
  QApplication app(argc,argv);
  MainWindow mainwindow;
  mainwindow.show();
  return app.exec();

  // Create the renderer, render window and interactor
  /*vtkNew<vtkNamedColors> colors;
  vtkNew<vtkRenderer> renderer;

  // renderer for views
  vtkNew<vtkRenderer> axialRenderer;
  vtkNew<vtkRenderer> coronalRenderer;
  vtkNew<vtkRenderer> sagittalRenderer;

  vtkNew<vtkRenderWindow> renWin;




  
  renWin->AddRenderer(axialRenderer);
  renWin->AddRenderer(coronalRenderer);
  renWin->AddRenderer(sagittalRenderer);
  renWin->AddRenderer(renderer);
  // Connect it all. Note that funny arithematic on the
  // SetDesiredUpdateRate - the vtkRenderWindow divides it
  // allocated time across all renderers, and the renderer
  // divides it time across all props. If clip is
  // true then there are two props
  vtkNew<vtkRenderWindowInteractor> iren;


  iren->SetRenderWindow(renWin);
  iren->SetDesiredUpdateRate(options.frameRate / (1 + options.clip));

  iren->GetInteractorStyle()->SetDefaultRenderer(renderer);
  
  // Verify that we actually have a volume
  int dim[3];
  input->GetDimensions(dim);

  if (dim[0] < 2 || dim[1] < 2 || dim[2] < 2)
  {
    std::cout << "Error loading data!" << std::endl;
    exit(EXIT_FAILURE);
  }

  vtkNew<vtkImageResample> resample;
  if (options.reductionFactor < 1.0)
  {
    resample->SetInputConnection(reader->GetOutputPort());
    resample->SetAxisMagnificationFactor(0, options.reductionFactor);
    resample->SetAxisMagnificationFactor(1, options.reductionFactor);
    resample->SetAxisMagnificationFactor(2, options.reductionFactor);
  }

  // Create our volume and mapper
  vtkNew<vtkVolume> volume;
  vtkNew<vtkFixedPointVolumeRayCastMapper> mapper;

  if (options.reductionFactor < 1.0)
  {
    mapper->SetInputConnection(resample->GetOutputPort());
  }
  else
  {
    mapper->SetInputConnection(reader->GetOutputPort());
  }

  // Set the sample distance on the ray to be 1/2 the average spacing
  double spacing[3];
  if (options.reductionFactor < 1.0)
  {
    resample->GetOutput()->GetSpacing(spacing);
  }
  else
  {
    input->GetSpacing(spacing);
  }


  //  mapper->SetSampleDistance( (spacing[0]+spacing[1]+spacing[2])/6.0 );
  //  mapper->SetMaximumImageSampleDistance(10.0);

  // Create our transfer function
  vtkNew<vtkColorTransferFunction> colorFun;
  vtkNew<vtkPiecewiseFunction> opacityFun;
  // Create the property and attach the transfer functions
  vtkNew<vtkVolumeProperty> property;
  property->SetIndependentComponents(true);
  property->SetColor(colorFun);
  property->SetScalarOpacity(opacityFun);
  property->SetInterpolationTypeToLinear();

  // connect up the volume to the property and the mapper
  volume->SetProperty(property);
  volume->SetMapper(mapper);

  // Depending on the blend type selected as a command line option,
  // adjust the transfer function
  switch (options.blendType)
  {
  // MIP
  // Create an opacity ramp from the window and level values.
  // Color is white. Blending is MIP.
    case  MeIm::BlendType::MIP: 
    colorFun->AddRGBSegment(0.0, 1.0, 1.0, 1.0, 255.0, 1.0, 1.0, 1.0);
    opacityFun->AddSegment(options.opacityLevel - 0.5 * options.opacityWindow, 0.0,
                           options.opacityLevel + 0.5 * options.opacityWindow, 1.0);
    mapper->SetBlendModeToMaximumIntensity();
    break;


  // CT_Skin
  // Use compositing and functions set to highlight skin in CT data
  // Not for use on RGB data
    case MeIm::BlendType::CT_Skin:
    colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
    colorFun->AddRGBPoint(-1000, .62, .36, .18, 0.5, 0.0);
    colorFun->AddRGBPoint(-500, .88, .60, .29, 0.33, 0.45);
    colorFun->AddRGBPoint(3071, .83, .66, 1, 0.5, 0.0);

    opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
    opacityFun->AddPoint(-1000, 0, 0.5, 0.0);
    opacityFun->AddPoint(-500, 1.0, 0.33, 0.45);
    opacityFun->AddPoint(3071, 1.0, 0.5, 0.0);

    mapper->SetBlendModeToComposite();
    property->ShadeOn();
    property->SetAmbient(0.1);
    property->SetDiffuse(0.9);
    property->SetSpecular(0.2);
    property->SetSpecularPower(10.0);
    property->SetScalarOpacityUnitDistance(0.8919);
    break;

  // CT_Bone
  // Use compositing and functions set to highlight bone in CT data
  // Not for use on RGB data
    case MeIm::BlendType::CT_Bone:
    colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
    colorFun->AddRGBPoint(-16, 0.73, 0.25, 0.30, 0.49, .61);
    colorFun->AddRGBPoint(641, .90, .82, .56, .5, 0.0);
    colorFun->AddRGBPoint(3071, 1, 1, 1, .5, 0.0);

    opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
    opacityFun->AddPoint(-16, 0, .49, .61);
    opacityFun->AddPoint(641, .72, .5, 0.0);
    opacityFun->AddPoint(3071, .71, 0.5, 0.0);

    mapper->SetBlendModeToComposite();
    property->ShadeOn();
    property->SetAmbient(0.1);
    property->SetDiffuse(0.9);
    property->SetSpecular(0.2);
    property->SetSpecularPower(10.0);
    property->SetScalarOpacityUnitDistance(0.8919);
    break;

  // CT_Muscle
  // Use compositing and functions set to highlight muscle in CT data
  // Not for use on RGB data
    case MeIm::BlendType::CT_Muscle:
    colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
    colorFun->AddRGBPoint(-155, .55, .25, .15, 0.5, .92);
    colorFun->AddRGBPoint(217, .88, .60, .29, 0.33, 0.45);
    colorFun->AddRGBPoint(420, 1, .94, .95, 0.5, 0.0);
    colorFun->AddRGBPoint(3071, .83, .66, 1, 0.5, 0.0);

    opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
    opacityFun->AddPoint(-155, 0, 0.5, 0.92);
    opacityFun->AddPoint(217, .68, 0.33, 0.45);
    opacityFun->AddPoint(420, .83, 0.5, 0.0);
    opacityFun->AddPoint(3071, .80, 0.5, 0.0);

    mapper->SetBlendModeToComposite();
    property->ShadeOn();
    property->SetAmbient(0.1);
    property->SetDiffuse(0.9);
    property->SetSpecular(0.2);
    property->SetSpecularPower(10.0);
    property->SetScalarOpacityUnitDistance(0.8919);
    break;

  // RGB_Composite
  // Use compositing and functions set to highlight red/green/blue regions
  // in RGB data. Not for use on single component data
    case MeIm::BlendType::RGB_Composite:
    opacityFun->AddPoint(0, 0.0);
    opacityFun->AddPoint(5.0, 0.0);
    opacityFun->AddPoint(30.0, 0.05);
    opacityFun->AddPoint(31.0, 0.0);
    opacityFun->AddPoint(90.0, 0.0);
    opacityFun->AddPoint(100.0, 0.3);
    opacityFun->AddPoint(110.0, 0.0);
    opacityFun->AddPoint(190.0, 0.0);
    opacityFun->AddPoint(200.0, 0.4);
    opacityFun->AddPoint(210.0, 0.0);
    opacityFun->AddPoint(245.0, 0.0);
    opacityFun->AddPoint(255.0, 0.5);

    mapper->SetBlendModeToComposite();
    property->ShadeOff();
    property->SetScalarOpacityUnitDistance(1.0);
    break;
  // CT_Lung
    case MeIm::BlendType::CT_Lung:
  colorFun->AddRGBPoint(-1000, 0, 0, 0, 0.0, 0.0); // Air (black)
  colorFun->AddRGBPoint(0, 0, 0, 0, 0.0, 0.0); // Air (black)
  colorFun->AddRGBPoint(2, 0.8, 0.7, 0.5, 0.1, 0.6); // Lungs (light brown or yellowish)
  colorFun->AddRGBPoint(5, 1.0, 0.8, 0.6, 0.2, 0.8); // Lungs (lighter brown)
  colorFun->AddRGBPoint(300, 1.0, 1.0, 1.0, 0.7, 0.8);  // Bone (white)

  opacityFun->AddPoint(-1000, 0.0); // Air (transparent)
  opacityFun->AddPoint(0, 0.0); // Air (transparent)
  opacityFun->AddPoint(2, 0.1);  // Lungs, semi-transparent
  opacityFun->AddPoint(5, 0.3);  // Lungs, slightly more opaque
  opacityFun->AddPoint(300, 1.0);   // Bone, fully opaque


    mapper->SetBlendModeToComposite();
    property->ShadeOn();
    property->SetAmbient(0.1);
    property->SetDiffuse(0.9);
    property->SetSpecular(0.2);
    property->SetSpecularPower(10.0);
    property->SetScalarOpacityUnitDistance(0.8919);

    break;
  default:
    vtkGenericWarningMacro("Unknown blend type.");
    break;
  }


   vtkNew<vtkImageViewer2> axialViewer;
  axialViewer->SetInputData(input);
  axialViewer->SetRenderWindow(renWin);
  axialViewer->SetRenderer(axialRenderer);
  axialViewer->SetSliceOrientationToXY();
  axialViewer->SetSlice(axialViewer->GetSliceMin()+1); // Set to middle slice

  vtkNew<vtkImageViewer2> coronalViewer;
  coronalViewer->SetInputData(input);
  coronalViewer->SetRenderWindow(renWin);
  coronalViewer->SetRenderer(coronalRenderer);
  coronalViewer->SetSliceOrientationToXZ();
  coronalViewer->SetSlice(axialViewer->GetSliceMin()+1); // Set to middle slice

  vtkNew<vtkImageViewer2> sagittalViewer;
  sagittalViewer->SetInputData(input);
  sagittalViewer->SetRenderWindow(renWin);
  sagittalViewer->SetRenderer(sagittalRenderer);
  sagittalViewer->SetSliceOrientationToYZ();
  sagittalViewer->SetSlice(axialViewer->GetSliceMin()+1); // Set to middle slice     //Set up viewports for the three renderers




  renderer->SetViewport(0.0, 0.0, 0.7, 1.0);  // Main renderer (full left)
  axialRenderer->SetViewport(0.7, 0.66, 1.0, 1.0);  // Axial view (top-right)
  coronalRenderer->SetViewport(0.7, 0.33, 1.0, 0.66); // Coronal view (middle-right)
  sagittalRenderer->SetViewport(0.7, 0.0, 1.0, 0.33); // Sagittal view (bottom-right)

  // Set the default window size
  renWin->SetSize(1000, 1000);
  renWin->SetWindowName("FixedPointVolumeRayCastMapperCT");
  renWin->Render();

  // Add the volume to the scene
  renderer->AddVolume(volume);

  renderer->ResetCamera();
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  auto camera = renderer->GetActiveCamera();
  axialRenderer->SetActiveCamera(camera);
  sagittalRenderer->SetActiveCamera(camera);
  coronalRenderer->SetActiveCamera(camera);
  camera->SetPosition(56.8656, -297.084, 78.913);
  camera->SetFocalPoint(109.139, 120.604, 63.5486);
  camera->SetViewUp(-0.00782421, -0.0357807, -0.999329);
  camera->SetDistance(421.227);
  camera->SetClippingRange(146.564, 767.987);

  // interact with data
  renWin->Render();

  iren->Start();*/

  return EXIT_SUCCESS;

  return 0;
}
