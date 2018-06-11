/****************************************************************************
 **
 **				dclock.cpp
 **			=========================
 **
 **  begin                : 2001
 **  copyright            : (C) 2001 - 2007 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **  License              : GPL
 **
 **  Shows a label with current time.
 **
 **  Special Thanks to Alexander Linden <alinden@gmx.de>
 **
 ****************************************************************************/

#include <qwidget.h>
#include <qdatetime.h>
#include <qtimer.h>
#include <qfont.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <QPaintEvent>
#include <QMouseEvent>
#include <defaults.h>
#include <libhde.h>

class dclock : public QLabel
{
  Q_OBJECT
	
    QTime time;
  void settime(QTime &);
  
 public slots:
  void timeout(void);
	
 protected:
  //virtual void drawContents ( QPainter * p );
  virtual void mouseDoubleClickEvent ( QMouseEvent * e );
  virtual void paintEvent ( QPaintEvent * );

 public:
  dclock(QWidget *parent=0, Qt::WindowFlags f = 0x00000000);

};
