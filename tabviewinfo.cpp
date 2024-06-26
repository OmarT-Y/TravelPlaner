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
    ui->originCurrencyLabel->setText("Currency: "+originCityFullInfo->currency_code + " ("+originCityFullInfo->currency_symbol+")");
    ui->originLangLabel->setText("Language: "+ originCityFullInfo->first_language_name );

    QNetworkAccessManager* m_netwManager = new QNetworkAccessManager(this);
    QUrl url(destCityFullInfo->flag_pic);
    QNetworkRequest request(url);
    QNetworkReply* reply = m_netwManager->get(request);
    while (!reply->isFinished()) {
        qApp->processEvents(); // Process events to prevent GUI freeze
    }
    QByteArray jpegData = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(jpegData);
    ui->destFlagLabel->setPixmap(pixmap.scaled(ui->destFlagLabel->width(),ui->destFlagLabel->height(),Qt::KeepAspectRatio));

    url = QUrl(originCityFullInfo->flag_pic);
    request = QNetworkRequest(url);
    reply = m_netwManager->get(request);
    while (!reply->isFinished()) {
        qApp->processEvents(); // Process events to prevent GUI freeze
    }
    jpegData = reply->readAll();
    QPixmap pixmap2;
    pixmap2.loadFromData(jpegData);
    ui->originFlagLabel->setPixmap(pixmap2.scaled(ui->originFlagLabel->width(),ui->originFlagLabel->height(),Qt::KeepAspectRatio));

    QFont font2 = ui->destCountryLabel->font();
    font2.setPointSize(18);
    font2.setBold(true);
    ui->destCountryLabel->setFont(font);
    ui->destCountryLabel->setText(destCityFullInfo->cityName+","+destCityFullInfo->countryCode);
    ui->destCurrencyLabel->setText("Currency: "+destCityFullInfo->currency_code + " ("+destCityFullInfo->currency_symbol+")");
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
void TabViewInfo::addActivity(activitiescell* offer)
{
    ui->activiteisLayout->addWidget(offer);
}
void TabViewInfo::hideFlight()
{
    ui->flightTab->setVisible(false);
    ui->tabWidget->setTabVisible(0,false);
}
void TabViewInfo::hideHotel()
{
    ui->accomodationsTab->setVisible(false);
    ui->tabWidget->setTabVisible(1,false);
}
TabViewInfo::~TabViewInfo()
{
    delete ui;
}
void TabViewInfo::on_pushButton_clicked()
{
    emit resetHomeSig();
}
