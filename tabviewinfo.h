#ifndef TABVIEWINFO_H
#define TABVIEWINFO_H
#include "cityinfo.h"
#include <QWidget>

namespace Ui {
class TabViewInfo;
}

class TabViewInfo : public QWidget
{
    Q_OBJECT

public:
    explicit TabViewInfo(CityInfoAll *originCityInfo,CityInfoAll *destCityInfo,QWidget *parent = nullptr);
    ~TabViewInfo();

private:
    Ui::TabViewInfo *ui;
};

#endif // TABVIEWINFO_H
