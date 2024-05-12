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
    CityInfo(QString,QString,QString);
};

#endif // CITYINFO_H
