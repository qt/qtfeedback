include(../auto.pri)

QT += qml feedback network

SOURCES += tst_qdeclarativefeedback.cpp

DEFINES += SRCDIR=\\\"$$PWD\\\"

OTHER_FILES += \
    data/hapticseffect.qml \
    data/fileeffect.qml \
    data/actuator.qml \
    data/themeeffect.qml \
    data/themeeffect2.qml \
    data/themeeffect3.qml
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
