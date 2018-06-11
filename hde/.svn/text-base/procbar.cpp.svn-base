/**********************************************************************
 **
 **				procbar.cpp
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **  Thanks to            : alinden@gmx.de
 **
 **  Creates the buttons for windows.
 **
 *********************************************************************/

#include "defs.h"
#include "defaults.h"
#include "procbar.h"
#include <libhde.h>

#include <QPalette>
#include <QBitmap>

// max. button width
#define max_bwidth 200


tbutton::tbutton(QWidget *parent)
  : QPushButton(parent)
{
  setFont(defaults::toolbarfont);
  tooltipTimer = new QTimer(this);
  Q_CHECK_PTR(tooltipTimer);
  tooltipTimer->setSingleShot(TRUE);
  connect(tooltipTimer, SIGNAL(timeout()), SLOT(showTooltip()));
  screenShotLabel = new QLabel;
  screenShotLabel->setFixedSize(200,150);
}

#include "xwindow.h"
#include "qapp.h"

void tbutton::enterEvent ( QEvent * event )
{
  QPushButton::enterEvent(event);

  tooltipTimer->start ( 500 );

}

void tbutton::leaveEvent ( QEvent * event )
{
  QPushButton::leaveEvent(event);
  
  if( tooltipTimer->isActive() )
    tooltipTimer->stop();
  hideLabel();
}

void tbutton::showTooltip()
{
  QPoint pos = mapToGlobal(QPoint(0,0));
  int x = pos.x() - ((200-width())/2);
    
  int y =  pos.y()-150;


    if(! defaults::toolbar_top)   // menu above button
    {
	QSize s(200,150);
	y = pos.y()-s.height();
    }
    else
    {
      QPoint p = mapToGlobal(QPoint(0, defaults::tb_height));
      y = p.y();
    }

  screenShotLabel->setGeometry(x, y, 200,150);
  drawScreenLabel();
  screenShotLabel->show();
  XRaiseWindow(QX11Info::display(), screenShotLabel->winId());

}

void tbutton::setScreenPixmap( QPixmap pix)
{
  screenPixmap = pix.scaled(180,130, Qt::IgnoreAspectRatio,
			    Qt::SmoothTransformation);
}

void tbutton::drawScreenLabel()
{
  QPixmap *sspix = new QPixmap(defaults::get_cfile("images/stooltip.png"));
  screenShotLabel->setMask(sspix->mask());
  QPixmap *bg = new QPixmap(200,150);
  QPainter p(bg);

  {
    xwindow *client;
    
    QRectF target0(0,0, screenShotLabel->width(), screenShotLabel->height());
    QRectF source0(screenShotLabel->geometry().x(), 
		   screenShotLabel->geometry().y(), 
		   screenShotLabel->geometry().width(), 
		   screenShotLabel->geometry().height());
    p.drawImage(target0, qapp::Desktop->desktopBG, source0);
    
    for (int i = clients.size()-1; i >=0 ; i--)
    {
      client = clients.at(i);
      
      bool curdesk;
      int dwidth = QApplication::desktop()->width();
      curdesk = client->x() <= dwidth && client->x() >= 0;
      
      if(client->isVisible() && curdesk )
      {
      
	int cx = client->x();
	int cy = client->y();
	int cw = client->width();
	int ch = client->height();
	
	QRect s(cx, cy, cw, ch);
	QRect t(screenShotLabel->x(), screenShotLabel->y(), 
		screenShotLabel->width(), screenShotLabel->height());
	
	if(t.intersects(s))
	{
	  QRect intrs = t & s;
	  cw = intrs.width();
	  ch = intrs.height();
	  
	  
	  if(screenShotLabel->x() >= client->x())
	  {
	    cx = 0;
	  }
	  else
	  {
	    cx = client->x() - screenShotLabel->x();
	  }
	  if(screenShotLabel->y() >= client->y())
	  {
	    cy = 0;
	  }
	  else
	  {
	    cy = client->y() - screenShotLabel->y();
	  }
	  
	  int ix = 0;
	  int iy = 0;
	  
	  if(screenShotLabel->x() > client->x())
	    ix = screenShotLabel->x() - client->x();
	  if(screenShotLabel->y() > client->y())
	    iy = screenShotLabel->y() - client->y();
	  
	  QRect irect(ix, iy, client->width()-ix, client->height()-iy);
	  QImage img = QImage::fromData(client->screenBytes);
	  img = img.copy(irect);
	  p.drawImage(QRect(cx,cy,irect.width(),irect.height()), img, 
		      QRect(0, 0, irect.width(), irect.height()));
	}
      }
    }
  }
  {   
    p.drawPixmap(0, 0, 200, 150, *sspix);
    if(!screenPixmap.isNull())
      p.drawPixmap(10, 10, 180, 130, screenPixmap);

    p.drawRect(10, 10, 180, 130);

  }
  p.end();

  screenShotLabel->setPixmap(*bg);

  delete sspix;
  delete bg;
}

