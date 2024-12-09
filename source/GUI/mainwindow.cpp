#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QVTKInteractor.h>
#include <vtkDICOMImageReader.h>
#include <string>
#include <utility>
#include <vtkNew.h>
#include <vtkCamera.h>
#include <vtkColorTransferFunction.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkImageData.h>
#include <vtkImageResample.h>
#include <vtkInteractorObserver.h>
#include <vtkNamedColors.h>
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
#include <vtkSmartPointer.h>

#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkViewport.h>

// toca quitar esta linea antes de compilar
#include "../../build/RenderImage_autogen/include_Release/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    double opacityWindow = 4096;
    double opacityLevel = 2048;
    int clip = 0;
    double reductionFactor = 1.0;
    double frameRate = 10.0;

    std::string dirPath = "C:\\Users\\Andres\\Desktop\\5.000000-SKINTOSKINSIM0.5MM10250\\5.000000-SKINTOSKINSIM0.5MM10250";
    vtkNew<vtkDICOMImageReader> reader;
    reader->SetDirectoryName(dirPath.c_str());
    
    reader->Update();
    auto input = reader->GetOutput();

    



    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkRenderer> renderer;

    // renderer for views
    vtkNew<vtkRenderer> axialRenderer;
    vtkNew<vtkRenderer> coronalRenderer;
    vtkNew<vtkRenderer> sagittalRenderer;

    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    this->ui->openGLWidget->setRenderWindow(renderWindow);




    // Verify that we actually have a volume
    int dim[3];
    input->GetDimensions(dim);

    if (dim[0] < 2 || dim[1] < 2 || dim[2] < 2)
    {
      exit(EXIT_FAILURE);
    }

    vtkNew<vtkImageResample> resample;
    if (reductionFactor < 1.0)
    {
      resample->SetInputConnection(reader->GetOutputPort());
      resample->SetAxisMagnificationFactor(0, reductionFactor);
      resample->SetAxisMagnificationFactor(1, reductionFactor);
      resample->SetAxisMagnificationFactor(2, reductionFactor);
    }

    // Create our volume and mapper
    vtkNew<vtkVolume> volume;
    vtkNew<vtkFixedPointVolumeRayCastMapper> mapper;

    if (reductionFactor < 1.0)
    {
      mapper->SetInputConnection(resample->GetOutputPort());
    }
    else
    {
      mapper->SetInputConnection(reader->GetOutputPort());
    }

    // Set the sample distance on the ray to be 1/2 the average spacing
    double spacing[3];
    if (reductionFactor < 1.0)
    {
      resample->GetOutput()->GetSpacing(spacing);
    }
    else
    {
      input->GetSpacing(spacing);
    }
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


   vtkNew<vtkImageViewer2> axialViewer;
    axialViewer->SetInputData(input);
    axialViewer->SetRenderWindow(renderWindow);
    axialViewer->SetRenderer(axialRenderer);
    axialViewer->SetSliceOrientationToXY();
    axialViewer->SetSlice(axialViewer->GetSliceMin()+1); // Set to middle slice

    vtkNew<vtkImageViewer2> coronalViewer;
    coronalViewer->SetInputData(input);
    coronalViewer->SetRenderWindow(renderWindow);
    coronalViewer->SetRenderer(coronalRenderer);
    coronalViewer->SetSliceOrientationToXZ();
    coronalViewer->SetSlice(axialViewer->GetSliceMin()+1); // Set to middle slice

    vtkNew<vtkImageViewer2> sagittalViewer;
    sagittalViewer->SetInputData(input);
    sagittalViewer->SetRenderWindow(renderWindow);
    sagittalViewer->SetRenderer(sagittalRenderer);
    sagittalViewer->SetSliceOrientationToYZ();
    sagittalViewer->SetSlice(axialViewer->GetSliceMin()+1); // Set to middle slice     //Set up viewports for the three renderers

    renderer->SetViewport(0.0, 0.0, 0.7, 1.0); 
    axialRenderer->SetViewport(0.7, 0.66, 1.0, 1.0);  // Axial view (top-right)
    coronalRenderer->SetViewport(0.7, 0.33, 1.0, 0.66); // Coronal view (middle-right)
    sagittalRenderer->SetViewport(0.7, 0.0, 1.0, 0.33); // Sagittal view (bottom-right)

    renderer->AddVolume(volume);
    renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
    this->ui->openGLWidget->renderWindow()->AddRenderer(axialRenderer);
    this->ui->openGLWidget->renderWindow()->AddRenderer(coronalRenderer);
    this->ui->openGLWidget->renderWindow()->AddRenderer(sagittalRenderer);

    this->ui->openGLWidget->renderWindow()->AddRenderer(renderer);
    renderWindow->Render();


    
}

MainWindow::~MainWindow()
{
    delete ui;
}
