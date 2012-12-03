include(../auto.pri)

QT += feedback

SOURCES += tst_qfeedbackactuator.cpp

linux-g++-maemo:DEFINES += HAVE_ACTUATORS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
