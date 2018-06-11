TEMPLATE = app
TARGET = hde
DEPENDPATH += .
INCLUDEPATH += .

CONFIG	+= thread

# Input
HEADERS += apbar.h \
           atoms.h \
           conf.h \
           dclock.h \
           defs.h \
           desktp.h \
           eventnames.h \
           keyboard.h \
           menu.h \
           pager.h \
           procbar.h \
           qapp.h \
           rubber.h \
           toolbar.h \
           wborder.h \
           winfo.h \
           winlist.h \
           xwindow.h \
           normalmenu.h \
           xpmenu.h \
           vistamenu.h 

SOURCES += apbar.cpp \
           atoms.cpp \
           dclock.cpp \
           desktp.cpp \
           keyboard.cpp \
           main.cpp \
           menu.cpp \
           pager.cpp \
           procbar.cpp \
           qapp.cpp \
           rubber.cpp \
           toolbar.cpp \
           wborder.cpp \
           winfo.cpp \
           winlist.cpp \
           xwindow.cpp\
           normalmenu.cpp \
           xpmenu.cpp \
           vistamenu.cpp

INCLUDEPATH += ../include
LIBS += -L../lib -lhde2


TRANSLATIONS    = ../files/lng/hde_ar.ts \
                  ../files/lng/hde_nl.ts \
                  ../files/lng/hde_fr.ts \
                  ../files/lng/hde_es.ts \
                  ../files/lng/hde_tr.ts

