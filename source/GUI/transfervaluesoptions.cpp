#include "transfervaluesoptions.h"
#include "ui_transfervaluesoptions.h"
#include <QColorDialog>
#include <iostream>
#include <qcolor.h>
#include <qnamespace.h>

//#include "../../build/RenderImage_autogen/include_Release/ui_transfervaluesoptions.h"
transferValuesOptions::transferValuesOptions(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::transferValuesOptions)
{
    ui->setupUi(this);

    this->ui->spinBox->setMinimum(-10000);
    this->ui->spinBox->setMaximum(10000);

    connect(this->ui->pushButton , &QPushButton::clicked , this , &transferValuesOptions::onColortButtonClick);
}

transferValuesOptions::~transferValuesOptions()
{
    delete ui;
}

void transferValuesOptions::onColortButtonClick(){

  QColor color = QColorDialog::getColor(Qt::white,this,"choose color",QColorDialog::ShowAlphaChannel);
  activeColor = color;
  setButtonColor(color.red(),color.green(), color.blue() , color.alpha());
}

void transferValuesOptions::setButtonColor(int r,int g,int b,int a){


  QString style = QString("border: none; background-color: rgba(%1, %2, %3,%4);")
                        .arg(r)
                        .arg(g)
                        .arg(b)
                        .arg(a);

  this->ui->pushButton->setStyleSheet(style);


}


void transferValuesOptions::setNumber(int value){

  this->ui->spinBox->setValue(value);

}
QColor transferValuesOptions::getButtonColor() const {
    return activeColor; // Replace with your actual member variable
}

int transferValuesOptions::getNumber() const {
    return this->ui->spinBox->value(); // Replace with your actual member variable
}
