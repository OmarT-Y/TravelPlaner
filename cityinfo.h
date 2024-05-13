#ifndef CITYINFO_H
#define CITYINFO_H
#include <QString>
class CityInfo
{
public:
    CityInfo();
    QString cityName;
    QString cityCode;
    QString countryCode;
    QString lon;
    QString lat;
    CityInfo(QString name,QString code,QString country,QString lon,QString Lat);
};

#endif // CITYINFO_H
