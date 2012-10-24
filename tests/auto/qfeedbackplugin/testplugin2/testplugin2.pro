TARGET = qtfeedback_testplugin2
QT = core feedback

PLUGIN_TYPE = feedback
load(qt_plugin)

CONFIG += testplugin

HEADERS += qfeedbacktestplugin.h
SOURCES += qfeedbacktestplugin.cpp

symbian: {
    TARGET.EPOCALLOWDLLDATA=1
    TARGET.CAPABILITY = All -Tcb
    TARGET = $${TARGET}$${QT_LIBINFIX}
    load(armcc_warnings)

    target.path = /sys/bin
    INSTALLS += target

    symbianplugin.sources = $${TARGET}.dll
    symbianplugin.path = $${QT_PLUGINS_BASE_DIR}/$${PLUGIN_TYPE}
    DEPLOYMENT += symbianplugin
}

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
