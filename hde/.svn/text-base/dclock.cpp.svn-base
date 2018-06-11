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

#include "dclock.h"
#include <qtooltip.h>
#include <qtranslator.h>
#include <QMouseEvent>
#include <QLabel>
#include <QPaintEvent>
#include <defaults.h>


dclock::dclock(QWidget *parent, Qt::WindowFlags flag) : QLabel(parent, flag)
{
  setMouseTracking( true );

  setFont(defaults::toolbarfont);
  QTime newtime = QTime::currentTime();
  settime(newtime);

  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), SLOT(timeout()));

  timer->start(5000);  // signal every 5 seconds


 QPalette palette;
 palette.setColor(foregroundRole(), defaults::apbar_fg);
 setPalette(palette);
}


void dclock::mouseDoubleClickEvent( QMouseEvent * e ){
  execCmd("hDateTime");
  return;
}


//void dclock::drawContents ( QPainter * p ){
void dclock::paintEvent ( QPaintEvent *e ){
  //QLabel::paintEvent(e);
  QPainter p(this);
    QColor textColor = palette().color(QPalette::Normal, 
				       QPalette::WindowText);
    QRect cr(0, 0, width()-1, height());
    QRect cr0(1, 1, width()-1, height());

    QColor shadowColor = getOppositeColor(textColor);
    p.setPen(shadowColor);
    p.setBrush(shadowColor);
    p.drawText( cr0, Qt::AlignLeft|Qt::AlignVCenter, text().simplified());
    p.setPen(textColor);
    p.setBrush(defaults::tbButton_fg);
    p.drawText( cr, Qt::AlignLeft|Qt::AlignVCenter, text().simplified());
    p.end();
}

void dclock::timeout(void)
{
  QTime newtime = QTime::currentTime();
  if(newtime.minute() != time.minute()){
    settime(time = newtime);
    setToolTip(tr(QDateTime::currentDateTime().toString().toUtf8().data()));
  }
}

void dclock::settime(QTime &tm)
{
    setText(tm.toString().left(5));
}


