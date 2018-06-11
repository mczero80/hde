/**********************************************************************
 **
 **				menu.cpp
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **  Thanks to            : alinden@gmx.de
 **
 **  Creates menu button and the XKill function
 **
 *********************************************************************/

#include "defs.h"
#include <defaults.h>
#include "qapp.h"
#include "toolbar.h"
#include "conf.h"
#include "normalmenu.h"
#include "xpmenu.h"
#include "vistamenu.h"

#define kcursor_width 32
#define kcursor_height 32
uchar menu::kcursor_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0x01,
   0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x08, 0x10, 0x01,
   0x80, 0x10, 0x08, 0x01, 0x80, 0x20, 0x04, 0x01, 0x80, 0x40, 0x02, 0x01,
   0x80, 0x80, 0x01, 0x01, 0x80, 0x80, 0x01, 0x01, 0x80, 0x40, 0x02, 0x01,
   0x80, 0x20, 0x04, 0x01, 0x80, 0x10, 0x08, 0x01, 0x80, 0x08, 0x10, 0x01,
   0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0xff, 0xff, 0x01,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

uchar menu::kcursor_mask[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x03, 0xc0, 0xff, 0xff, 0x03,
   0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x1c, 0x38, 0x03,
   0xc0, 0x38, 0x1c, 0x03, 0xc0, 0x70, 0x0e, 0x03, 0xc0, 0xe0, 0x07, 0x03,
   0xc0, 0xc0, 0x03, 0x03, 0xc0, 0xc0, 0x03, 0x03, 0xc0, 0xe0, 0x07, 0x03,
   0xc0, 0x70, 0x0e, 0x03, 0xc0, 0x38, 0x1c, 0x03, 0xc0, 0x1c, 0x38, 0x03,
   0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0xff, 0xff, 0x03,
   0xc0, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

QString menutxt = "";
bool menupix;

/*********************************************************************
 *
 * Our class inhirit a QPushButton, it's not driven from a QPopupMenu
 *
 ********************************************************************/
menu::menu(QWidget *parent) : QPushButton(parent)
{
  /*****************************************************
   *
   * get the start button height and apply it.
   *
   ****************************************************/
  QString icnstr = defaults::get_cfile(defaults::starticon.toAscii().data());
  if(QFileInfo( icnstr ).isFile()){
    if((defaults::startheight < 10) && (defaults::startwidth < 10)){
      setFixedWidth(QPixmap(icnstr).width());
      menupix = true;	
      setFixedHeight(defaults::tb_height);
    }else{
      menupix = true;
      if(defaults::starticonplace != "MIDDLE")
	setFixedHeight(defaults::tb_height);
      else if(defaults::startheight > 9)
	setFixedHeight(defaults::startheight);
      else
	setFixedHeight(defaults::tb_height);

      if(defaults::startwidth > 9)
	setFixedWidth(defaults::startwidth);
      else
	setFixedWidth(QPixmap( icnstr ).width());

    }
  }else
    setFixedHeight(defaults::tc_height);

  killop = FALSE;

  /***************************************************************
   *
   * Creating our menu and setting it's connections.
   *
   ***************************************************************/
  basemenu = new menuMenu;
  Q_CHECK_PTR(basemenu);
  connect(basemenu, SIGNAL( triggered( QAction *) ),
	  basemenu, SLOT(actionTriggered( QAction *)));
  

  QImage img(qapp::get_cfile("images/menu.xpm"));
  
  if(! img.isNull())  // make scaled pixmap
  {
    int wh = defaults::tc_height-4;
    setIcon(QIcon(QPixmap::fromImage(img.scaled(wh, wh, Qt::IgnoreAspectRatio,
						Qt::SmoothTransformation))));
  }
  
  act_quit = new QAction(this);
  act_quit->setData(QVariant(QString("_Quit")));
  act_kill = new QAction(this);
  act_kill->setData(QVariant(QString("_Kill")));
  act_rest = new QAction(this);
  act_rest->setData(QVariant(QString("_Restart")));


  /***************************************************************
   *
   * Setting it's style.
   *
   ***************************************************************/
  
  if(defaults::menuStyle == "xp")
    defaults::smenu = new xpMenu(0, Qt::CustomizeWindowHint |
				   Qt::FramelessWindowHint |
				   Qt::WindowStaysOnTopHint|
				   Qt::X11BypassWindowManagerHint);
  else if(defaults::menuStyle == "vista")
    defaults::smenu = new vistaMenu(0, Qt::CustomizeWindowHint |
				   Qt::FramelessWindowHint |
				   Qt::WindowStaysOnTopHint|
				   Qt::X11BypassWindowManagerHint);
  else
    defaults::smenu = new normalMenu(0, Qt::CustomizeWindowHint |
				   Qt::FramelessWindowHint |
				   Qt::WindowStaysOnTopHint|
				   Qt::X11BypassWindowManagerHint);

  defaults::smenu->setPgramsMenu(basemenu);

  defaults::smenu->exitItem->connectItem( this, SLOT(winkill_all()));
  defaults::smenu->killItem->connectItem( this, SLOT(winkill()));


  QString mnutxt =  defaults::get_cfile("applnk/.directory");
  if(QFileInfo::QFileInfo(mnutxt).exists()){
    hdeItem ditem = defaults::readItem(mnutxt);
    menutxt = ditem.name;
  }else{
    //setText("");
  }

  if(QString::compare(text(),"")==0 || QString::compare(text(),NULL)==0){
    QImage img(qapp::get_cfile("images/menu.xpm"));

    if(! img.isNull())  // make scaled pixmap
    {
      int wh = defaults::tc_height-4;
      QPixmap pix;
      pix.fromImage(img.scaled(wh, wh));
      //	setPixmap(pix);
      setIcon(QIcon(pix));
      mainpix = pix;
    }
  }else{
    QImage img(qapp::get_cfile("images/menu.xpm"));
    
    if(! img.isNull())  // make scaled pixmap
    {
      int wh = defaults::tc_height-4;
      QPixmap pix;
      pix.fromImage(img.scaled(wh, wh));
      setIcon(QIcon(pix));
      mainpix = pix;
    }

  }
  if(menupix){
  }else if(menutxt != ""){
    QFontMetrics qf(font());
    //	setFixedWidth(qf.width(menutxt) + pixmap()->width() + 9);
    setFixedWidth(qf.width(menutxt) + height() + 9);
  }else
    setFixedWidth(height());
  

  setDefault ( false );
}

/*********************************************************************
 *
 * paintEvent, all paint operations must come here.
 *
 ********************************************************************/
void menu::paintEvent( QPaintEvent *e ){

  if(menupix){
    QPainter *p = new QPainter(this);
    QString strtIcon = defaults::get_cfile(defaults::starticon);
    QImage img(strtIcon);
    if(isDown() && 
       (QFileInfo(defaults::get_cfile(defaults::startdown)).isFile()))
    {
      strtIcon = defaults::get_cfile(defaults::startdown);
      img = QImage(strtIcon);
    }else if(testAttribute(Qt::WA_UnderMouse) && 
	    (QFileInfo(defaults::get_cfile(defaults::starticonmo)).isFile()))
    {
      strtIcon = defaults::get_cfile(defaults::starticonmo);
      img = QImage(strtIcon);
    }
    if(! img.isNull())  // make scaled pixmap
    {
      if( ((defaults::starticonplace == "TOP") || 
	   (defaults::starticonplace == "BUTTOM")) && 
	  (defaults::startheight > 9) )
	if(QApplication::isRightToLeft())
	  img = img.mirrored(TRUE,FALSE).scaled(width(),
						defaults::startheight);
	else
	  img = img.scaled(width(), defaults::startheight);
      else
	if(QApplication::isRightToLeft())
	  img = img.mirrored(TRUE,FALSE).scaled(width(), height());
	else
	  img = img.scaled(width(), height());
      
      if( (defaults::starticonplace == "TOP") 
	  && (defaults::startheight > 9) )
	p->drawImage(0,0, img);
      else if ( (defaults::starticonplace == "BUTTOM") 
		&& (defaults::startheight > 9) )	
	p->drawImage(0, height()-defaults::startheight, img);
      else
	p->drawImage(0,0, img);
    }


    if(defaults::startButton_fg != Qt::transparent)
    {
      QFont fnt= defaults::startbtnfont;//font();
      setFont(fnt);
      {
	QPalette palette;
	palette.setColor(foregroundRole(), defaults::startButton_fg);
	setPalette(palette);
      }
      int defheight = 0;
      defheight = height() - defaults::startheight;

      
      QColor shadowColor = Qt::black;
      {
	int r = defaults::startButton_fg.red();
	int g = defaults::startButton_fg.green();
	int b = defaults::startButton_fg.blue();

	int r2 = r -255;
	if(r2 < 0)
	  r2 = r2 * -1;

	int g2 = g -255;
	if(g2 < 0)
	  g2 = g2 * -1;

	int b2 = b -255;
	if(b2 < 0)
	  b2 = b2 * -1;

	shadowColor.setRgb(r2,g2,b2);
      }

      QRect r =  QRect(0, 0, width(), height());
      QRect ro = QRect(1, 1, width()+1, height()+1);

      if( (defaults::starticonplace == "TOP") && (height() > 9) )
      {
	p->setPen(shadowColor);
	p->drawText( ro, Qt::AlignTop|Qt::AlignHCenter, menutxt);
	p->setPen(defaults::startButton_fg);
	p->drawText( r, Qt::AlignTop|Qt::AlignHCenter, menutxt);
      }
      else if( (defaults::starticonplace == "BUTTOM") && (height() > 9) )
      {
	p->setPen(shadowColor);
	p->drawText( ro, Qt::AlignBottom|Qt::AlignHCenter, menutxt);
	p->setPen(defaults::startButton_fg);
	p->drawText( r, Qt::AlignBottom|Qt::AlignHCenter, menutxt);
      }
      else
      {
	p->setPen(shadowColor);
	p->drawText( ro, Qt::AlignCenter, menutxt);
	p->setPen(defaults::startButton_fg);
	p->drawText( r, Qt::AlignCenter, menutxt);
      }
    }

    p->end();
    delete p;
  }else{
    QPushButton::paintEvent(e);
    QPainter *p = new QPainter(this);
    if(QApplication::isRightToLeft())
    {
      p->drawPixmap( 9+QFontMetrics(font()).width(menutxt),3, mainpix);
      p->drawText( 3, (height()/2) + (QFontMetrics(font()).height()/2)
		   -3 , menutxt);
    }else{
      p->drawPixmap(3,3, mainpix);
      p->drawText(height()+4, (height()/2) + 
		  (QFontMetrics(font()).height()/2)-3, menutxt);
    }
    
    p->end();
    delete p;
  }
}

/****************************************************************
 *
 * Reading our menu.
 *
 ***************************************************************/
void menu::readmenu(void)
{
  xdgMenu xdg;
  xdg.readMenus(basemenu);
}

void menu::winkill(void)
{
  QBitmap bmapc = QBitmap::fromData(QSize(kcursor_width, kcursor_height),
				    kcursor_bits);
  QBitmap bmapm = QBitmap::fromData(QSize(kcursor_width, kcursor_height),
				    kcursor_mask);
  grabMouse(QCursor(bmapc, bmapm));
	
  killop = TRUE;
}


void menu::run_cmd(QByteArray &cmd)  // execute menu item
{
  pid_t pid;
  
  if((pid = fork()) == -1)
  {
    perror("fork()");
    return;
  }	
  if(pid)
    return;
  
  execl("/bin/sh", "sh", "-c", cmd.data(), NULL);
  perror("cannot run /bin/sh");
  exit(1); 
}

void menu::start_popup(void)
{	
  Window rw,cw;
  int rx,ry,wx,wy;
  unsigned mr;
  
  if(qapp::menu_open)
    return;
  
  xwindow *focusclient = qapp::focusclient;
  qapp::menu_open = TRUE;
  
  setDown(TRUE);
  
  if(! defaults::show_menu || qapp::smode)  // show at mouse position
  {
    XQueryPointer(QX11Info::display(), QX11Info::appRootWindow(), &rw, 
		  &cw, &rx, &ry, &wx, &wy, &mr);

    defaults::smenu->show();
    defaults::smenu->move(QPoint(rx, ry));
  }
  else
  {
    if(! defaults::toolbar_top)   // menu above button
    {
      if(QApplication::isRightToLeft()){
	QPoint p = mapToGlobal(QPoint(0, 0));
	QSize s(defaults::smenu->size());
	p.setY(p.y()-s.height());
	p.setX(p.x()-s.width()+width()+2);
	defaults::smenu->show();
	defaults::smenu->move(p);
      }else{
	QPoint p = mapToGlobal(QPoint(0, 0));
	QSize s(defaults::smenu->size());
	p.setY(p.y()-s.height());
	defaults::smenu->show();
	defaults::smenu->move(p);
      }
    }
    else
    {
      QPoint p = mapToGlobal(QPoint(0, height()));
      QSize s(defaults::smenu->size());
      defaults::smenu->show();
      defaults::smenu->move(p);
    }
  }
  qapp::menu_open = FALSE;
  setDown(FALSE);
  
  XSetInputFocus(QX11Info::display(), QX11Info::appRootWindow(), 
		 RevertToPointerRoot, CurrentTime);
  if(focusclient != NULL && clients.indexOf(focusclient) != -1)
    focusclient->setchildfocus(CurrentTime);
}

void menu::mousePressEvent(QMouseEvent *event)
{
  if(killop)  //  window kill operation
  {
    xwindow *client;
    
    killop = FALSE;
    releaseMouse();
    
    if(event->button() != Qt::LeftButton)
      return;
    
    if((client = (xwindow*)QApplication::widgetAt(event->globalPos())) == NULL)
      return;
		
    XKillClient(QX11Info::display(), client->client_id());
    XSync(QX11Info::display(), FALSE);
    
    return;
  }
  start_popup();
}


void menu::winkill_all()
{ 
  tb_pb->remove_all();
  for(int i=0; i < clients.size(); i++) 
    clients.at(i)->wdestroy();
  
  clients.clear();
  delete qapp::tb;
  XSync(QX11Info::display(), FALSE);
}
