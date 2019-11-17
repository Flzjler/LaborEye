HEADERS += \
    $$PWD/DataType.h \
    $$PWD/DecodeCardSdk.h \
    $$PWD/HCNetSDK.h \
    $$PWD/plaympeg4.h \
    $$PWD/hikvision.h


SOURCES += \
    $$PWD/hikvision.cpp

# Hikvision Camera SDK
LIBS += $$PWD/Library/GdiPlus.lib
LIBS += $$PWD/Library/HCCore.lib
LIBS += $$PWD/Library/HCNetSDK.lib
LIBS += $$PWD/Library/PlayCtrl.lib
