#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonArray>
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

void MainWindow::flight_offer_search_API(QString originLocationCode , QString destinationLocationCode , QString departureDate , int adults , int children=-1,QString returnDate="", QString currency="",QString amount ="")
{
    //TODO : MAX PRICE OF FLIGHT
    //TODO : TYPE OF SEAT

    QString baseurl = "https://test.api.amadeus.com/v2/shopping/flight-offers";
    QUrl url(baseurl);
    QUrlQuery query;
    query.addQueryItem("originLocationCode",originLocationCode.toUtf8());
    query.addQueryItem("destinationLocationCode",destinationLocationCode.toUtf8());
    query.addQueryItem("departureDate",departureDate.toUtf8());
    if(currency.size() && amount.size())
    {
        query.addQueryItem("currencyCode",currency.toUtf8());
        query.addQueryItem("maxPrice",amount.toUtf8());
    }

    if(returnDate.size())
    {
        query.addQueryItem("returnDate",returnDate.toUtf8());
    }
    query.addQueryItem("adults",QString::number(adults).toUtf8());
    if(children!=-1)
    {
        query.addQueryItem("children",QString::number(children).toUtf8());
    }
    query.addQueryItem("max","10");
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/vnd.amadeus+json");
    request.setRawHeader("Authorization", "Bearer "+amadeusKey.toUtf8());
    reply = manager.get(request);

    // Busy wait until the reply is ready
    while (!reply->isFinished()) {
        qApp->processEvents(); // Process events to prevent GUI freeze
    }

    QByteArray data = reply->readAll();
    QJsonDocument jsonDocument =QJsonDocument::fromJson(data);
    QJsonArray data_array = jsonDocument["data"].toArray();
    for(const auto &i : data_array)
    {
        QJsonObject entry = i.toObject();
        flight_offer current_offer ;
        current_offer.flightSource= entry["source"].toString();
        current_offer.oneWay=entry["oneWay"].toBool();
        current_offer.lastingTickitingDate=entry["lastTicketingDate"].toString();
        current_offer.numberOfSeatsLeft=entry["numberOfBookableSeats"].toInt();
        current_offer.price=(entry["price"].toObject())["grandTotal"].toString();
        QJsonArray iti =entry["itineraries"].toArray();
        current_offer.flights.first.duration=(iti[0].toObject())["duration"].toString();
        current_offer.flights.first.numberOfStops=(iti[0].toObject())["segments"].toArray().size()-1;
        current_offer.flights.first.departureDateTime=(((iti[0].toObject())["segments"].toArray())[0].toObject())["departure"].toObject()["at"].toString();
        current_offer.flights.first.arrivalDateTime=(((iti[0].toObject())["segments"].toArray())[ \
        (iti[0].toObject())["segments"].toArray().size()-1].toObject())["arrival"].toObject()["at"].toString();

        if(iti.size()==2)
        {
            current_offer.flights.second.duration=(iti[1].toObject())["duration"].toString();
            current_offer.flights.second.numberOfStops=(iti[1].toObject())["segments"].toArray().size()-1;
            current_offer.flights.second.departureDateTime=(((iti[1].toObject())["segments"].toArray())[0].toObject())["departure"].toObject()["at"].toString();
            current_offer.flights.second.arrivalDateTime=(((iti[1].toObject())["segments"].toArray())[ \
            (iti[1].toObject())["segments"].toArray().size()-1].toObject())["arrival"].toObject()["at"].toString();
        }
        flight_offers.push_back(current_offer);
    }
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
    this->flight_offer_search_API("CAI" , "BKK" , "2024-05-20" ,   3, 1,"2024-05-24","EUR","800");
}

