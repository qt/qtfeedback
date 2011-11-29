include(../auto.pri)

QT += feedback

SOURCES += tst_qfeedbackactuator.cpp

symbian|linux-g++-maemo:DEFINES += HAVE_ACTUATORS
