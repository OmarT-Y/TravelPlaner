#include "cityinfo.h"

CityInfo::CityInfo() {}
CityInfo::CityInfo(QString name,QString code,QString country,QString lon,QString lat) {
    this->cityCode=code;
    this->cityName=name;
    this->countryCode=country;
    this->lat = lat;
    this->lon = lon;
}
