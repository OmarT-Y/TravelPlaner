#include "tabviewinfo.h"
#include "ui_tabviewinfo.h"

TabViewInfo::TabViewInfo(CityInfoAll* originCityFullInfo,CityInfoAll* destCityFullInfo,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TabViewInfo)
{
    ui->setupUi(this);
    QFont font = ui->originCountryLabel->font();
    font.setPointSize(18);
    font.setBold(true);
    ui->originCountryLabel->setFont(font);
    ui->originCountryLabel->setText(originCityFullInfo->cityName+","+originCityFullInfo->countryCode);
    ui->originCurrencyLabel->setText("Currency: "+ originCityFullInfo->currency_name +"-"+originCityFullInfo->currency_code + " ("+originCityFullInfo->currency_symbol+")");
    ui->originLangLabel->setText("Language: "+ originCityFullInfo->first_language_name );

    // QString imageUrl = originCityFullInfo->flag_pic;

    // // Create a network manager to handle the network requests
    // QNetworkAccessManager manager;

    // // Send a GET request to download the image
    // QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(imageUrl)));

    // // Connect the finished signal to a lambda function to handle the response
    // QObject::connect(reply, &QNetworkReply::finished, [&]() {
    //     if (reply->error() == QNetworkReply::NoError) {
    //         // Read the downloaded data
    //         QByteArray imageData = reply->readAll();
    //         // Create a QImage from the image data
    //         QImage image;
    //         if (image.loadFromData(imageData)) {
    //             // Set the image to the label
    //             ui->originFlagLabel->setPixmap(QPixmap::fromImage(image));
    //         } else {
    //             // Handle error if any
    //             qDebug() << "Error loading image from data";
    //         }
    //     } else {
    //         // Handle error if any
    //         qDebug() << "Error downloading image:" << reply->errorString();
    //     }
    //     // Clean up
    //     reply->deleteLater();
    // });



    QFont font2 = ui->destCountryLabel->font();
    font2.setPointSize(18);
    font2.setBold(true);
    ui->destCountryLabel->setFont(font);
    ui->destCountryLabel->setText(destCityFullInfo->cityName+","+destCityFullInfo->countryCode);
    ui->destCurrencyLabel->setText("Currency: "+ destCityFullInfo->currency_name +"-"+destCityFullInfo->currency_code + " ("+destCityFullInfo->currency_symbol+")");
    ui->destlangLabel->setText("Language: "+ destCityFullInfo->first_language_name );
}
void TabViewInfo::addFlightOffer(FlightInfoWidget* offer)
{
    ui->flightLayout->addWidget(offer);
}
void TabViewInfo::addHotelOffer(hotelsCell* offer)
{
    ui->accomodationLayout->addWidget(offer);
}
// void TabViewInfo::addActivity(ActivityInfoWidget* offer)
// {
//     ui->activiteisLayout->addWidget(offer);
// }
TabViewInfo::~TabViewInfo()
{
    delete ui;
}
