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

class CityInfoAll  : public CityInfo
{
public:
    QString country_name;
    QString region;
    //QString population_of_country;
    QString time_zone;
    QString flag_pic;
    QString first_language_name;
    QString second_language_name;
    QString currency_code;
    QString currency_name;
    QString currency_symbol;
};

#endif // CITYINFO_H
