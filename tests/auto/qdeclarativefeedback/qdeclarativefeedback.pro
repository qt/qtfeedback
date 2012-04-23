include(../auto.pri)

QT += declarative feedback network script

SOURCES += tst_qdeclarativefeedback.cpp

symbian: {
    importFiles.sources = data
    importFiles.path = .
    DEPLOYMENT += importFiles
} else {
    DEFINES += SRCDIR=\\\"$$PWD\\\"
}

OTHER_FILES += \
    data/hapticseffect.qml \
    data/fileeffect.qml \
    data/actuator.qml \
    data/themeeffect.qml \
    data/themeeffect2.qml \
    data/themeeffect3.qml
