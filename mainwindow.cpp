#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrlQuery>
#include "cityinfo.h"
#include "hotelsearch.h"
#include "cityselectionwindow.h"
#include <QMessageBox>
#include "flightinfowidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->travelInfoWidget = new TravelInfo();
    this->ui->mainLayout->addWidget(travelInfoWidget);
    amadeusAuthKey();
    connect(this->travelInfoWidget->searchButton,SIGNAL(clicked(bool)),this,SLOT(letsTravelClicked()));
    setObjectName("MainMenu");
    setStyleSheet("QWidget#MainMenu {border-image: url(:/new/prefix1/bg8);}");

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
std::vector<CityInfo> MainWindow::City_Search_API(QString searchKey)
{
    std::vector<CityInfo> citySearchRes;
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
        QString lon = QString::number(entry["geoCode"].toObject()["longitude"].toDouble());
        QString lat = QString::number(entry["geoCode"].toObject()["latitude"].toDouble());
        CityInfo city(entry["name"].toString(),entry["iataCode"].toString(),entry["address"].toObject()["countryCode"].toString(),lon,lat);
        if(city.cityCode.size())
            citySearchRes.push_back(city);
    }
    return citySearchRes;
}
void MainWindow::Hotel_List(QString cityCode,uint64_t am_flag, int min_rating)
{
    QString baseurl = "https://test.api.amadeus.com/v1/reference-data/locations/hotels/by-city";
    QUrl url(baseurl);
    QUrlQuery query;

    query.addQueryItem("cityCode",cityCode.toUtf8());
    QString amenities = amenitiesToQString(am_flag);
    if(am_flag)
        query.addQueryItem("amenities", QUrl::toPercentEncoding(amenities));
    query.addQueryItem("radius","20");
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
        cityHotelRes.push_back(hotel["hotelId"].toString());
        if(cityHotelRes.size()>49)break;
    }
}
QString MainWindow::getAirline(QString code)
{
    QString baseurl = "https://test.api.amadeus.com/v1/reference-data/airlines";
    QUrl url(baseurl);
    QUrlQuery query;
    query.addQueryItem("airlineCodes",code.toUtf8());
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
    if(data_array.size())
        return data_array[0].toObject()["businessName"].toString();
    return "";
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
        current_offer.airline=(iti[0].toObject())["segments"].toArray()[0].toObject()["carrierCode"].toString();
        current_offer.airline=getAirline(current_offer.airline);
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


void MainWindow::get_Tours_Activities(QString latitude , QString longitude)
{
    QString baseurl = "https://test.api.amadeus.com/v1/shopping/activities";
    QUrl url(baseurl);
    QUrlQuery query;
    query.addQueryItem("latitude",latitude.toUtf8());
    query.addQueryItem("longitude",longitude.toUtf8());
    query.addQueryItem("radius" , QString::number(10).toUtf8());

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
        activity current_activity ;
        current_activity.name=entry["name"].toString();
        current_activity.description=entry["description"].toString();
        current_activity.booking_link=entry["bookingLink"].toString();
        current_activity.duration_hours=entry["minimumDuration"].toString();
        current_activity.currency=entry["price"].toObject()["currencyCode"].toString();
        current_activity.price=entry["price"].toObject()["amount"].toString();

        for (int j=0;j<entry["pictures"].toArray().size();j++)
        {
            current_activity.pictures.push_back(entry["pictures"].toArray()[j].toString());
        }
        activities.push_back(current_activity);
    }
}
/*Omar Tamer*/
QString MainWindow::getErrorMsgJson(QJsonDocument &doc)
{
    QJsonObject jsonData = doc.object();
    if(jsonData.contains("title"))
    {
        return jsonData["title"].toString();
    }
    else if(jsonData.contains("errors"))
    {
        return (jsonData["errors"].toArray())[0].toString();
    }
    return "NoErr";
}

