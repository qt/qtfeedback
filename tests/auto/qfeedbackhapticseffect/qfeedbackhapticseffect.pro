include(../auto.pri)

QMAKE_LIBS += -Wl,-rpath,$${QT.feedback.libs}

QT += feedback

SOURCES += tst_qfeedbackhapticseffect.cpp
