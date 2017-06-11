#-------------------------------------------------
#
# Project created by QtCreator 2017-03-06T16:22:50
#
#-------------------------------------------------

QT       += core gui
QT       +=xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibraryTest
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    searchbar.cpp \
    toolbutton.cpp \
    bookexhibition.cpp \
    bookmanagewindow.cpp \
    book_mgmt.cpp \
    messagebox.cpp\
    reader_mgmt.cpp \
    bookinfowindow.cpp \
    authoritycheckwindow.cpp \
    getreasonwindow.cpp \
    loginwindow.cpp \
    signupwindow.cpp \
    borrowform.cpp \
    personalinfowindow.cpp \
    messagewidget.cpp \
    resvform.cpp \
    returnwindow.cpp \
    bookhandlewindow.cpp \
    rechargewindow.cpp \
    readersearchwindow.cpp \
    bookoverviewwindow.cpp \
    label.cpp \
    reportreasonwindow.cpp

HEADERS  += widget.h \
    searchbar.h \
    bookexhibition.h \
    bookmanagewindow.h \
    book_mgmt.h \
    messagebox.h\
    reader_mgmt.h \
    bookinfowindow.h \
    authoritycheckwindow.h \
    getreasonwindow.h \
    loginwindow.h \
    signupwindow.h \
    borrowform.h \
    personalinfowindow.h \
    messagewidget.h \
    resvform.h \
    returnwindow.h \
    toolbutton.h \
    bookhandlewindow.h \
    rechargewindow.h \
    readersearchwindow.h \
    bookoverviewwindow.h \
    label.h \
    reportreasonwindow.h

FORMS    += widget.ui

RESOURCES += \
    images.qrc
RC_ICONS = myicon.ico
