TARGET = qtfeedback_mmk
QT = core feedback multimedia

load(qt_plugin)

DESTDIR = $$QT.feedback.plugins/feedback

HEADERS += qfeedback.h
SOURCES += qfeedback.cpp

symbian: {
    TARGET.EPOCALLOWDLLDATA=1
    TARGET.CAPABILITY = All -Tcb
    TARGET.UID3 = 0x200315FF
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
