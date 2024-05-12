#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
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

void MainWindow::flight_offer_search_API(QString originLocationCode , QString destinationLocationCode , QString departureDate , int adults , int children=-1,QString returnDate="")
{
    QString baseurl = "https://test.api.amadeus.com/v2/shopping/flight-offers";
    QNetworkAccessManager manager;
    QNetworkReply *reply = nullptr;
    QUrl url(baseurl);
    QUrlQuery query;
    query.addQueryItem("originLocationCode",originLocationCode.toUtf8());
    query.addQueryItem("destinationLocationCode",destinationLocationCode.toUtf8());
    query.addQueryItem("departureDate",departureDate.toUtf8());
    if(!returnDate.size())
    {
        query.addQueryItem("returnDate",returnDate.toUtf8());
    }
    query.addQueryItem("adults",QString::number(adults).toUtf8());
    if(children!=-1)
    {
        query.addQueryItem("children",QString::number(children).toUtf8());
    }
   // query.addQueryItem("nonStop","true");
   // query.addQueryItem("maxPrice","5000");
    query.addQueryItem("max","10");
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader("Authorization", "Bearer "+amadeusKey.toUtf8());

    reply = manager.get(request);

    // Busy wait until the reply is ready
    while (!reply->isFinished()) {
        qApp->processEvents(); // Process events to prevent GUI freeze
    }

    QByteArray data = reply->readAll();
}
void MainWindow::reqData()
{
    QString baseurl = "https://test.api.amadeus.com/v1/reference-data/locations/hotels/by-city";
    QNetworkAccessManager manager;
    QNetworkReply *reply = nullptr;
    QUrl url(baseurl);
    QUrlQuery query;
    query.addQueryItem("cityCode","CAI");
    query.addQueryItem("radius","15");
    query.addQueryItem("amenities","SWIMMING_POOL,SPA,TENNIS");
    query.addQueryItem("hotelSource","ALL");
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader("Authorization", "Bearer "+amadeusKey.toUtf8());

    reply = manager.get(request);

    // Busy wait until the reply is ready
    while (!reply->isFinished()) {
        qApp->processEvents(); // Process events to prevent GUI freeze
    }

    QByteArray data = reply->readAll();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->flight_offer_search_API("CAI" , "BKK" , "2024-05-20" ,   3, 1,"2024-05-24");
}

