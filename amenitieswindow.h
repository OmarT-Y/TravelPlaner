#ifndef AMENITIESWINDOW_H
#define AMENITIESWINDOW_H

#include <QDialog>
#include <QCheckBox>
namespace Ui {
class AmenitiesWindow;
}

class AmenitiesWindow : public QDialog
{
    Q_OBJECT

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

#endif // AMENITIESWINDOW_H
