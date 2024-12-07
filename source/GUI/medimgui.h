#ifndef MEDIMGUI_H
#define MEDIMGUI_H

#include <QMainWindow>

namespace Ui {
class MedImGUI;
}

class MedImGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit MedImGUI(QWidget *parent = nullptr);
    ~MedImGUI();

private:
    Ui::MedImGUI *ui;
};

#endif // MEDIMGUI_H
