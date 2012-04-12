load(qt_build_config)

TARGET = qtfeedback_immersion
QT = core feedback

load(qt_plugin)

DESTDIR = $$QT.feedback.plugins/feedback

HEADERS += qfeedback.h
SOURCES += qfeedback.cpp

INCLUDEPATH += $$QT.feedback.includes

LIBS += -limmvibe

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