void tbutton::hideLabel()
{
  if(screenShotLabel->isVisible())
    screenShotLabel->hide();
}

tbutton::~tbutton()
{
  screenShotLabel->close();
  delete screenShotLabel;
}


void tbutton::paintEvent( QPaintEvent *e ){
  QString butbg = defaults::get_cfile(defaults::tbButton_bg);
  if(QFileInfo(butbg).isFile())
  {
    QPainter *p = new QPainter(this);

    QImage img(butbg);
    if( (isDown() || isChecked()) && 
	(QFileInfo(defaults::get_cfile(defaults::tbButtondown_bg)).isFile()))
      img = QImage(defaults::get_cfile(defaults::tbButtondown_bg));
    else if(testAttribute(Qt::WA_UnderMouse) && 
	    (QFileInfo(defaults::get_cfile(defaults::tbButtonmo_bg)).isFile()))
      img = QImage(defaults::get_cfile(defaults::tbButtonmo_bg));

    if(! img.isNull())  // make scaled pixmap
    {
      //QPixmap pix;
      if( ((defaults::starticonplace == "TOP") || 
	   (defaults::starticonplace == "BUTTOM")) &&
	  (defaults::tbButtonHeight > 9) )
	img = img.scaled(width(), defaults::tbButtonHeight, 
			 Qt::IgnoreAspectRatio,
			 Qt::SmoothTransformation);
      else
	img = img.scaled(width(), height(),
			 Qt::IgnoreAspectRatio,
			 Qt::SmoothTransformation);

      if( (defaults::starticonplace == "TOP")
	  && (defaults::tbButtonHeight > 9) ){
	p->drawImage(0,0, img);
	p->drawPixmap(2,2, icon().pixmap(iconSize()) );
      }else if ( (defaults::starticonplace == "BUTTOM") 
		 && (defaults::tbButtonHeight > 9) ){
	p->drawImage(0, height()-defaults::tbButtonHeight, img);
	p->drawPixmap(2,height()-defaults::tbButtonHeight +2, 
		      icon().pixmap(iconSize()));
      }else{
	p->drawImage(0,0, img);
	p->drawPixmap(2,2, icon().pixmap(iconSize()));
      }
    }


    p->end();
    delete p;

  }else
    QPushButton::paintEvent(e);
}


procbar::procbar(QWidget *parent) : QWidget(parent)
{
  setFont(defaults::toolbarfont);
}

void procbar::draw_button(WINLIST *w)
{
  int txtstart = 4;
  int h=w->button->height();
  int hi=w->button->height();
  QPixmap newpix(w->button->width(), w->button->height() );
  Q_CHECK_PTR(newpix);
  QBitmap bmask(w->button->width(), w->button->height()); //all transparent
  Q_CHECK_PTR(bmask);
  bmask.fill(Qt::white);
  newpix.setMask(bmask);

  QPainter painter(&newpix);
  painter.setFont(defaults::toolbarfont);


    if(! w->pixmap->isNull())   // draw scaled pixmap
    {
      QRect cr(1,1, w->button->height()-3, w->button->height()-3);
      painter.drawPixmap(cr, *w->pixmap, w->pixmap->rect());
      txtstart = w->button->height()+2;
    }


  QRect cr(txtstart, 0, w->button->width(), w->button->height());
  QRect cr0(txtstart+1, 1, w->button->width(), w->button->height());

  QColor shadowColor = getOppositeColor(defaults::tbButton_fg);
  if(defaults::toolbuttonsShadow)
  {
    painter.setPen(shadowColor);
    painter.setBrush(shadowColor);
    painter.drawText( cr0, Qt::AlignLeft|Qt::AlignVCenter, w->text);
  }
  painter.setPen(defaults::tbButton_fg);
  painter.setBrush(defaults::tbButton_fg);
  painter.drawText( cr, Qt::AlignLeft|Qt::AlignVCenter, w->text);
  painter.end();



  w->button->setIconSize(QSize(w->button->width(), w->button->height()-2));
  w->button->setIcon(QIcon(newpix));
}

