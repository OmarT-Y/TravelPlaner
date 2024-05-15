#include "cityselectionwindow.h"
#include "ui_cityselectionwindow.h"

CitySelectionWindow::CitySelectionWindow(int* originI,int* destI,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CitySelectionWindow)
{
    ui->setupUi(this);
    this->destIndex = destI;
    this->originIndex = originI;
}
void CitySelectionWindow::addOriginCity(QString city)
{
    ui->originComboBox->addItem(city);
}
void CitySelectionWindow::addDestCity(QString city)
{
    ui->destComboBox->addItem(city);
}
CitySelectionWindow::~CitySelectionWindow()
{
    delete ui;
}


void CitySelectionWindow::on_originComboBox_currentIndexChanged(int index)
{
    *originIndex=index;
}


void CitySelectionWindow::on_destComboBox_currentIndexChanged(int index)
{
    *destIndex=index;
}

void CitySelectionWindow::on_pushButton_clicked()
{
    CitySelectionWindow::close();
}

