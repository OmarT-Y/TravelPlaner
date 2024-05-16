#include "flightinfowidget.h"
#include "ui_flightinfowidget.h"
#include <QDesktopServices>
FlightInfoWidget::FlightInfoWidget(QString origin,QString dest,flight_offer* offer,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FlightInfoWidget)
{
    //set airline and price
    ui->setupUi(this);
    ui->airLinePriceLabel->setText("Air Line:"+offer->airline+","+" Total Amount:"+offer->price);
    QFont font = ui->airLinePriceLabel->font();
    font.setPointSize(9);
    font.setBold(true);
    ui->airLinePriceLabel->setFont(font);
    //set offer end date and seat count
    ui->bookingLimitLabel->setText("Available Untill:"+offer->lastingTickitingDate+", "+QString::number(offer->numberOfSeatsLeft)+" Seats Left");
    ui->bookingLimitLabel->setAlignment(Qt::AlignRight);
    QFont font2 = ui->bookingLimitLabel->font();
    font2.setPointSize(9);
    font2.setBold(true);
    ui->bookingLimitLabel->setFont(font);
    //set the first trip
    ui->trip1FromLabel->setText("From: "+origin+", At: "+offer->flights.first.departureDateTime);
    ui->trip1ToLabel->setText("To: "+dest+", At: "+offer->flights.first.arrivalDateTime);
    if(offer->flights.first.numberOfStops)
        ui->trip1StopsLabel->setText(QString::number(offer->flights.first.numberOfStops)+"Stops: "+QString::number(offer->flights.first.numberOfStops));
    else
        ui->trip1StopsLabel->setVisible(false);
    //set the second trip
    if(offer->oneWay == false)
    {
        ui->trip2FromLabel->setText("From: "+origin+", At: "+offer->flights.second.departureDateTime);
        ui->trip2ToLabel->setText("To: "+dest+", At: "+offer->flights.second.arrivalDateTime);
        if(offer->flights.second.numberOfStops)
            ui->trip2StopsLabel->setText("Stops: "+QString::number(offer->flights.second.numberOfStops));
        else
            ui->trip2StopsLabel->setVisible(false);
    }
    else
    {
        ui->trip2StopsLabel->setVisible(false);
        ui->trip2ToLabel->setVisible(false);
        ui->trip2FromLabel->setVisible(false);
    }
    this->reservationLink="https://www.youtube.com/watch?v=Wqu22Kw1XG8";
}
void FlightInfoWidget::mousePressEvent(QMouseEvent *event)
{
    QDesktopServices::openUrl(QUrl(this->reservationLink));
}
FlightInfoWidget::~FlightInfoWidget()
{
    delete ui;
}
