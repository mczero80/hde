TEMPLATE =  lib
#CONFIG   +=  qt warn_on
CONFIG    += designer qt thread release
win32::CONFIG    += plugin

SUBDIRS += \
	plugins 


RESOURCES     = libhde.qrc

HEADERS  +=  ../include/libhde.h \
	    ../include/lhdeconf.h \
	    ../include/defs.h \
	    ../include/defaults.h \
	    ../include/hinifile.h \
            ../include/qhijri.h \
            ../include/hcloseframe.h \
            ../include/netwm.h \
            ../include/netwm_def.h \
            ../include/netwm_p.h \
            ../include/hclock.h \
            ../include/hdestyle.h \
            ../include/hcalender.h \
            ../include/xdgmenu.h \
            ../include/hmime.h \
            ../include/hfilelist.h \
            ../include/hfilewidget.h \
            ../include/mycomputer.h \
            ../include/himagevw.h
#            ../include/hsynedit.h \
#            ../include/hrichedit.h \
#            ../include/hdirlist.h \


SOURCES  +=  libhde.cpp \
	     defaults.cpp \
             qhijri.cpp \
	     hinifile.cpp \
             hcloseframe.cpp \
             netwm.cpp \
	     hclock.cpp \
	     hcalender.cpp \
	     hdestyle.cpp \
             xdgmenu.cpp \
             mycomputer.cpp \
             hfilelist.cpp \
             hfilewidget.cpp \
             hmime.cpp \
	     himagevw.cpp

#	     hde_tbab.cpp \
#             hsynedit.cpp \
#	     hrichedit.cpp \
#             hdirlist.cpp \
#             mycomputer.cpp

#FORMS +=     himagevw.ui

unix {
  HEADERS += ../include/smenuitem.h \
            ../include/startmenu.h 

  SOURCES += smenuitem.cpp \
             startmenu.cpp
  VERSION = $$(LVERSION)
}


TRANSLATIONS    = ../files/lng/libhde_ar.ts \
                  ../files/lng/libhde_nl.ts \
                  ../files/lng/libhde_fr.ts \
                  ../files/lng/libhde_es.ts \
                  ../files/lng/libhde_tr.ts


TARGET   =  hde2

target.path=$$plugins.path
isEmpty(target.path):target.path=$$QT_PREFIX/plugins
INSTALLS    += target 
DEFINES += HCLOSEFRAME_IS_WIDGET


DESTDIR	 =  ../lib
INCLUDEPATH += ../include
LANGUAGE	= C++

DEFINES += QT_CLEAN_NAMESPACE
win32::CONFIG    += staticlib
