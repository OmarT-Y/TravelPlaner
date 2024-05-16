#include "hotelscell.h"
#include "ui_hotelscell.h"

hotelsCell::hotelsCell(HotelRoomOfferInfo *currentHotel,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::hotelsCell)
{
    ui->setupUi(this);
    ui->hotelNamePriceLabel->setText("Hotel: "+ currentHotel->hotelName + " Price: "+currentHotel->price+" "+currentHotel->currencyCode + " "+currentHotel->payment_type);
    ui->roomsLeftLabel->setText("Rooms Left: "+QString::number(currentHotel->numOf_rooms));
    QFont font = ui->hotelNamePriceLabel->font();
    font.setPointSize(10);
    font.setBold(true);
    ui->hotelNamePriceLabel->setFont(font);
    QFont font2 = ui->roomsLeftLabel->font();
    font2.setPointSize(10);
    font2.setBold(true);
    ui->roomsLeftLabel->setFont(font2);
    ui->offerDescriptionLabel->setText("Description: "+currentHotel->offer_description);
    ui->bedsperroomandTypeLabel->setText("Room Type: "+currentHotel->roomCategory+" Number of beds: "+QString::number(currentHotel->numOf_beds) + " Bed Type: "+currentHotel->bedtype);
}

hotelsCell::~hotelsCell()
{
    delete ui;
}
