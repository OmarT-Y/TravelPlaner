#include "hotelscell.h"
#include "ui_hotelscell.h"

hotelsCell::hotelsCell(HotelRoomOfferInfo *currentHotel,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::hotelsCell)
{
    ui->setupUi(this);
    ui->hotelNamePriceLabel->setText("Hotel: "+ currentHotel->hotelName + " ,Price: "+currentHotel->price+" "+currentHotel->currencyCode);
    QString text2 = "";
    if(currentHotel->payment_type.size())
    {
        text2+="Payment: "+currentHotel->payment_type;
    }
    text2+=", for: "+QString::number(currentHotel->numOf_rooms)+" Rooms";
    ui->roomsLeftLabel->setText(text2);
    QFont font = ui->hotelNamePriceLabel->font();
    font.setPointSize(10);
    font.setBold(true);
    ui->hotelNamePriceLabel->setFont(font);
    QFont font2 = ui->roomsLeftLabel->font();
    font2.setPointSize(10);
    font2.setBold(true);
    ui->roomsLeftLabel->setFont(font2);
    ui->offerDescriptionLabel->setText("Description: "+currentHotel->offer_description);
    QString text="";
    if(currentHotel->boardType.size())
    {
        text+=currentHotel->boardType+" ";
    }
    if(currentHotel->roomCategory.size())
    {
        text+=currentHotel->roomCategory+" ";
    }
    text += QString::number(currentHotel->numOf_beds)+" "+currentHotel->bedtype;
    text+= " bed";
    ui->bedsperroomandTypeLabel->setText(text);

    if(currentHotel->taxAmount.size())
    {
        ui->taxLabel->setText("Tax: "+currentHotel->taxAmount+" not included");
        ui->taxLabel->setAlignment(Qt::AlignRight);
    }
    else if(currentHotel->taxPer.size())
    {
        ui->taxLabel->setText("Tax: "+currentHotel->taxPer+"% not included");
        ui->taxLabel->setAlignment(Qt::AlignRight);
    }
    else
    {
        ui->taxLabel->setVisible(false);
    }
    link = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
}
void hotelsCell::mousePressEvent(QMouseEvent *event)
{
    QDesktopServices::openUrl(QUrl(link));
}
hotelsCell::~hotelsCell()
{
    delete ui;
}
