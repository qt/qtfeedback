%modules = ( # path to module name map
    "QtFeedback" => "$basedir/src/feedback",
);
%moduleheaders = ( # restrict the module headers to those found in relative path
);
%classnames = (
    "qtfeedbackversion.h" => "QtFeedbackVersion",
);
%mastercontent = (
    "feedback" => "#include <QtFeedback/QtFeedback>\n",
);
%modulepris = (
    "QtFeedback" => "$basedir/modules/qt_feedback.pri",
);
# Modules and programs, and their dependencies.
# Each of the module version specifiers can take one of the following values:
#   - A specific Git revision.
#   - "LATEST_REVISION", to always test against the latest revision.
#   - "LATEST_RELEASE", to always test against the latest public release.
#   - "THIS_REPOSITORY", to indicate that the module is in this repository.
%dependencies = (
    "QtFeedback" => {
        "QtCore" => "LATEST_RELEASE",
        "QtDeclarative" => "LATEST_RELEASE",
        "QtGui" => "LATEST_RELEASE",
    },
);
