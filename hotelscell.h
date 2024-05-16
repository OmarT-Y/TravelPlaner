#ifndef HOTELSCELL_H
#define HOTELSCELL_H

#include <QWidget>
#include "hotelsearch.h"
#include <QDesktopServices>
namespace Ui {
class hotelsCell;
}

class hotelsCell : public QWidget
{
    Q_OBJECT

public:
    explicit hotelsCell(HotelRoomOfferInfo *currentHotel,QWidget *parent = nullptr);
    ~hotelsCell();
    QString link;
private:
    Ui::hotelsCell *ui;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // HOTELSCELL_H
