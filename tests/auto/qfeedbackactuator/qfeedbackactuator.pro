include(../auto.pri)

QMAKE_LIBS += -Wl,-rpath,$${QT.feedback.libs}

QT += feedback

SOURCES += tst_qfeedbackactuator.cpp

symbian|linux-g++-maemo:DEFINES += HAVE_ACTUATORS