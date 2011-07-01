TEMPLATE = subdirs
SUBDIRS += qfeedbackactuator \
           qfeedbackhapticseffect \
           qfeedbackplugin \
           qfeedbacknoplugins

# this is the same condition that enables the mmk plugin
equals(QT_MAJOR_VERSION, 4) : greaterThan(QT_MINOR_VERSION, 6):contains(mobility_modules,multimedia): SUBDIRS += qfeedbackmmk

contains(QT_CONFIG, declarative) {
    SUBDIRS += qdeclarativefeedback
}