void MainWindow::Hotel_Search_API(int number_of_rooms ,int adultInRoom,QString checkIn,QString checkOut,QString currency,QString price_high = "")
{
    QString baseurl = "https://test.api.amadeus.com/v3/shopping/hotel-offers";
    QUrl url(baseurl);
    QUrlQuery query;
    QString hotelListString="";
    for(int i=1;i<cityHotelRes.size();i++)
    {
        hotelListString+=cityHotelRes[i];
        hotelListString+=',';
    }
    hotelListString.removeLast();
    query.addQueryItem("hotelIds",hotelListString.toUtf8());
    query.addQueryItem("roomQuantity" , QString::number(number_of_rooms).toUtf8());
    query.addQueryItem("checkInDate",checkIn.toUtf8());
    query.addQueryItem("checkOutDate",checkOut.toUtf8());
    query.addQueryItem("adults",QString::number(adultInRoom).toUtf8());
    if(price_high.size()&&price_high!="0")
    {
        QString price_range="0-"+price_high;
        query.addQueryItem("priceRange",price_range.toUtf8());
        query.addQueryItem("currency",currency.toUtf8());
    }
    query.addQueryItem("paymentPolicy","NONE");
    query.addQueryItem("includeClosed","false");
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/vnd.amadeus+json");
    request.setRawHeader("Authorization", "Bearer "+amadeusKey.toUtf8());
    reply = manager.get(request);
    // Busy wait until the reply is ready
    while (!reply->isFinished()) {
        qApp->processEvents(); // Process events to prevent GUI freeze
    }
    QByteArray replyData = reply->readAll();
    QJsonDocument resDoc = QJsonDocument::fromJson(replyData);
    QJsonArray data = resDoc["data"].toArray();
    for(auto const& entry:data)
    {
        HotelRoomOfferInfo offer;
        QJsonObject HotelOffer = entry.toObject();
        //hotel details
        offer.hotelName = HotelOffer["hotel"].toObject()["name"].toString();
        //offer details
        QJsonArray offers= HotelOffer["offers"].toArray();
        for(auto const& offer_entry:offers)
        {
            QJsonObject hotel_offer = offer_entry.toObject();
            offer.numOf_rooms = hotel_offer["roomQuantity"].toInt();
            if(offer.numOf_rooms==0)offer.numOf_rooms=number_of_rooms;
            offer.roomCategory = ((hotel_offer["room"].toObject())["typeEstimated"].toObject())["category"].toString();
            offer.numOf_beds = ((hotel_offer["room"].toObject())["typeEstimated"].toObject())["beds"].toInt();
            offer.bedtype = ((hotel_offer["room"].toObject())["typeEstimated"].toObject())["bedType"].toString();
            offer.offer_description = ((hotel_offer["room"].toObject())["description"].toObject())["text"].toString();
            offer.currencyCode = ((hotel_offer["price"].toObject()))["currency"].toString();
            offer.price = ((hotel_offer["price"].toObject()))["total"].toString();
            if(hotel_offer.contains("boardType"))
                offer.boardType = hotel_offer["boardType"].toString();
            else
                offer.boardType = "";
            offer.payment_type = ((hotel_offer["policies"].toObject()))["paymentType"].toString();
            QJsonObject price = hotel_offer["price"].toObject();
            if (price.contains("taxes"))
            {
                QJsonObject taxes = price["taxes"].toObject();
                if (taxes.contains("amount") && !taxes["included"].toBool())
                    offer.taxAmount = taxes["amount"].toString();
                else
                    offer.taxAmount = "";

                if (taxes.contains("percentage") && !taxes["included"].toBool())
                    offer.taxPer = taxes["percentage"].toString();
                else
                    offer.taxPer = "";
            }
            else
            {
                offer.taxPer = "";
                offer.taxAmount = "";
            }
            this->roomOffers.push_back(offer);
        }
    }
}

