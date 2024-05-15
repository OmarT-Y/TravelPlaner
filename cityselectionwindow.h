#ifndef CITYSELECTIONWINDOW_H
#define CITYSELECTIONWINDOW_H

#include <QDialog>

namespace Ui {
class CitySelectionWindow;
}

class CitySelectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CitySelectionWindow(int* originI,int* destI,QWidget *parent=nullptr);
    ~CitySelectionWindow();
    void addOriginCity(QString city);
    void addDestCity(QString city);
private slots:
    void on_pushButton_clicked();

    void on_originComboBox_currentIndexChanged(int index);

    void on_destComboBox_currentIndexChanged(int index);

private:
    int *originIndex = nullptr;
    int *destIndex = nullptr;
    Ui::CitySelectionWindow *ui;
};

#endif // CITYSELECTIONWINDOW_H
