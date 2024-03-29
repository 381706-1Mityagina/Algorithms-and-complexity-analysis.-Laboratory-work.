#-------------------------------------------------
#
# Project created by QtCreator 2019-12-06T12:10:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = AiAS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    avl_tree.cpp \
    intersect.cpp \
    line_segment.cpp \
    main_work.cpp \
    my_vector.cpp \
    segments_generate.cpp \
    sweep_line.cpp \
    sweep_line_avl.cpp \
    qcustomplot.cpp \
    cubic_spline.cpp

HEADERS += \
        mainwindow.h \
    my_vector.h \
    ../AiAS_lab/qcustomplot.h \
    qcustomplot.h \
    my_vector.h \
    cubic_spline.h

FORMS += \
        mainwindow.ui

SUBDIRS += \
    ../AiAS_lab/AiAS_lab.pro
