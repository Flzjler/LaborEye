#-------------------------------------------------
#
# Project created by QtCreator 2019-10-24T15:44:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LaborEye
TEMPLATE = app

SOURCES += \
    main.cpp

include ($$PWD/MainView/MainView.pri)
include ($$PWD/PreviewView/PreviewView.pri)
include ($$PWD/HistoryView/HistoryView.pri)
include ($$PWD/HouseView/HouseView.pri)
include ($$PWD/StaffView/StaffView.pri)
include ($$PWD/SettingView/SettingView.pri)

include ($$PWD/LaborEyeDatabase/LaborEyeDatabase.pri)
include ($$PWD/Hikvision/Hikvision.pri)
include ($$PWD/Config/Config.pri)

RESOURCES += \
    Src.qrc


