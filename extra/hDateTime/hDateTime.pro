TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

HEADERS  +=  configdlg.h
SOURCES  +=  main.cpp configdlg.cpp

TARGET   =   hDateTime

TRANSLATIONS    = ../../files/lng/hdatetime_ar.ts \
                  ../../files/lng/hdatetime_nl.ts \
                  ../../files/lng/hdatetime_es.ts \
                  ../../files/lng/hdatetime_fr.ts \
                  ../../files/lng/hdatetime_tr.ts

INCLUDEPATH += ../../include
LIBS		+= -L../../lib -lhde2
