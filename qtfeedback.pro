TEMPLATE = subdirs
CONFIG += ordered

module_qtfeedback_src.subdir = src
module_qtfeedback_src.target = module-qtfeedback-src

module_qtfeedback_tests.subdir = tests
module_qtfeedback_tests.target = module-qtfeedback-tests
module_qtfeedback_tests.depends = module_qtfeedback_src
!contains(QT_BUILD_PARTS,tests) {
    module_qtfeedback_tests.CONFIG = no_default_target no_default_install
}

SUBDIRS += module_qtfeedback_src \
           module_qtfeedback_tests
