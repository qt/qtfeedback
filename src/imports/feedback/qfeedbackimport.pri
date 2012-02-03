load(qt_module)

TEMPLATE = lib
CONFIG += qt plugin

win32|mac:!wince*:!win32-msvc:!macx-xcode:CONFIG += debug_and_release

isEmpty(TARGETPATH) {
    error("qimportbase.pri: You must provide a TARGETPATH!")
}

isEmpty(TARGET) {
    error("qimportbase.pri: You must provide a TARGET!")
}

QMLDIRFILE = $${_PRO_FILE_PWD_}/qmldir
copy2build.input = QMLDIRFILE
copy2build.output = $$QT.feedback.imports/$$TARGETPATH/qmldir
!contains(TEMPLATE_PREFIX, vc):copy2build.variable_out = PRE_TARGETDEPS
copy2build.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copy2build.name = COPY ${QMAKE_FILE_IN}
copy2build.CONFIG += no_link
# `clean' should leave the build in a runnable state, which means it shouldn't delete qmldir
copy2build.CONFIG += no_clean

# Another qmldir copied to the old import path pointing to the plugin in the new import path.
OLDQMLDIRFILE = $${_PRO_FILE_PWD_}/old/qmldir
oldcopy2build.input = OLDQMLDIRFILE
oldcopy2build.output = $$QT.feedback.imports/$$OLDTARGETPATH/qmldir
!contains(TEMPLATE_PREFIX, vc):oldcopy2build.variable_out = PRE_TARGETDEPS
oldcopy2build.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
oldcopy2build.name = COPY ${QMAKE_FILE_IN}
oldcopy2build.CONFIG += no_link
# `clean' should leave the build in a runnable state, which means it shouldn't delete qmldir
oldcopy2build.CONFIG += no_clean

QMAKE_EXTRA_COMPILERS += copy2build oldcopy2build

TARGET = $$qtLibraryTarget($$TARGET)
contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols

load(qt_targets)
