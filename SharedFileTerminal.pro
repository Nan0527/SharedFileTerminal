#QT += quick
QT += core gui widgets
QT += network
QT += qml quick network multimedia widgets
QT += sql
QT += axcontainer
QT += printsupport
LIBS     += -L../SharedFileTerminal/ -lzint

TEMPLATE = app
TARGET = SharedFileTerminal
INCLUDEPATH += .


CONFIG += c++11

# Input
HEADERS += mainwindow.h qnavigationwidget.h \
    ftpform.h \
    ftpmanager.h \
    qftp.h \
    qurlinfo.h \
    qsearchwidget.h \
    netdatalistenerthread.h \
    sqlite.h \
    sqlite3.h \
    webservicehelp.h \
    files.h \
    PageWidget.h \
    qtransactwidget.h \
    qhistorywidget.h \
    qaboutwidget.h \
    qzint.h \
    zint.h \
    barcode.h
SOURCES += main.cpp mainwindow.cpp qnavigationwidget.cpp \
    ftpform.cpp \
    ftpmanager.cpp \
    qftp.cpp \
    qurlinfo.cpp \
    qsearchwidget.cpp \
    netdatalistenerthread.cpp \
    sqlite.cpp \
    webservicehelp.cpp \
    files.cpp \
    PageWidget.cpp \
    qtransactwidget.cpp \
    qhistorywidget.cpp \
    qaboutwidget.cpp \
    qzint.cpp \
    barcode.cpp

FORMS += \
    ftpform.ui \
    PageWidget.ui

DISTFILES +=

RESOURCES += \
    image.qrc \
    qml.qrc
RC_ICONS=pages.ico
