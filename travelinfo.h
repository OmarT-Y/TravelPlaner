#ifndef TRAVELINFO_H
#define TRAVELINFO_H

#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QDateEdit>
#include <QFormLayout>
#include <QCheckBox>
#include <QComboBox>
class TravelInfo : public QWidget
{
    Q_OBJECT
public:
    explicit TravelInfo(QWidget *parent = nullptr);

signals:
private:
    QVBoxLayout *mainWidgetLayout = nullptr;
    QLineEdit *originCitySearch = nullptr;
    QLineEdit *destCitySearch = nullptr;
    QDateEdit *startDate = nullptr;
    QDateEdit *endDate = nullptr;
    QCheckBox *flightCheck = nullptr;
    QCheckBox *hotelCheck = nullptr;
    QComboBox *currencyBox = nullptr;
};

#endif // TRAVELINFO_H
