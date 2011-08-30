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
# Module dependencies.
# Every module that is required to build this module should have one entry.
# Each of the module version specifiers can take one of the following values:
#   - A specific Git revision.
#   - any git symbolic ref resolvable from the module's repository (e.g. "refs/heads/master" to track master branch)
#
%dependencies = (
    "qtbase" => "refs/heads/master",
    "qtsvg" => "refs/heads/master",
    "qtxmlpatterns" => "refs/heads/master",
    "qtdeclarative" => "refs/heads/master",
    "qtmultimediakit" => "refs/heads/master",
);
