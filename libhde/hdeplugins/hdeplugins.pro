TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on release plugin designer

INCLUDEPATH	+= $$QT_SOURCE_TREE/tools/designer/interfaces

HEADERS	+= plugin.h \
	defaults.h \
	../../include/hcloseframe.h \
	../../include/hcalender.h \
	../../include/hclock.h \
	../../include/HIniFile.h \
	../../include/qhijri.h \
	../../include/libhde.h \
	../../include/hmime.h \
	../../include/hfilewidget.h \
	../../include/hfilelist.h \
	../../include/mycomputer.h \
	../../include/himagevw.h

#	../../include/hdirlist.h \

#FORMS +=     ../himagevw.ui

SOURCES	+= plugin.cpp \
	defaults.cpp \
	../hcloseframe.cpp \
	../hclock.cpp \
	../hcalender.cpp \
	../HIniFile.cpp \
	../qhijri.cpp \
	../libhde.cpp \
	../hmime.cpp \
	../hfilewidget.cpp \
	../hfilelist.cpp \
	../mycomputer.cpp \
	../himagevw.cpp

#	../hdirlist.cpp \


TARGET   = hdeplugins

RESOURCES     = hdeplugins.qrc

win32{
DESTDIR   = $(QTDIR)/plugins/designer

target.path=$$plugins.path

INSTALLS    += target
}
INCLUDEPATH += ../../include

