#ifndef HOTELSEARCH_H
#define HOTELSEARCH_H
#include <QString>
QString amenitiesToQString(uint32_t am_flag);
class HotelInfo
{
public:
    HotelInfo();
    QString h_name;
    QString h_ID;
    HotelInfo(QString name, QString id);
};

// class HotelInfoAll  : public HotelInfo
// {
// public:
//     QString bedtype;
//     int number_of_beds;
//     QString hotel_description;
//     QString price;
//     QString payment_type;
//     QString currency_type;
//     QString room_category;
//     QString rate_code;
// };
#endif // HOTELSEARCH_H
