TEMPLATE = subdirs
SUBDIRS += \
    qfeedbackactuator \
    qfeedbackhapticseffect \
    qfeedbackplugin \
    qfeedbackmmk \
    qdeclarativefeedback \
    cmake

!qtHaveModule(qml): SUBDIRS -= \
    qdeclarativefeedback \

!qtHaveModule(multimedia): SUBDIRS -= \
    qfeedbackmmk \