void procbar::change_text(QString *icname, xwindow *win)
{	
  WINLIST *w;
  int i;
  
  for(i=0; i < wlist.size(); i++)
    if(wlist.at(i)->win == win)
      break;
  
  if(i == wlist.size())
    return;
  
  w = wlist.at(i);
  w->pixmap = win->icon();
  w->text = *icname;
  draw_button(w);

}

void procbar::draw_buttons(void)
{
  WINLIST *w;
  int i,i2;
  
  if(wlist.isEmpty())
    return;
  
  int h = height();
  int pos = 0;     // current position
  bwidth = (width()/wlist.size())-2;   // button width
  
  
  if(bwidth < h)         // scroll on overflow
  {
    bwidth = h;
    
    int tsize = wlist.size()*(h+1);
    int maxscr = ((tsize-width())/(h+1))+1;
    w = wlist.at(i=0);
    for(i=0; i < maxscr; i++)
    {
      w->button->hide();
      w = wlist.at(i);
    }
  }
  else
  {
    i=0;
	w = wlist.at(i=0);

    if(bwidth > max_bwidth)
      bwidth = max_bwidth-1;
  }

  if(QApplication::isRightToLeft()){
    pos = width()-bwidth -2;
    while(i < wlist.size())
    {
      w = wlist.at(i);
      w->button->show();
      if((defaults::tbButtonHeight>9)&& 
	 (defaults::starticonplace != "MIDDLE"))
	w->button->setGeometry(pos, 0, bwidth, h);
      else
	w->button->setGeometry(pos, 3, bwidth, h-6);
      draw_button(w);
      
      if(! w->button->isVisible())
	w->button->show();
      
      pos -= bwidth+2;
      i++;
    }
  }else{
    pos = pos + 2;
    while(i < wlist.size())
    {
      w = wlist.at(i);
      w->button->show();
      if((defaults::tbButtonHeight>9)&& 
	 (defaults::starticonplace != "MIDDLE"))
	w->button->setGeometry(pos, 0, bwidth, h);
      else
	w->button->setGeometry(pos, 3, bwidth, h-6);
      draw_button(w);
      
      if(! w->button->isVisible())
	w->button->show();
      
      pos += bwidth+2;
      i++;
    }
  }
  
}


void procbar::resizeEvent(QResizeEvent *)
{
  if(QFileInfo(defaults::get_cfile(defaults::toolbar_bg.
				   toAscii().data())).isFile()){
    QImage qp(width(), height(), QImage::Format_RGB32);
    QPainter painter(&qp);
    
    QImage img(defaults::get_cfile(defaults::toolbar_bg));
    if(! img.isNull())  // make scaled pixmap
    {
      img = img.scaled(width(), height(), Qt::IgnoreAspectRatio,
		       Qt::SmoothTransformation );
      painter.drawImage(0,0, img);
      
      painter.end();
      QPalette palette;
      palette.setBrush(backgroundRole(), QBrush(qp));
      setPalette(palette);
    }
    
  }else if ( defaults::taskStyle == "hde" ){
    QImage qp(width(), height(), QImage::Format_RGB32);
    QPainter painter(&qp);
    QColor firstColor(palette().brush(QPalette::Active, 
				      QPalette::Background).color());
    //    qp.fill(firstColor.rgb());

    int i = 0;
    
    int h = (height()) / 2;
    
    //
    //
    
    painter.fillRect(0,0, width(), height(), firstColor);
    
    painter.setPen(firstColor.dark(100+h*2));
    painter.drawLine(0,0 , width(), 0); 
    
    painter.setPen(firstColor.light(100+h*2));

    for ( i = 0; i <= h; ++i ) {
      painter.setPen(firstColor.dark(100 + (h*2)-(i*2)));
      painter.drawLine(0,i , width(), i); 
    }
    int j = 0;
    for ( i =  h; i < height() ; ++i ) {
      painter.setPen( firstColor.light(100 + (j*2)) );
      j++;
      painter.drawLine(0, i , width(), i); 
    }
    
    for ( i = 1; i < 3; ++i ) {
      painter.setPen(firstColor.light(100+(h*2)-i));
      painter.drawLine(0,i , width(), i); 
    }

    
    for ( i = height()-3; i < height(); ++i ) {
      painter.setPen(firstColor.dark(100+(i*2)));
      painter.drawLine(0,i , width(), i); 
    }

    if(QApplication::isRightToLeft()){
      painter.setPen(firstColor.dark(250) );
      painter.drawLine(0,0 , 0, height()); 
    }else{
      painter.setPen(firstColor.dark(250));
      painter.drawLine(width()-1,0 , width()-1, height()); 
    }
    
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(qp));
    setPalette(palette);
    
    painter.end();
  }else{
    QImage qp(width(), height(), QImage::Format_RGB32);
    QColor firstColor(palette().brush(QPalette::Active, 
				      QPalette::Background).color());
    //    qp.fill(firstColor.rgb());
    QPainter paint(&qp);
    
    paint.fillRect(0,0, width(), height(), firstColor);
    paint.setPen(firstColor.light(130));
    paint.drawLine(0 ,0 , width(), 0); 
    paint.drawLine(0 ,1 , width(), 1); 
    
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(qp));
    setPalette(palette);
    paint.end();	
  }
  draw_buttons();
}

