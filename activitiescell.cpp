#include "activitiescell.h"
#include "ui_activitiescell.h"

activitiescell::activitiescell(activity* currentActivity,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::activitiescell)
{
    ui->setupUi(this);
    ui->textEdit->setMaximumWidth(530);
    ui->textEdit->setReadOnly(true);
    if(currentActivity->price.size())
    {
        ui->namePriceLabel->setText(currentActivity->name +", Price: "+currentActivity->price+ " "+currentActivity->currency);
    }
    else
    {
        ui->namePriceLabel->setText(currentActivity->name);
    }

    if(currentActivity->description.size())
    {
        ui->textEdit->setText(currentActivity->description);
    }
    else
    {
        ui->textEdit->setVisible(false);
    }

    QFont font = ui->namePriceLabel->font();
    font.setPointSize(10);
    font.setBold(true);
    ui->namePriceLabel->setFont(font);
    QFont font2 = ui->hoursLabel->font();
    font2.setPointSize(10);
    font2.setBold(true);
    ui->hoursLabel->setFont(font2);
    if(currentActivity->duration_hours.size())
    {
        ui->hoursLabel->setText("Expected Duration: "+currentActivity->duration_hours);
    }
    else
    {
        ui->hoursLabel->setVisible(false);
    }
    // if(currentActivity->booking_link.size())
    // {
    //     ui->bookingLinkLabel->setText(currentActivity->booking_link);
    //     ui->bookingLinkLabel->setTextFormat(Qt::RichText);
    //     ui->bookingLinkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    //     ui->bookingLinkLabel->setOpenExternalLinks(true);
    // }
    // else
    // {
    //     ui->bookingLinkLabel->setVisible(false);
    // }

}

activitiescell::~activitiescell()
{
    delete ui;
}
