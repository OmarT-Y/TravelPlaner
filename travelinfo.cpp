#include "travelinfo.h"
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
    this->mainWidgetLayout->addWidget(welcomeLabel);
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

    hbox2->addLayout(formLayout1);
    hbox2->addLayout(formLayout2);
    mainWidgetLayout->addLayout(hbox2);


}
