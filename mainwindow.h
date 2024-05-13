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

#include "flight_search.h"
#include "activities_tours.h"

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
    void City_Search_API(QString searchKey);
    void Hotel_List(QString cityCode,uint32_t am_flag, int min_rating);
    void flight_offer_search_API(QString originLocationCode , QString destinationLocationCode , QString departureDate ,int adults , int children,QString returnDate, QString currency,QString amount  );
    void get_Tours_Activities(QString latitude , QString longitude );
    QString getAirline(QString code);

    /*Omar Tamer*/
    /*end Omar Tamer*/
    /*Ziad Mohamed*/
    void getCityInfo(CityInfo city);
//void getHotelExtraInfo( int number_of_rooms , QString price_low,QString price_high ,QString currency);
    /*end Ziad Mohamed*/
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
    QNetworkReply *reply = nullptr;
    QString amadeusKey;
    std::pair<QString,QString> originCity;
    std::pair<QString,QString> destCity;
    std::vector<CityInfo> citySearchRes;
    std::vector<HotelInfo> cityHotelRes;
    std::vector <flight_offer> flight_offers;
    std::vector <activity> activities;
    /*Omar Tamer*/

    /*end Omar Tamer*/
    /*Ziad Mohamed*/
    CityInfoAll CityFullinfo;
    // std::vector<HotelInfoAll> HotelsFullInfo;
    /*end Ziad Mohamed*/
};
#endif // MAINWINDOW_H
