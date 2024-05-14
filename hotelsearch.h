#ifndef HOTELSEARCH_H
#define HOTELSEARCH_H
#include <QString>
QString amenitiesToQString(uint32_t am_flag);

class HotelRoomOfferInfo
{
public:
    QString hotelName;
    int numOf_rooms;
    QString boardType;
    QString roomCategory;
    QString bedtype;
    int numOf_beds;
    QString offer_description;
    QString currencyCode;
    QString price;
    QString taxPer;
    QString taxAmount;
    QString payment_type;
};
#endif // HOTELSEARCH_H
