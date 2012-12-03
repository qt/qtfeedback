TARGET = qtfeedback_testplugin2
QT = core feedback

PLUGIN_TYPE = feedback
load(qt_plugin)

CONFIG += testplugin

HEADERS += qfeedbacktestplugin.h
SOURCES += qfeedbacktestplugin.cpp

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
