#include "amenitieswindow.h"
#include "ui_amenitieswindow.h"
#include "hotelsearch.h"
#include <QLayout>
AmenitiesWindow::AmenitiesWindow(uint64_t* am_flag,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AmenitiesWindow)
{
    ui->setupUi(this);
    checkFlag = am_flag;
    QVBoxLayout *vbox1 = new QVBoxLayout(this);
    QVBoxLayout *vbox2 = new QVBoxLayout(this);
    for(int i=0;i<amenities.size()-1;i++)
    {
        QCheckBox *check = new QCheckBox(amenities[i],this);
        if(i&1)
            vbox1->addWidget(check);
        else
            vbox2->addWidget(check);

        if((*am_flag)&(1<<i))
            check->setCheckState(Qt::Checked);
        else
            check->setCheckState(Qt::Unchecked);

        connect(check,SIGNAL(checkStateChanged(Qt::CheckState)),this,SLOT(checkBoxChanged(Qt::CheckState)));
        checkBoxes.push_back(check);
    }
    if(amenities.size()%2==0)
    {
        QCheckBox *check = new QCheckBox(amenities[amenities.size()-1],this);
        vbox1->addWidget(check);
        ui->horizontalLayout->addLayout(vbox1);
        ui->horizontalLayout->addLayout(vbox2);
    }
    else
    {
        QCheckBox *check = new QCheckBox(amenities[amenities.size()-1],this);
        ui->horizontalLayout->addLayout(vbox1);
        ui->horizontalLayout->addLayout(vbox2);
        ui->verticalLayout_2->addWidget(check);
    }

}
int AmenitiesWindow::findID(QObject* obj)
{
    for(int i =0;i<checkBoxes.size();i++)
        if(obj==checkBoxes[i])return i;
    return -1;
}
void AmenitiesWindow::checkBoxChanged(Qt::CheckState state)
{
    int checkBoxID = findID(this->sender());
    if(checkBoxID != -1)
    {
        if(state==Qt::Checked)
        {
            (*checkFlag) |= 1<<checkBoxID;
        }
        else
        {
            (*checkFlag) &= ~(1<<checkBoxID);
        }
    }
}
AmenitiesWindow::~AmenitiesWindow()
{
    delete ui;
}
