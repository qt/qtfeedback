TEMPLATE = subdirs
SUBDIRS += \
    qfeedbackactuator \
    qfeedbackhapticseffect \
    qfeedbackplugin \
    qfeedbackmmk \
    qdeclarativefeedback \
    cmake

!contains(QT_CONFIG, qml): SUBDIRS -= \
    qdeclarativefeedback \

!contains(QT_CONFIG, multimedia): SUBDIRS -= \
    qfeedbackmmk \

