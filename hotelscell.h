#ifndef HOTELSCELL_H
#define HOTELSCELL_H

#include <QWidget>

namespace Ui {
class hotelsCell;
}

class hotelsCell : public QWidget
{
    Q_OBJECT

public:
    explicit hotelsCell(QWidget *parent = nullptr);
    ~hotelsCell();

private:
    Ui::hotelsCell *ui;
};

#endif // HOTELSCELL_H
