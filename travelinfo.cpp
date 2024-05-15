#include "travelinfo.h"
#include "amenitieswindow.h"
TravelInfo::TravelInfo(QWidget *parent)
    : QWidget{parent}
{
    this->mainWidgetLayout = new QVBoxLayout(this);
    /*set welcome label*/
    QLabel *welcomeLabel = new QLabel("Welcome to TripTactics! Your guide for an unforgettable journey",this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    QFont font = welcomeLabel->font();
    font.setPointSize(18);
    font.setBold(true);
    welcomeLabel->setFont(font);
    mainWidgetLayout->addWidget(welcomeLabel);
    QSpacerItem *mainlayoutSpacer2 = new QSpacerItem(0,30,QSizePolicy::Fixed,QSizePolicy::Fixed);
    mainWidgetLayout->addSpacerItem(mainlayoutSpacer2);
    /*city and date selection*/
    QFormLayout *formLayout1 = new QFormLayout(this);
    QFormLayout *formLayout2 = new QFormLayout(this);
    /*set city selection*/
    QLabel *originCityLabel = new QLabel("From:",this);
    QLabel *destCityLabel = new QLabel("To:",this);
    this->destCitySearch = new QLineEdit(this);
    this->destCitySearch->setPlaceholderText("Destination City");
    this->originCitySearch = new QLineEdit(this);
    this->originCitySearch->setPlaceholderText("Origin City");
    formLayout1->addRow(originCityLabel,originCitySearch);
    formLayout2->addRow(destCityLabel,destCitySearch);
    /*set date selection*/
    QLabel *startDateLabel = new QLabel("Start Date:",this);
    QLabel *endDateLabel = new QLabel("End Date:",this);
    this->startDate = new QDateEdit(QDate::currentDate(),this);
    startDate->setMinimumDate(QDate::currentDate());
    this->endDate = new QDateEdit(QDate::currentDate(),this);
    //TODO:set the minimum of the end date to the start date (slot signal to be update at changes)
    startDate->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    endDate->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    formLayout1->addRow(startDateLabel,startDate);
    formLayout2->addRow(endDateLabel,endDate);
    QHBoxLayout *hbox2 = new QHBoxLayout(this);
    /*adults and children numbers*/
    QLabel *adultNumberLabel = new QLabel("Adult Travelers:",this);
    QLabel *childrenNumberLabel = new QLabel("Child Travelers:",this);
    adultnumberspinBox=new QSpinBox();
    adultnumberspinBox->setMaximum(9);
    childrennumberspinBox=new QSpinBox();
    childrennumberspinBox->setMaximum(9);
    formLayout1->addRow(adultNumberLabel,adultnumberspinBox);
    formLayout2->addRow(childrenNumberLabel,childrennumberspinBox);

    /*set flight details and flights/hotel disable box*/
    flightCheck = new QCheckBox("Disable Flights Planning",this);
    hotelCheck = new QCheckBox("Disable Hotel Planning",this);
    QLabel *currencyLabel = new QLabel("Currency:",this);
    currencyLabel->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    currencyBox = new QComboBox(this);
    currencyBox->addItems({"EGP","EUR","USD"});
    currencyBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    currencyBox->setCurrentIndex(0);
    formLayout1->addRow(currencyLabel,currencyBox);
    QHBoxLayout *hbox3 = new QHBoxLayout(this);
    hbox3->addWidget(flightCheck);
    hbox3->addWidget(hotelCheck);
    formLayout2->addRow(hbox3);
    /* flight & hotel options headers */
    QSpacerItem *verticalSeparator1 = new QSpacerItem(1,30,QSizePolicy::Fixed,QSizePolicy::Fixed);
    QSpacerItem *verticalSeparator2 = new QSpacerItem(1,30,QSizePolicy::Fixed,QSizePolicy::Fixed);
    formLayout1->addItem(verticalSeparator1);
    formLayout2->addItem(verticalSeparator2);
    QLabel *flightoptionheaderLabel = new QLabel("Flight Options",this);
    flightoptionheaderLabel->setAlignment(Qt::AlignCenter);
    flightoptionheaderLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    QFont font2 = flightoptionheaderLabel->font();
    font2.setPointSize(12);
    font2.setBold(true);
    flightoptionheaderLabel->setFont(font2);
    QLabel *hoteloptionheaderLabel = new QLabel("Hotel Options",this);
    hoteloptionheaderLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    hoteloptionheaderLabel->setAlignment(Qt::AlignCenter);
    QFont font3 = hoteloptionheaderLabel->font();
    font3.setPointSize(12);
    font3.setBold(true);
    hoteloptionheaderLabel->setFont(font3);
    formLayout1->addRow(flightoptionheaderLabel);
    formLayout2->addRow(hoteloptionheaderLabel);
    /* actual options of flight & hotel options */
    QLabel *flightpriceLabel = new QLabel("Max Price:");
    QLabel *hotelpriceLabel = new QLabel("Max Price:");
    hotelmaxpriceSpinBox = new QSpinBox(this);
    flightmaxpriceSpinBox = new QSpinBox(this);
    formLayout1->addRow(flightpriceLabel,flightmaxpriceSpinBox);
    formLayout2->addRow(hotelpriceLabel,hotelmaxpriceSpinBox);
    QLabel *minimumratingLabel = new QLabel("Minimum Rating:");
    QLabel *numberofRoomsLabel = new QLabel("Number of Rooms:");
    minimumRatingSpinBox = new QSpinBox(this);
    minimumRatingSpinBox->setMaximum(5);
    numberofRoomsSpinBox = new QSpinBox(this);
    numberofRoomsSpinBox->setMaximum(9);
    formLayout2->addRow(minimumratingLabel,minimumRatingSpinBox);
    formLayout2->addRow(numberofRoomsLabel,numberofRoomsSpinBox);
    searchButton = new QPushButton("Let's Travel!",this);
    extraAmenitiesButton = new QPushButton("Choose Extra Amenities",this);
    formLayout2->addRow(extraAmenitiesButton);
    hbox2->addLayout(formLayout1);
    hbox2->addLayout(formLayout2);
    mainWidgetLayout->addLayout(hbox2);
    QSpacerItem *mainlayoutSpacer = new QSpacerItem(0,30,QSizePolicy::Fixed,QSizePolicy::Expanding);
    mainWidgetLayout->addSpacerItem(mainlayoutSpacer);
    mainWidgetLayout->addWidget(searchButton);


    /*slot connection for limitting the maxmimum travers to 10*/
    connect(adultnumberspinBox,SIGNAL(valueChanged(int)),this,SLOT(adultCountChanged()));
    connect(childrennumberspinBox,SIGNAL(valueChanged(int)),this,SLOT(childCountChanged()));

    /*connect amenities button to its slot*/
    connect(extraAmenitiesButton,SIGNAL(clicked(bool)),this,SLOT(AmenitiesButtonClicked()));
}
void TravelInfo::adultCountChanged()
{
    childrennumberspinBox->setMaximum(9-adultnumberspinBox->value());
}
void TravelInfo::childCoundChanged()
{
    adultnumberspinBox->setMaximum(9-childrennumberspinBox->value());
}
void TravelInfo::AmenitiesButtonClicked()
{
    AmenitiesWindow *amWin = new AmenitiesWindow(&am_flag,this);
    amWin->exec();
    while(amWin->hasFocus());
    amWin->deleteLater();
}
