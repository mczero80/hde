######################################################################
# Automatically generated by qmake (2.01a) Wed Apr 25 22:29:41 2007
######################################################################

TEMPLATE = app
TARGET = hrun
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += hrun.h
FORMS += hrun.ui
SOURCES += hrun.cpp main.cpp

TRANSLATIONS    = ../../files/lng/hrun_ar.ts \
                  ../../files/lng/hrun_nl.ts \
                  ../../files/lng/hrun_es.ts \
                  ../../files/lng/hrun_fr.ts \
                  ../../files/lng/hrun_tr.ts

INCLUDEPATH += ../../include
LIBS		+= -L../../lib -lhde2
