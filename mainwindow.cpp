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
    request.setRawHeader("Authorization", "Bearer i3kRQQ1tKfM9183Fvi50bE3w3wNFhlRK");

    reply = manager.get(request);

    // Busy wait until the reply is ready
    while (!reply->isFinished()) {
        qApp->processEvents(); // Process events to prevent GUI freeze
    }

    QByteArray data = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonObject data_ = json["data"].toObject();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->reqData();
}

