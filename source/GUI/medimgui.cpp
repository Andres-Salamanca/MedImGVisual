#include "medimgui.h"
#include "ui_medimgui.h"

MedImGUI::MedImGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MedImGUI)
{
    ui->setupUi(this);
}

MedImGUI::~MedImGUI()
{
    delete ui;
}
