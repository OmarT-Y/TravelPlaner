#ifndef TABVIEWINFO_H
#define TABVIEWINFO_H
#include "cityinfo.h"
#include <QImage>
#include <QWidget>
#include "flightinfowidget.h"
#include "hotelscell.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include "activitiescell.h"
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
    void addHotelOffer(hotelsCell* offer);
    void addActivity(activitiescell* offer);
    void hideFlight();
    void hideHotel();
    void setCallBackHomeReset(void (*resHome)(void));
private slots:
    void on_pushButton_clicked();
signals:
    void resetHomeSig();
private:
    Ui::TabViewInfo *ui;
};

#endif // TABVIEWINFO_H
