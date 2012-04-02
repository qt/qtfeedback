TEMPLATE = subdirs

# Feedback API examples
contains(mobility_modules, feedback) {
    SUBDIRS += hapticsplayer hapticsquare # this not a good UI for mobile screens at the moment
}


