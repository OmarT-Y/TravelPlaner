#ifndef FLIGHTINFOWIDGET_H
#define FLIGHTINFOWIDGET_H

#include <QWidget>
#include "flight_search.h"
namespace Ui {
class FlightInfoWidget;
}

class FlightInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FlightInfoWidget(QString origin,QString dest,flight_offer* offer,QWidget *parent = nullptr);
    ~FlightInfoWidget();
protected:
    void mousePressEvent(QMouseEvent *event) override;
private:
    QString reservationLink;
    Ui::FlightInfoWidget *ui;
};

#endif // FLIGHTINFOWIDGET_H
