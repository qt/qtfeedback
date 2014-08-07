TARGET = QtFeedback
QT = core

QMAKE_DOCS = $$PWD/../../doc/qtfeedback.qdocconf

MODULE_PLUGIN_TYPES = \
    feedback

load(qt_module)

PUBLIC_HEADERS += qfeedbackglobal.h \
                  qfeedbackactuator.h \
                  qfeedbackeffect.h \
                  qfeedbackplugininterfaces.h \
                  qfeedbackpluginsearch.h

PRIVATE_HEADERS += qfeedbackeffect_p.h \
                   qfeedbackplugin_p.h

HEADERS =  $$PUBLIC_HEADERS $$PRIVATE_HEADERS

SOURCES += qfeedbackactuator.cpp \
           qfeedbackeffect.cpp \
           qfeedbackplugin.cpp
