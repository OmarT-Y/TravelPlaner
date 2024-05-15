#ifndef AMENITIESWINDOWS_H
#define AMENITIESWINDOWS_H

#include <QDialog>

namespace Ui {
class AmenitiesWindows;
}

class AmenitiesWindows : public QDialog
{
    Q_OBJECT

public:
    explicit AmenitiesWindows(QWidget *parent = nullptr);
    ~AmenitiesWindows();

private:
    Ui::AmenitiesWindows *ui;
public:
    explicit AmenitiesWindow(uint64_t* am_flag,QWidget *parent = nullptr);
    ~AmenitiesWindow();
private slots:
    void checkBoxChanged(Qt::CheckState state);
private:
    int findID(QObject* obj);
    Ui::AmenitiesWindow *ui;
    std::vector<QCheckBox*> checkBoxes;
    uint64_t* checkFlag=nullptr;
};

#endif // AMENITIESWINDOWS_H
