include(../auto.pri)

QMAKE_LIBS += -Wl,-rpath,$${QT.feedback.libs}

QT += feedback

SOURCES += tst_qfeedbackmmk.cpp

wince*|symbian {
    deploy.files = test.wav
    DEPLOYMENT = deploy
    DEFINES += QT_QFEEDBACKMMK_USEAPPLICATIONPATH
} else:maemo* {
    DEFINES += QT_QFEEDBACKMMK_USEAPPLICATIONPATH
} else {
    DEFINES += SRCDIR=\\\"$$PWD/\\\"
}

mac:qpa:CONFIG += insignificant_test    # quicktime qtmultimedia backend is disabled for now
maemo*:CONFIG += insignificant_test
