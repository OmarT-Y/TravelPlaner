#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include "cityinfo.h"
#include "hotelsearch.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    amadeusAuthKey();

}
void MainWindow::amadeusAuthKey()
{
    //get the key
    QString baseAuthURL = "https://test.api.amadeus.com/v1/security/oauth2/token";
    QUrl authURL(baseAuthURL);
    QUrlQuery authQuery;
    authQuery.addQueryItem("grant_type","client_credentials");
    authQuery.addQueryItem("client_id","i3kRQQ1tKfM9183Fvi50bE3w3wNFhlRK");
    authQuery.addQueryItem("client_secret","meZFXqwOahv9JtsX");
    //authURL.setQuery(authQuery);

    QNetworkRequest authReq(authURL);
    authReq.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    reply = manager.post(authReq,authQuery.toString(QUrl::FullyEncoded).toUtf8());
    // Busy wait until the reply is ready
    while (!reply->isFinished()) {
        qApp->processEvents(); // Process events to prevent GUI freeze
    }
    QByteArray dataAuth = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(dataAuth);
    QJsonObject jsonObj = jsonDoc.object();
    amadeusKey = jsonObj["access_token"].toString();
}
void MainWindow::City_Search_API(QString searchKey)
{
    QString baseurl = "https://test.api.amadeus.com/v1/reference-data/locations/cities";
    QUrl url(baseurl);
    QUrlQuery query;
    query.addQueryItem("keyword",searchKey.toUtf8());
    query.addQueryItem("max","15");
    url.setQuery(query);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader("Authorization", "Bearer "+amadeusKey.toUtf8());

    reply = manager.get(request);

    // Busy wait until the reply is ready
    while (!reply->isFinished()) {
        qApp->processEvents(); // Process events to prevent GUI freeze
    }
    QByteArray replyData = reply->readAll();
    QJsonDocument resDoc = QJsonDocument::fromJson(replyData);
    QJsonArray data = resDoc["data"].toArray();
    for(const auto &result : data)
    {
        QJsonObject entry = result.toObject();
        QString lon = ((entry["geoCode"].toObject())["longitude"]).toString();
        QString lat = ((entry["geoCode"].toObject())["latitude"]).toString();
        citySearchRes.push_back(CityInfo(entry["name"].toString(),entry["iataCode"].toString(),entry["address"].toObject()["countryCode"].toString(),lon,lat));
    }
}
void MainWindow::Hotel_List(QString cityCode,uint32_t am_flag, int min_rating)
{
    QString baseurl = "https://test.api.amadeus.com/v1/reference-data/locations/hotels/by-city";
    QUrl url(baseurl);
    QUrlQuery query;

    query.addQueryItem("cityCode",cityCode.toUtf8());
    QString amenities = amenitiesToQString(am_flag);
    query.addQueryItem("amenities", QUrl::toPercentEncoding(amenities));
    query.addQueryItem("radius","15");
    if(min_rating > 1 )
    {
        QString rating = "";
        for(int i= min_rating;i<5;i++)
        {
            rating += QString::number(i);
            rating +=",";
        }
        rating.removeLast();

        query.addQueryItem("ratings",rating.toUtf8());
    }
    url.setQuery(query);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader("Authorization", "Bearer "+amadeusKey.toUtf8());

    reply = manager.get(request);

    // Busy wait until the reply is ready
    while (!reply->isFinished()) {
        qApp->processEvents(); // Process events to prevent GUI freeze
    }
    QByteArray replyData = reply->readAll();
    QJsonDocument resDoc = QJsonDocument::fromJson(replyData);
    QJsonArray data = resDoc["data"].toArray();

    //let the parsing begin
    for(const auto& entry:data)
    {
        QJsonObject hotel = entry.toObject();
        cityHotelRes.push_back(HotelInfo(hotel["name"].toString(),hotel["hotelId"].toString()));
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->Hotel_List("CAI",1<<25,0);
}

