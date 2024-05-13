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

#endif // HOTELSEARCH_H
