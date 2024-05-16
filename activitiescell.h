#ifndef ACTIVITIESCELL_H
#define ACTIVITIESCELL_H

#include <QWidget>
#include "activities_tours.h"
namespace Ui {
class activitiescell;
}

class activitiescell : public QWidget
{
    Q_OBJECT

public:
    explicit activitiescell(activity *currentActivity,QWidget *parent = nullptr);
    ~activitiescell();

private:
    Ui::activitiescell *ui;
};

#endif // ACTIVITIESCELL_H
