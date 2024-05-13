#ifndef ACTIVITIES_TOURS_H
#define ACTIVITIES_TOURS_H
#include <QString>
#include <vector>
class activity
{
public:
    std::vector <QString> pictures;
    QString name;
    QString description;
    QString price;
    QString currency;
    QString booking_link;
    QString duration_hours;
};



#endif // ACTIVITIES_TOURS_H
