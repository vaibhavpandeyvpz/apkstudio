# Setting up QMake flags for sub-dir template
CONFIG += ordered
TEMPLATE = subdirs

# Directory names (in build order) of sub-projects to be built
SUBDIRS = resources helpers components windows

# Finally, add the main executable project to build
SUBDIRS += application
