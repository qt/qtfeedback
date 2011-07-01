QT.feedback.VERSION = 5.0.0
QT.feedback.MAJOR_VERSION = 5
QT.feedback.MINOR_VERSION = 0
QT.feedback.PATCH_VERSION = 0

QT.feedback.name = QtFeedback
QT.feedback.bins = $$QT_MODULE_BIN_BASE
QT.feedback.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtFeedback
QT.feedback.private_includes = $$QT_MODULE_INCLUDE_BASE/QtFeedback/$$QT.feedback.VERSION
QT.feedback.sources = $$QT_MODULE_BASE/src/feedback
QT.feedback.libs = $$QT_MODULE_LIB_BASE
QT.feedback.plugins = $$QT_MODULE_PLUGIN_BASE
QT.feedback.imports = $$QT_MODULE_IMPORT_BASE
QT.feedback.depends = core
QT.feedback.DEFINES = QT_FEEDBACK_LIB

QT_CONFIG += feedback
