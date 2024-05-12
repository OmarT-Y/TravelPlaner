#ifndef FLIGHT_SEARCH_H
#define FLIGHT_SEARCH_H
#include <QString>
class flight
{
public:
    QString departureDateTime;
    QString arrivalDateTime;
    QString duration;
    int numberOfStops;
};

class flight_offer
{
public:
    bool oneWay;
    int numberOfSeatsLeft;
    QString flightSource;
    QString lastingTickitingDate;
    QString price;
    std::pair <flight,flight> flights;

};

#endif // FLIGHT_SEARCH_H
