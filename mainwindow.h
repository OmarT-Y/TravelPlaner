#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include "flight_search.h"
#include "activities_tours.h"
#include <vector>
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
    void flight_offer_search_API(QString originLocationCode , QString destinationLocationCode , QString departureDate ,int adults , int children,QString returnDate, QString currency,QString amount  );
    void get_Tours_Activities(QString latitude , QString longitude );
    QString getAirline(QString code);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
    QNetworkReply *reply = nullptr;
    QString amadeusKey;
    std::vector <flight_offer> flight_offers;
    std::vector <activity> activities;
};
#endif // MAINWINDOW_H
