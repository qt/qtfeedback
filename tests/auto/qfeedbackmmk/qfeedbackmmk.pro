include(../auto.pri)

QT += feedback

SOURCES += tst_qfeedbackmmk.cpp

maemo* {
    DEFINES += QT_QFEEDBACKMMK_USEAPPLICATIONPATH
} else {
    DEFINES += SRCDIR=\\\"$$PWD/\\\"
}

linux-*:system(". /etc/lsb-release && [ $DISTRIB_CODENAME = oneiric ]"):CONFIG += insignificant_test   # QTBUG-25448
win32: CONFIG += insignificant_test # QTBUG-25448
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
