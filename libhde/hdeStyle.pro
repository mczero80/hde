TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on release plugin

INCLUDEPATH	+= $(QTDIR)/tools/designer/interfaces ../include

HEADERS	+= ../include/hdestyle.h

SOURCES	+= hdestyle.cpp

#DESTDIR   = $QTDIR/plugins/styles
TARGET    = hdeStyle


win32{
DESTDIR   = $(QTDIR)/plugins/styles

target.path=$$plugins.path

#target.path=../lib
#plugins.path
#isEmpty(target.path):target.path=$$QT_PREFIX/plugins
INSTALLS    += target
}
CONFIG += thread

PROJECTNAME  = Plugin


#The following line was inserted by qt3to4
QT +=  qt3support 
