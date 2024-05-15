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
#include <QSpinBox>
#include <QSpacerItem>
#include <QPushButton>
class TravelInfo : public QWidget
{
    Q_OBJECT
signals:
private slots:
    void adultCountChanged();
    void childCoundChanged();
    void AmenitiesButtonClicked();
    void hotelTriggered(Qt::CheckState);
    void flightTriggered(Qt::CheckState);
    void startDateChanged(QDate date);
public:
    explicit TravelInfo(QWidget *parent = nullptr);
    QPushButton *searchButton = nullptr;
    uint64_t am_flag=0;
    QVBoxLayout *mainWidgetLayout = nullptr;
    QLineEdit *originCitySearch = nullptr;
    QLineEdit *destCitySearch = nullptr;
    QDateEdit *startDate = nullptr;
    QDateEdit *endDate = nullptr;
    QCheckBox *flightCheck = nullptr;
    QCheckBox *hotelCheck = nullptr;
    QComboBox *currencyBox = nullptr;
    QSpinBox  *adultnumberspinBox = nullptr;
    QSpinBox  *childrennumberspinBox = nullptr;
    QSpinBox  *flightmaxpriceSpinBox = nullptr;
    QSpinBox  *hotelmaxpriceSpinBox = nullptr;
    QSpinBox  * minimumRatingSpinBox= nullptr;
    QSpinBox  * numberofRoomsSpinBox= nullptr;
    QPushButton *extraAmenitiesButton=nullptr;
};

#endif // TRAVELINFO_H
