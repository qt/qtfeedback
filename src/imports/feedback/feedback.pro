TARGET  = declarative_feedback
TARGETPATH = QtFeedback
include(qfeedbackimport.pri)
target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH
DESTDIR = $$QT.feedback.imports/$$TARGETPATH
INSTALLS += target

qmldir.files += $$PWD/qmldir
qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH
pluginTypes.files += $$PWD/plugins.qmltypes
pluginTypes.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH
INSTALLS += qmldir pluginTypes

QT += qml feedback

HEADERS += qdeclarativehapticseffect_p.h \
           qdeclarativefileeffect_p.h \
           qdeclarativethemeeffect_p.h \
           qdeclarativefeedbackactuator_p.h \
           qdeclarativefeedbackeffect_p.h

SOURCES += qdeclarativehapticseffect.cpp \
           qdeclarativefileeffect.cpp \
           plugin.cpp \
           qdeclarativethemeeffect.cpp \
           qdeclarativefeedbackactuator.cpp \
           qdeclarativefeedbackeffect.cpp
