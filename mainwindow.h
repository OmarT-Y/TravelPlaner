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
};
#endif // MAINWINDOW_H
