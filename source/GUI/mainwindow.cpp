#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QVTKInteractor.h>
#include <iostream>
#include <memory>
#include <qlistwidget.h>
#include <qpushbutton.h>
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
#include <QTimer>

#include "transfervaluesoptions.h"

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

    // renderer for views
    vtkNew<vtkRenderer> axialRenderer;
    vtkNew<vtkRenderer> coronalRenderer;
    vtkNew<vtkRenderer> sagittalRenderer;

    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    this->ui->openGLWidget->setRenderWindow(renderWindow);


    //// COnseguir dimensiones para confirmar que es una imagen 3d

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


  // usar volume raycast para que se muestre la iamgen en volumetric rendering

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



  /// seleccionar solore y opacidad para diferenciar partes del cuerpo
    // Create our transfer function
    /*vtkNew<vtkColorTransferFunction> colorFun;
    vtkNew<vtkPiecewiseFunction> opacityFun;*/
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



  // inicializar vistas anatomicas

    axialViewer->SetInputData(input);
    axialViewer->SetRenderWindow(renderWindow);
    axialViewer->SetRenderer(axialRenderer);
    axialViewer->SetSliceOrientationToXY();
    axialViewer->SetSlice(axialViewer->GetSliceMin()+1); // Set to middle slice

    coronalViewer->SetInputData(input);
    coronalViewer->SetRenderWindow(renderWindow);
    coronalViewer->SetRenderer(coronalRenderer);
    coronalViewer->SetSliceOrientationToXZ();
    coronalViewer->SetSlice(coronalViewer->GetSliceMin()+1); // Set to middle slice

    sagittalViewer->SetInputData(input);
    sagittalViewer->SetRenderWindow(renderWindow);
    sagittalViewer->SetRenderer(sagittalRenderer);
    sagittalViewer->SetSliceOrientationToYZ();
    sagittalViewer->SetSlice(coronalViewer->GetSliceMin()+1); // Set to middle slice     //Set up viewports for the three renderers

    renderer->SetViewport(0.0, 0.0, 0.7, 1.0); 
    axialRenderer->SetViewport(0.7, 0.66, 1.0, 1.0);  // Axial view (top-right)
    coronalRenderer->SetViewport(0.7, 0.33, 1.0, 0.66); // Coronal view (middle-right)
    sagittalRenderer->SetViewport(0.7, 0.0, 1.0, 0.33); // Sagittal view (bottom-right)



  // renderizr todo
    renderer->AddVolume(volume);
    renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
    this->ui->openGLWidget->renderWindow()->AddRenderer(axialRenderer);
    this->ui->openGLWidget->renderWindow()->AddRenderer(coronalRenderer);
    this->ui->openGLWidget->renderWindow()->AddRenderer(sagittalRenderer);
    this->ui->openGLWidget->renderWindow()->AddRenderer(renderer);


    renderWindow->Render();

    
    // added timer for reducing rendering updates

    debounceTimer = new QTimer(this);
    debounceTimer->setSingleShot(true); // Only trigger once after the timeout
    debounceTimer->setInterval(500); // 100 ms delay before rendering


    // initializa sliders

    this->ui->horizontalSlider->setRange(axialViewer->GetSliceMin(), axialViewer->GetSliceMax());
    this->ui->horizontalSlider_2->setRange(coronalViewer->GetSliceMin(), coronalViewer->GetSliceMax());
    this->ui->horizontalSlider_3->setRange(sagittalViewer->GetSliceMin(), sagittalViewer->GetSliceMax());

    connect(this->ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::onSliderValueChangedAxial);
    connect(this->ui->horizontalSlider_2, &QSlider::valueChanged, this, &MainWindow::onSliderValueChangedCoronal);
    connect(this->ui->horizontalSlider_3, &QSlider::valueChanged, this, &MainWindow::onSliderValueChangedSagittal);
    connect(this->ui->pushButton_4, &QPushButton::clicked , this , &MainWindow::onMuscleButtonClick);
    connect(this->ui->pushButton_5, &QPushButton::clicked , this , &MainWindow::onLungButtonClick);
    connect(this->ui->pushButton_2, &QPushButton::clicked , this , &MainWindow::onBoneButtonClick);
    connect(this->ui->pushButton_3, &QPushButton::clicked , this , &MainWindow::onSkinButtonClick);


  auto item = new QListWidgetItem();

  auto prueba1 = new transferValuesOptions(this);
  item->setSizeHint(prueba1->sizeHint());
  this->ui->listWidget->addItem(item);
  this->ui->listWidget->setItemWidget(item, prueba1);
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSliderValueChangedAxial(int value)
{
  axialViewer->SetSlice(value);
  debounceTimer->start();

}
void MainWindow::onSliderValueChangedCoronal(int value)
{
  coronalViewer->SetSlice(value);
  debounceTimer->start();

}
void MainWindow::onSliderValueChangedSagittal(int value)
{
  sagittalViewer->SetSlice(value);
  debounceTimer->start();

}

void MainWindow::onSliderTimeout() {
    // Perform the rendering after debounce delay
    axialViewer->Render();
    coronalViewer->Render();
    sagittalViewer->Render();
}

