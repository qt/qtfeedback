load(qt_module)

TARGET = QtFeedback
QPRO_PWD = $PWD

CONFIG += module
MODULE_PRI = ../../modules/qt_feedback.pri

QT = core gui network

DEFINES += QT_BUILD_FEEDBACK_LIB QT_MAKEDLL

load(qt_module_config)

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
