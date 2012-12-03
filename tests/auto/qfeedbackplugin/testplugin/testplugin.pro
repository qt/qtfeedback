TARGET = qtfeedback_testplugin
QT = core feedback

PLUGIN_TYPE = feedback
load(qt_plugin)

HEADERS += qfeedbacktestplugin.h
SOURCES += qfeedbacktestplugin.cpp

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