void MainWindow::letsTravelClicked()
{
    //retrieve data
    tripDetails.am_flag=travelInfoWidget->am_flag;
    tripDetails.currencyCode = travelInfoWidget->currencyBox->currentText();
    tripDetails.destCity = travelInfoWidget->destCitySearch->text().trimmed();
    tripDetails.originCity = travelInfoWidget->originCitySearch->text().trimmed();
    tripDetails.endDate = travelInfoWidget->endDate->date().toString("yyyy-MM-dd");
    tripDetails.startDate = travelInfoWidget->startDate->date().toString("yyyy-MM-dd");
    tripDetails.flightEnable = travelInfoWidget->flightCheck->isChecked();
    tripDetails.hotelEnable = travelInfoWidget->hotelCheck->isChecked();
    tripDetails.numOfAdult = travelInfoWidget->adultnumberspinBox->text();
    tripDetails.numOfChild = travelInfoWidget->childrennumberspinBox->text();
    tripDetails.flightMaxPrice = travelInfoWidget->flightmaxpriceSpinBox->text();
    tripDetails.hotelMaxPrice = travelInfoWidget->hotelmaxpriceSpinBox->text();
    tripDetails.hotelMinRating = travelInfoWidget->minimumRatingSpinBox->text();
    tripDetails.hotelNumOfRooms = travelInfoWidget->numberofRoomsSpinBox->text();

    //open city selection window
    int originIndex=0;
    int destIndex=0;
    CitySelectionWindow * cityWin = new CitySelectionWindow(&originIndex,&destIndex,this);
    //search origin city
    std::vector<CityInfo> originCitySearchRes = City_Search_API(tripDetails.originCity);
    if(!originCitySearchRes.size())
    {
        //error no city fond
        QMessageBox errorBox;
        errorBox.setIcon(QMessageBox::Critical);
        errorBox.setText("No Origin City was found Please try again");
        errorBox.setWindowTitle("Error");
        errorBox.setStandardButtons(QMessageBox::Ok);
        // Displaying the error message
        errorBox.exec();
        return;
    }
    for(auto const& city:originCitySearchRes)
    {
        cityWin->addOriginCity(city.cityName+","+city.countryCode+",("+city.cityCode+")");
    }
    //search destination city
    std::vector<CityInfo> destCitySearchRes = City_Search_API(tripDetails.destCity);
    if(!destCitySearchRes.size())
    {
        //error no city fond
        QMessageBox errorBox;
        errorBox.setIcon(QMessageBox::Critical);
        errorBox.setText("No Destination City was found Please try again");
        errorBox.setWindowTitle("Error");
        errorBox.setStandardButtons(QMessageBox::Ok);
        // Displaying the error message
        errorBox.exec();
        return;
    }
    for(auto const& city:destCitySearchRes)
    {
        cityWin->addDestCity(city.cityName+","+city.countryCode+",("+city.cityCode+")");
    }
    cityWin->exec();
    while(cityWin->hasFocus());
    cityWin->deleteLater();
    /*get the selected city*/
    this->originCity = originCitySearchRes[originIndex];
    this->destCity = destCitySearchRes[destIndex];

    delete travelInfoWidget;


    originCityFullinfo=getCityInfo(originCity);
    destCityFullinfo=getCityInfo(destCity);
    tabView = new TabViewInfo(&originCityFullinfo,&destCityFullinfo,this);
    this->ui->mainLayout->addWidget(tabView);
    flight_offer_search_API(originCity.cityCode,destCity.cityCode,tripDetails.startDate,tripDetails.numOfAdult.toInt(),tripDetails.numOfChild.toInt(),tripDetails.endDate);
    for(int i =0;i<flight_offers.size();i++)
    {
        FlightInfoWidget *flightWidget = new FlightInfoWidget(originCity.cityName,destCity.cityName,&flight_offers[i],this);
        tabView->addFlightOffer(flightWidget);
    }
    Hotel_List(destCity.cityCode,tripDetails.am_flag, tripDetails.hotelMinRating.toInt());
    Hotel_Search_API(tripDetails.hotelNumOfRooms.toInt(),tripDetails.numOfAdult.toInt(),\
                    tripDetails.startDate,tripDetails.endDate,tripDetails.currencyCode,tripDetails.hotelMaxPrice);
    for(int j=0;j<roomOffers.size();j++)
    {
        hotelsCell *hotelWidget = new hotelsCell(&roomOffers[j],this);
        tabView->addHotelOffer(hotelWidget);
    }
}
/*end Omar Tamer*/


/*Ziad Mohamed*/
CityInfoAll MainWindow::getCityInfo(CityInfo city)
{
    CityInfoAll CityFullinfo;
    CityFullinfo.countryCode=city.countryCode;
    CityFullinfo.cityCode=city.cityCode;
    CityFullinfo.cityName=city.cityName;
    CityFullinfo.lat=city.lat;
    CityFullinfo.lon= city.lon;
    QString baseurl = "https://restcountries.com/v2/alpha/";
    baseurl+=city.countryCode;
    QUrl url(baseurl);

    QNetworkRequest request(url);
    reply = manager.get(request);

    // Busy wait until the reply is ready
    while (!reply->isFinished()) {
        qApp->processEvents(); // Process events to prevent GUI freeze
    }
    QByteArray data = reply->readAll();
    QJsonDocument jsonDocument =QJsonDocument::fromJson(data);
    //QJsonArray data_array = jsonDocument["data"].toArray();
    CityFullinfo.country_name=jsonDocument["name"].toString();
    CityFullinfo.region=jsonDocument["region"].toString();
    CityFullinfo.time_zone=jsonDocument["timezones"].toArray()[0].toString();
    CityFullinfo.flag_pic=jsonDocument["flags"].toObject()["png"].toString();
    CityFullinfo.currency_code=jsonDocument["currencies"].toArray()[0].toObject()["code"].toString();
    CityFullinfo.currency_name=jsonDocument["currencies"].toArray()[0].toObject()["name"].toString();
    CityFullinfo.currency_symbol=jsonDocument["currencies"].toArray()[0].toObject()["symbol"].toString();
    CityFullinfo.first_language_name=jsonDocument["languages"].toArray()[0].toObject()["name"].toString();
    if(jsonDocument["languages"].toArray().size()>1)
    {
       CityFullinfo.second_language_name=jsonDocument["languages"].toArray()[1].toObject()["name"].toString();
    }
    return CityFullinfo;
}
MainWindow::~MainWindow()
{
    delete ui;
}


