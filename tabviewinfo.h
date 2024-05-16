#ifndef TABVIEWINFO_H
#define TABVIEWINFO_H
#include "cityinfo.h"
#include <QWidget>
#include "flightinfowidget.h"

namespace Ui {
class TabViewInfo;
}

class TabViewInfo : public QWidget
{
    Q_OBJECT

public:
    explicit TabViewInfo(CityInfoAll *originCityInfo,CityInfoAll *destCityInfo,QWidget *parent = nullptr);
    ~TabViewInfo();
    void addFlightOffer(FlightInfoWidget* offer);
    // void addHotelOffer(HotelOfferInfoWidget* offer);
    // void addActivity(ActivityInfoWidget* offer);
private:
    Ui::TabViewInfo *ui;
};

#endif // TABVIEWINFO_H
