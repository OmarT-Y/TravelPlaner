#include "hotelscell.h"
#include "ui_hotelscell.h"

hotelsCell::hotelsCell(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::hotelsCell)
{
    ui->setupUi(this);
}

hotelsCell::~hotelsCell()
{
    delete ui;
}
