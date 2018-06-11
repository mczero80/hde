/****************************************************************************
 **
 **				libhde.h
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2006 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  Some base functions for libhde.
 **
 ****************************************************************************/
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <X11/Xos.h>

#ifndef HDESTYLE_H
#define HDESTYLE_H

#include <stdlib.h>
#include <qstring.h>
#include <qtextcodec.h>
#include <qpixmap.h>
//#include "hinifile.h"

// Render string for encoding
QString render(QString s, char *coding);
QString render(QString s, QString coding);
// Get config file
QString get_cfile(char *name);

// get Image file
QString get_ifile(QString name, QString size);
QString get_ifile(QString name, QString size, QString type);

// Get Encoding from locale
QString hde_langinfo(QString lng);

// Execute command
void execCmd(QString cmd);

// Get Opposite Color
QColor getOppositeColor(const QColor &color);

// Draw gradiant
void gradient(QPixmap &pixmap, const QColor &ca, const QColor &cb);
void makeTray(WId win);
QString getIconFile(QString icn, const char *size);
QString getIconFile(QString icn, const char *size, const char *type);

#endif
