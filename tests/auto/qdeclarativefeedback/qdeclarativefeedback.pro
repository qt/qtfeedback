include(../auto.pri)

QMAKE_LIBS += -Wl,-rpath,$${QT.feedback.libs}

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

maemo*:CONFIG += insignificant_test