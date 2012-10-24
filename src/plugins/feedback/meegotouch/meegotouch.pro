TARGET = qtfeedback_meegotouch
QT = core feedback

PLUGIN_TYPE = feedback
load(qt_plugin)

HEADERS += qfeedback.h
SOURCES += qfeedback.cpp

LIBS += -lmeegotouchcore
