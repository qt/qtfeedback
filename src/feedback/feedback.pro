load(qt_module)

TARGET = QtFeedback
QPRO_PWD = $PWD

CONFIG += module

QT = core

DEFINES += QT_BUILD_FEEDBACK_LIB QT_MAKEDLL

load(qt_module_config)

PUBLIC_HEADERS += qfeedbackglobal.h \
                  qfeedbackactuator.h \
                  qfeedbackeffect.h \
                  qfeedbackplugininterfaces.h

PRIVATE_HEADERS += qfeedbackeffect_p.h \
                   qfeedbackplugin_p.h

HEADERS = qtfeedbackversion.h $$PUBLIC_HEADERS $$PRIVATE_HEADERS

SOURCES += qfeedbackactuator.cpp \
           qfeedbackeffect.cpp \
           qfeedbackplugin.cpp

symbian {
    TARGET.EPOCALLOWDLLDATA = 1
    TARGET.CAPABILITY = ALL \
        -TCB

    # UID
    TARGET.UID3 = 0x2002BFCE

    LIBS += -lefsrv

    # Main library
    FEEDBACK_DEPLOYMENT.sources = QtFeedback.dll
    FEEDBACK_DEPLOYMENT.path = /sys/bin
    DEPLOYMENT += FEEDBACK_DEPLOYMENT
    deploy.path = $$EPOCROOT
}
