#include "cityinfo.h"

CityInfo::CityInfo() {}
CityInfo::CityInfo(QString name,QString code,QString country) {
    this->cityCode=code;
    this->cityName=name;
    this->countryCode=country;
}
