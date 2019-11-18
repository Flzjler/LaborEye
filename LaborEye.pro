#-------------------------------------------------
#
# Author: pureZer
# Project created by QtCreator 2019-11-15T20:00:00
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = LaborEye

TEMPLATE = app

SOURCES += \
    main.cpp

# Resourecs files
RESOURCES += \
    Src.qrc

# Sub-modules path
include ($$PWD/MainView/MainView.pri)
include ($$PWD/PreviewView/PreviewView.pri)
include ($$PWD/HistoryView/HistoryView.pri)
include ($$PWD/HouseView/HouseView.pri)
include ($$PWD/StaffView/StaffView.pri)
include ($$PWD/SettingView/SettingView.pri)

include ($$PWD/LaborEyeDatabase/LaborEyeDatabase.pri)
include ($$PWD/Hikvision/Hikvision.pri)
include ($$PWD/Config/Config.pri)
include ($$PWD/Entity/Entity.pri)




