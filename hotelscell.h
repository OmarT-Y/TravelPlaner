#ifndef HOTELSCELL_H
#define HOTELSCELL_H

#include <QWidget>
#include "hotelsearch.h"
namespace Ui {
class hotelsCell;
}

class hotelsCell : public QWidget
{
    Q_OBJECT

public:
    explicit hotelsCell(HotelRoomOfferInfo *currentHotel,QWidget *parent = nullptr);
    ~hotelsCell();

private:
    Ui::hotelsCell *ui;
};

#endif // HOTELSCELL_H
