#ifndef ACTIVITIESCELL_H
#define ACTIVITIESCELL_H

#include <QWidget>
#include "activities_tours.h"
#include <QString>
#include <QDesktopServices>
namespace Ui {
class activitiescell;
}

class activitiescell : public QWidget
{
    Q_OBJECT

public:
    explicit activitiescell(activity *currentActivity,QWidget *parent = nullptr);
    ~activitiescell();
    QString link;

private:
    Ui::activitiescell *ui;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // ACTIVITIESCELL_H
