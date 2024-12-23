#ifndef TRANSFERVALUESOPTIONS_H
#define TRANSFERVALUESOPTIONS_H

#include <QWidget>
#include <qobject.h>
#include <qtmetamacros.h>
namespace Ui {
class transferValuesOptions;
}

class transferValuesOptions : public QWidget
{
    Q_OBJECT

public:
    explicit transferValuesOptions(QWidget *parent = nullptr);
    ~transferValuesOptions();
    void setButtonColor(int r,int g,int b,int a=255);
    void setNumber(int value);
    QColor getButtonColor() const;
    int getNumber() const;
    QColor activeColor;
private:
    Ui::transferValuesOptions *ui;
private slots:
  void onColortButtonClick();
};

#endif // TRANSFERVALUESOPTIONS_H
