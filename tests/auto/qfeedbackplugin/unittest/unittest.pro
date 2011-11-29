include(../../auto.pri)

QT += feedback

SOURCES += tst_qfeedbackplugin.cpp

symbian|linux-g++-maemo:DEFINES += HAVE_ACTUATORS
