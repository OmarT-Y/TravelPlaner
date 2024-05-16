#include "tabviewinfo.h"
#include "ui_tabviewinfo.h"

TabViewInfo::TabViewInfo(CityInfoAll* originCityFullInfo,CityInfoAll* destCityFullInfo,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TabViewInfo)
{
    ui->setupUi(this);
    QImage image ;

}
void TabViewInfo::addFlightOffer(FlightInfoWidget* offer)
{
    ui->flightLayout->addWidget(offer);
}
// void TabViewInfo::addHotelOffer(HotelOfferInfoWiget* offer)
// {
//     ui->accomodationLayout->addWidget(offer);
// }
// void TabViewInfo::addActivity(ActivityInfoWidget* offer)
// {
//     ui->activiteisLayout->addWidget(offer);
// }
TabViewInfo::~TabViewInfo()
{
    delete ui;
}