void MainWindow::onMuscleButtonClick(){



  colorFun->RemoveAllPoints();
  opacityFun->RemoveAllPoints();
  for(auto const &po : proper.Muscle){


    colorFun->AddRGBPoint(po.value,po.colorOpt.r , po.colorOpt.g , po.colorOpt.b , po.colorOpt.midpoint , po.colorOpt.sharp);
    opacityFun->AddPoint(po.value , po.opaOpt.a , po.opaOpt.midpoint , po.opaOpt.sharp);

  }
  /*colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
  colorFun->AddRGBPoint(-155, .55, .25, .15, 0.5, .92);
  colorFun->AddRGBPoint(217, .88, .60, .29, 0.33, 0.45);
  colorFun->AddRGBPoint(420, 1, .94, .95, 0.5, 0.0);
  colorFun->AddRGBPoint(3071, .83, .66, 1, 0.5, 0.0);


  opacityFun->RemoveAllPoints();
  opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
  opacityFun->AddPoint(-155, 0, 0.5, 0.92);
  opacityFun->AddPoint(217, .68, 0.33, 0.45);
  opacityFun->AddPoint(420, .83, 0.5, 0.0);
  opacityFun->AddPoint(3071, .80, 0.5, 0.0);*/
  renderer->Render();
}

void MainWindow::onLungButtonClick(){

  colorFun->RemoveAllPoints();
  opacityFun->RemoveAllPoints();
  for(auto const &po : proper.Lung){


    colorFun->AddRGBPoint(po.value,po.colorOpt.r , po.colorOpt.g , po.colorOpt.b , po.colorOpt.midpoint , po.colorOpt.sharp);
    opacityFun->AddPoint(po.value , po.opaOpt.a , po.opaOpt.midpoint , po.opaOpt.sharp);

  }

  /*colorFun->AddRGBPoint(-1000, 0, 0, 0, 0.0, 0.0); // Air (black)
  colorFun->AddRGBPoint(0, 0, 0, 0, 0.0, 0.0); // Air (black)
  colorFun->AddRGBPoint(2, 0.8, 0.7, 0.5, 0.1, 0.6); // Lungs (light brown or yellowish)
  colorFun->AddRGBPoint(5, 1.0, 0.8, 0.6, 0.2, 0.8); // Lungs (lighter brown)
  colorFun->AddRGBPoint(300, 1.0, 1.0, 1.0, 0.7, 0.8);  // Bone (white)

  opacityFun->RemoveAllPoints();
  opacityFun->AddPoint(-1000, 0.0); // Air (transparent)
  opacityFun->AddPoint(0, 0.0); // Air (transparent)
  opacityFun->AddPoint(2, 0.1);  // Lungs, semi-transparent
  opacityFun->AddPoint(5, 0.3);  // Lungs, slightly more opaque
  opacityFun->AddPoint(300, 1.0);   // Bone, fully opaque*/
  renderer->Render();

}


void MainWindow::onBoneButtonClick(){


  colorFun->RemoveAllPoints();
  opacityFun->RemoveAllPoints();
  for(auto const &po : proper.Bone){


    colorFun->AddRGBPoint(po.value,po.colorOpt.r , po.colorOpt.g , po.colorOpt.b , po.colorOpt.midpoint , po.colorOpt.sharp);
    opacityFun->AddPoint(po.value , po.opaOpt.a , po.opaOpt.midpoint , po.opaOpt.sharp);

  }
  /*colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
  colorFun->AddRGBPoint(-16, 0.73, 0.25, 0.30, 0.49, .61);
  colorFun->AddRGBPoint(641, .90, .82, .56, .5, 0.0);
  colorFun->AddRGBPoint(3071, 1, 1, 1, .5, 0.0);

  opacityFun->RemoveAllPoints();
  opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
  opacityFun->AddPoint(-16, 0, .49, .61);
  opacityFun->AddPoint(641, .72, .5, 0.0);
  opacityFun->AddPoint(3071, .71, 0.5, 0.0);*/
  renderer->Render();

}

void MainWindow::onSkinButtonClick(){

  colorFun->RemoveAllPoints();
  opacityFun->RemoveAllPoints();
  for(auto const &po : proper.Skin){


    colorFun->AddRGBPoint(po.value,po.colorOpt.r , po.colorOpt.g , po.colorOpt.b , po.colorOpt.midpoint , po.colorOpt.sharp);
    opacityFun->AddPoint(po.value , po.opaOpt.a , po.opaOpt.midpoint , po.opaOpt.sharp);

  }
  /*colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
  colorFun->AddRGBPoint(-1000, .62, .36, .18, 0.5, 0.0);
  colorFun->AddRGBPoint(-500, .88, .60, .29, 0.33, 0.45);
  colorFun->AddRGBPoint(3071, .83, .66, 1, 0.5, 0.0);

  opacityFun->RemoveAllPoints();
  opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
  opacityFun->AddPoint(-1000, 0, 0.5, 0.0);
  opacityFun->AddPoint(-500, 1.0, 0.33, 0.45);
  opacityFun->AddPoint(3071, 1.0, 0.5, 0.0);*/
  renderer->Render();
}


