TARGET = qtfeedback_immersion
QT = core feedback

PLUGIN_TYPE = feedback
load(qt_plugin)

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
