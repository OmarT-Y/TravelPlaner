#ifndef ACTIVITIESCELL_H
#define ACTIVITIESCELL_H

#include <QWidget>
#include "activities_tours.h"
#include <QString>
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
};

#endif // ACTIVITIESCELL_H
