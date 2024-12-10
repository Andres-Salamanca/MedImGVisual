#include "transfervaluesoptions.h"
#include "ui_transfervaluesoptions.h"
#include <QColorDialog>
#include <iostream>
#include <qcolor.h>
#include <qnamespace.h>

#include "../../build/RenderImage_autogen/include_Release/ui_transfervaluesoptions.h"
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
  std::cout << color.red() << " " << color.blue() << " " << color.green() << color.alpha() << "\n";
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

