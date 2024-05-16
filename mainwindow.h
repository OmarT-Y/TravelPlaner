#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>

#include "cityinfo.h"
#include "hotelsearch.h"
#include "tabviewinfo.h"
#include "flight_search.h"
#include "activities_tours.h"
#include "travelinfo.h"
#include "hotelscell.h"
#include "activitiescell.h"

typedef struct
{
    QString originCity;
    QString destCity;
    QString startDate;
    QString endDate;
    QString numOfAdult;
    QString numOfChild;
    QString currencyCode;
    bool flightEnable;
    bool hotelEnable;
    QString flightMaxPrice;
    QString hotelMaxPrice;
    QString hotelMinRating;
    QString hotelNumOfRooms;
    uint64_t am_flag;
}TripDetails;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void amadeusAuthKey();
    std::vector<CityInfo> City_Search_API(QString searchKey);
    void Hotel_List(QString cityCode,uint64_t am_flag, int min_rating);
    void flight_offer_search_API(QString originLocationCode , QString destinationLocationCode , QString departureDate ,int adults , int children,QString returnDate, QString currency,QString amount  );
    void get_Tours_Activities(QString latitude , QString longitude );
    QString getAirline(QString code);

    /*Omar Tamer*/
    QString getErrorMsgJson(QJsonDocument &doc);
    void Hotel_Search_API(int number_of_rooms ,int adultInRoom,QString checkIn,QString checkOut,QString currency,QString price_high );
    /*end Omar Tamer*/
    /*Ziad Mohamed*/
    CityInfoAll getCityInfo(CityInfo city);

//void getHotelExtraInfo( int number_of_rooms , QString price_low,QString price_high ,QString currency);
    /*end Ziad Mohamed*/
private slots:
    void letsTravelClicked();
    void resetHome();
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
    QNetworkReply *reply = nullptr;
    QString amadeusKey;
    TabViewInfo* tabView =nullptr;
    std::vector<QString> cityHotelRes;
    std::vector <flight_offer> flight_offers;
    std::vector <activity> activities;
    /*Omar Tamer*/
    std::vector<HotelRoomOfferInfo> roomOffers;
    TravelInfo* travelInfoWidget=nullptr;
    TripDetails tripDetails;
    CityInfo originCity;
    CityInfo destCity;
    /*end Omar Tamer*/
    /*Ziad Mohamed*/
    CityInfoAll originCityFullinfo;
    CityInfoAll destCityFullinfo;
    /*end Ziad Mohamed*/
};
#endif // MAINWINDOW_H