void procbar::add(xwindow *win)
{
  WINLIST *w;
  int i;
	
  if(win == NULL)
    return;
  
  foreach(w, wlist)
  {
    if(w->win == win)    // window already on bar
    {
      w->button->setChecked(FALSE);
      return;
    }
  }
  
  w = new WINLIST;
  Q_CHECK_PTR(w);
  w->button = new tbutton(this);
  Q_CHECK_PTR(w->button);
  w->button->lower();  // last to redraw
  w->pixmap = win->icon();
  w->text = win->icaption();
  draw_button(w);

  w->win = win;
  w->button->setCheckable(TRUE);

  w->button->setContextMenuPolicy( Qt::CustomContextMenu );
  connect(w->button, SIGNAL(toggled(bool)), win, SLOT(state(bool)));
  connect(w->button, SIGNAL( customContextMenuRequested(const QPoint &) ),
	  win, SLOT( ContextMenuRequested(const QPoint &) ));

  wlist.append(w);
  draw_buttons();
}

void procbar::set_on(xwindow *win, bool onstat)
{
  WINLIST *w;
	
  foreach(w, wlist)
  {
    disconnect(w->button, SIGNAL(toggled(bool)), w->win, SLOT(state(bool)));
    w->button->setChecked(FALSE);
    connect(w->button, SIGNAL(toggled(bool)), w->win, SLOT(state(bool)));
    
    if(w->win == win)    // window on bar
    {
      if(onstat)
	w->button->setChecked(true);
      else
	w->button->setChecked(FALSE);
    }
  }
}	

void procbar::setScreenPixmap(xwindow *win, QPixmap pix)
{
  WINLIST *w;
	
  foreach(w, wlist)
  {
    if(w->win == win)    // window on bar
    {
      w->button->setScreenPixmap(pix);
    }
  }
}

void procbar::upDown(xwindow *win, bool onstat)
{
  WINLIST *w;
	
  foreach(w, wlist)
  {
    disconnect(w->button, SIGNAL(toggled(bool)), w->win, SLOT(state(bool)));
    w->button->setChecked(FALSE);
    
    if(w->win == win)    // window on bar
    {
      if(onstat)
	w->button->setChecked(true);
      else
	w->button->setChecked(FALSE);
    }
    connect(w->button, SIGNAL(toggled(bool)), w->win, SLOT(state(bool)));
  }
}

void procbar::change_palette(const QPalette &bpal, xwindow *win)
{
  int i;
	
  for(i=0; i < wlist.size(); i++)
    if(wlist.at(i)->win == win)
      break;
	
  if(i == wlist.size())
    return;
  
  wlist.at(i)->button->setPalette(bpal);
}

void procbar::remove(xwindow *win)   // remove from bar
{
  WINLIST *w;
  int i;
  
  for(i=0; i < wlist.size() && wlist.at(i)->win != win; i++);
  
  if(i == wlist.size())
    return;
  
  w = wlist.takeAt(i);
  delete w->button;
  delete w;
  
  draw_buttons();
}

void procbar::remove_all(void)
{
  WINLIST *w;

  foreach(w, wlist)
  {
    delete w->button;
    delete w;
  }
  wlist.clear();
}
