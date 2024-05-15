#ifndef HOTELSEARCH_H
#define HOTELSEARCH_H
#include <QString>
QString amenitiesToQString(uint64_t am_flag);
extern std::vector<QString> amenities;
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
