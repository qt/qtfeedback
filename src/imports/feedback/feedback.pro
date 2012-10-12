QT = core qml feedback

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

load(qml_plugin)
