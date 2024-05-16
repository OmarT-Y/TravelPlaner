QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    amenitieswindow.cpp \
    cityinfo.cpp \
    cityselectionwindow.cpp \
    hotelsearch.cpp \
    main.cpp \
    mainwindow.cpp \
    tabviewinfo.cpp \
    travelinfo.cpp

HEADERS += \
    amenitieswindow.h \
    cityinfo.h \
    cityselectionwindow.h \
    hotelsearch.h \
    activities_tours.h \
    flight_search.h \
    mainwindow.h \
    tabviewinfo.h \
    travelinfo.h

FORMS += \
    amenitieswindow.ui \
    cityselectionwindow.ui \
    mainwindow.ui \
    tabviewinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
