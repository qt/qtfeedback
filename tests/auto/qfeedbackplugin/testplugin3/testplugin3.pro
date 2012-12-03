TARGET = qtfeedback_testplugin3
QT = core feedback

PLUGIN_TYPE = feedback
load(qt_plugin)

INCLUDEPATH += $$QT.feedback.includes

CONFIG += testplugin

HEADERS += qfeedbacktestplugin.h
SOURCES += qfeedbacktestplugin.cpp

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
