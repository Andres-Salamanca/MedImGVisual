#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtmetamacros.h>
#include <vtkImageViewer2.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    vtkNew<vtkImageViewer2> axialViewer;
    vtkNew<vtkImageViewer2> coronalViewer;
    vtkNew<vtkImageViewer2> sagittalViewer;
    QTimer *debounceTimer;
    Ui::MainWindow *ui;

private slots:
  void onSliderValueChangedAxial(int value);
  void onSliderValueChangedCoronal(int value);
  void onSliderValueChangedSagittal(int value);
  void onMuscleButtonClick();
  void onBoneButtonClick();
  void onSkinButtonClick();
  void onLungButtonClick();
  void onSliderTimeout();
};

#endif // MAINWINDOW_H
