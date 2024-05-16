#include "activitiescell.h"
#include "ui_activitiescell.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

activitiescell::activitiescell(activity* currentActivity,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::activitiescell)
{
    ui->setupUi(this);
    ui->textEdit->setMaximumWidth(530);
    ui->textEdit->setReadOnly(true);
    ui->namePriceLabel->setText(currentActivity->name);
    if(currentActivity->description.size())
    {
        ui->textEdit->setText(currentActivity->description);
    }
    else
    {
        ui->textEdit->setVisible(false);
    }
    link = currentActivity->booking_link;
    QFont font = ui->namePriceLabel->font();
    font.setPointSize(9);
    font.setBold(true);
    ui->namePriceLabel->setFont(font);
    QFont font2 = ui->hoursLabel->font();
    font2.setPointSize(9);
    font2.setBold(true);
    ui->hoursLabel->setFont(font2);
    QString text="";
    if(currentActivity->duration_hours.size())
    {
        text += "Duration: "+currentActivity->duration_hours+" ,";
    }
    if(currentActivity->price.size())
    {
        text += "Price: "+currentActivity->price+" "+currentActivity->currency;
    }
    if(text.size())
    {
        ui->hoursLabel->setText(text);
    }
    else
    {
        ui->hoursLabel->setVisible(false);
    }
    if(currentActivity->pictures.size())
    {
        QNetworkAccessManager* m_netwManager = new QNetworkAccessManager(this);
        QUrl url(currentActivity->pictures[0]);
        QNetworkRequest request(url);
        QNetworkReply* reply = m_netwManager->get(request);
        while (!reply->isFinished()) {
            qApp->processEvents(); // Process events to prevent GUI freeze
        }
        QByteArray jpegData = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(jpegData);
        ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->width(),ui->imageLabel->height(),Qt::KeepAspectRatio));
    }
    else
    {
        ui->imageLabel->setVisible(false);
    }    if(currentActivity->pictures.size()>1)
    {
        QNetworkAccessManager* m_netwManager = new QNetworkAccessManager(this);
        QUrl url(currentActivity->pictures[1]);
        QNetworkRequest request(url);
        QNetworkReply* reply = m_netwManager->get(request);
        while (!reply->isFinished()) {
            qApp->processEvents(); // Process events to prevent GUI freeze
        }
        QByteArray jpegData = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(jpegData);
        ui->image2Label->setPixmap(pixmap.scaled(ui->image2Label->width(),ui->image2Label->height(),Qt::KeepAspectRatio));
    }
    else
    {
        ui->image2Label->setVisible(false);
    }
}
void activitiescell::mousePressEvent(QMouseEvent *event)
{
    QDesktopServices::openUrl(QUrl(this->link));
}
activitiescell::~activitiescell()
{
    delete ui;
}
