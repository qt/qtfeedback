load(qt_build_config)

TARGET = qtfeedback_meegotouch
QT = core feedback

load(qt_plugin)

DESTDIR = $$QT.feedback.plugins/feedback

HEADERS += qfeedback.h
SOURCES += qfeedback.cpp

INCLUDEPATH += $$QT.feedback.includes

LIBS += -lmeegotouchcore

target.path += $$[QT_INSTALL_PLUGINS]/feedback
INSTALLS += target
