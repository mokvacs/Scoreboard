QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buzzerwidget.cpp \
    colourselectorwidget.cpp \
    configeditordialog.cpp \
    configmanager.cpp \
    controlitemwithshortcut.cpp \
    controlwidget.cpp \
    customlabel.cpp \
    incrementablelcdnumber.cpp \
    main.cpp \
    mainwindow.cpp \
    periodwidget.cpp \
    scoreboard.cpp \
    shortcutbutton.cpp \
    shortcutrecorderdialog.cpp \
    timeeditdialog.cpp \
    timerwidget.cpp

HEADERS += \
    buzzerwidget.h \
    colourselectorwidget.h \
    configeditordialog.h \
    configmanager.h \
    controlitemwithshortcut.h \
    controlwidget.h \
    customlabel.h \
    incrementablelcdnumber.h \
    mainwindow.h \
    periodwidget.h \
    scoreboard.h \
    shortcutbutton.h \
    shortcutrecorderdialog.h \
    timeeditdialog.h \
    timerwidget.h

FORMS += \
    buzzerwidget.ui \
    configeditordialog.ui \
    controlitemwithshortcut.ui \
    controlwidget.ui \
    mainwindow.ui \
    periodwidget.ui \
    scoreboard.ui \
    shortcutrecorderdialog.ui \
    timeeditdialog.ui \
    timerwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

