/****************************************************************************
 **
 **				smenuitem.cpp
 **			===========================
 **
 **  begin                : Jan 01 2005
 **  copyright            : (C) 2005 -2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  Qpopup menu items look alike for start menu.
 **
 ****************************************************************************/

#include <qpainter.h> 
#include <qapplication.h>
#include <qfontmetrics.h>
#include <qtimer.h> 

#include <qbitmap.h>
#include <QPixmap>
#include <QEvent>
#include <QMouseEvent>

#include <libhde.h>
#include "smenuitem.h"
//#include "defs.h"


sMenuItem::sMenuItem( QWidget *parent )
  : QWidget( parent )
{
  haspopup = false;
  drawPixmap = true;
  pixWidth = 0;
  pixHeight = 0;
  insidePainting = false;
  mfont = font();
  mfont.setBold(true);
}


void sMenuItem::paintEvent ( QPaintEvent * event )
{
  if(insidePainting)
    return;
  else
    insidePainting = true;

  QPainter p;
  p.begin(this);
  
  p.setFont( mfont );
  
  if( !orig_pic.isNull() && drawPixmap){
    if( (pixWidth > 0 ) && ( pixHeight > 0 ) )
      pix = orig_pic.scaled(pixWidth, pixHeight, Qt::IgnoreAspectRatio,
			    Qt::SmoothTransformation);
    else
      pix = orig_pic.scaled(height(),height(), Qt::IgnoreAspectRatio,
			    Qt::SmoothTransformation);
  }
  
  if(underMouse()){
    QRect fillRect(0, 0 ,width(),height());
    if(hbgpix.isNull())
      p.fillRect(fillRect, palette().highlight() );
    else
    {
      QPixmap hbgcp = hbgpix.scaled(width(),height(), Qt::IgnoreAspectRatio,
				    Qt::SmoothTransformation);
      p.drawPixmap(fillRect, hbgcp );
    }
    p.setPen( palette().color(QPalette::HighlightedText) );
  }else{
    p.setPen( palette().color(QPalette::Text) );
    if(!bgpix.isNull())
    {
      QRect fillRect(0, 0 ,width(),height());
      QPixmap bgcp = hbgpix.scaled(width(),height(), Qt::IgnoreAspectRatio,
				   Qt::SmoothTransformation);
      p.drawPixmap(fillRect, bgcp );

    }
  }

  int texts = 4;
  
  if(QApplication::isRightToLeft() ){
    texts = 10;
    if( !pix.isNull()  && drawPixmap){
      p.drawPixmap( width() - pix.width()-5,(height()/2 )-(pix.height()/2),
		     pix, 0, 0, pix.width(), pix.height());
      texts = 15;
    }
    

    if(! str.isEmpty())
    {
      QRect r(2,2, width()-pix.width()-texts, height());
      p.drawText(r, Qt::AlignVCenter|Qt::AlignLeft, str );
    }
    
    if(haspopup){
      p.drawLine( 10 ,(height()/2)-3, 10 , (height()/2)+3);
      p.drawLine( 9 ,(height()/2)-2, 9, (height()/2)+2);
      p.drawLine( 8 ,(height()/2)-1, 8, (height()/2)+1);
      p.drawLine( 7 ,(height()/2), 7, (height()/2));
    }
  
  }else{
    if( !pix.isNull()  && drawPixmap){
      p.drawPixmap ( 5, (height()/2 ) - (pix.height()/2), pix, 0, 0, 
		      pix.width(), pix.height());
      texts = pix.width() +4;
    }
    
    if(! str.isEmpty())
      p.drawText( QRect( texts +5 , (height()/2 ) - 
			  (QFontMetrics(mfont).height()/2), width()-6,
			  height()), str );
    
    if(haspopup){
      p.drawLine( width() - 10 ,(height()/2)-3,width() - 10, (height()/2)+3);
      p.drawLine( width() - 9 ,(height()/2)-2,width() - 9, (height()/2)+2);
      p.drawLine( width() - 8 ,(height()/2)-1,width() - 8, (height()/2)+1);
      p.drawLine( width() - 7 ,(height()/2),width() - 7, (height()/2));
    }
  }
    
  p.end();
  insidePainting = false;
}


void sMenuItem::enterEvent ( QEvent * event ) 
{ 
  repaint(); 
  emit highlighted(this);
  if(haspopup)
    QTimer::singleShot( 1000, this, SLOT(pop()) );
}


bool sMenuItem::connectItem( const QObject * receiver, const char * member )
{
  connect( this, SIGNAL( clicked() ), receiver, member);
  return false;
}


bool sMenuItem::disconnectItem( const QObject * receiver, const char * member)
{
  disconnect( this, SIGNAL( clicked() ), receiver, member);
  return false;
}

void sMenuItem::mouseReleaseEvent ( QMouseEvent * )
{
  if(haspopup)
    pop();
  else
    emit clicked();
}

void sMenuItem::pop(void)
{
  if(underMouse()){
    QPoint p = mapToGlobal(QPoint(0, 0));
    QSize s(popup->sizeHint());
    p.setY(p.y()-s.height() + height() + 1);
    
    if(QApplication::isRightToLeft() ){
      p.setX(p.x()-s.width() +1);
    }else{
      p.setX(p.x() + width() +1);
    }
    
    popup->exec(p);
  }
}

void sMenuItem::setCommand(QString com)
{
    command = com;
    disconnect( this,SLOT(execCommand()));
    connectItem(this, SLOT(execCommand()));
}



void sMenuItem::execCommand(void)
{
  execCmd(command);
}

void sMenuItem::setPixmap(QPixmap pic)
{ 
  pix = pic;
  orig_pic = pic;
  
  repaint();
}
