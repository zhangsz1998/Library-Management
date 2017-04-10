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
    reader_mgmt.cpp

HEADERS  += widget.h \
    searchbar.h \
    toolbutton.h \
    bookexhibition.h \
    bookmanagewindow.h \
    book_mgmt.h \
    messagebox.h\
    reader_mgmt.h

FORMS    += widget.ui

RESOURCES += \
    images.qrc
