load(qt_build_config)

TARGET = qtfeedback_testplugin
QT = core feedback

load(qt_plugin)

DESTDIR = $$QT.feedback.plugins/feedback

INCLUDEPATH += $$QT.feedback.includes

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

target.path += $$[QT_INSTALL_PLUGINS]/feedback
INSTALLS += target
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
