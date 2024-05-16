#include "tabviewinfo.h"
#include "ui_tabviewinfo.h"

TabViewInfo::TabViewInfo(CityInfoAll* originCityFullInfo,CityInfoAll* destCityFullInfo,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TabViewInfo)
{
    ui->setupUi(this);
    QImage image ;

}

TabViewInfo::~TabViewInfo()
{
    delete ui;
}
