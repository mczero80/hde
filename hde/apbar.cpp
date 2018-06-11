/****************************************************************************
 **
 **				apbar.cpp
 **			=========================
 **
 **  begin                : 2001 based on qlwm
 **  copyright            : (C) 2001 - 2007 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **  License              : GPL
 **
 **  Manages the applets on the right side of the toolbar
 **
 **  Special Thanks to Alexander Linden <alinden@gmx.de>
 **
 ****************************************************************************/
#include "defs.h"
#include <defaults.h>
#include "qapp.h"
#include "toolbar.h"
#include "apbar.h"
#include "dclock.h"

dclock *dc;

apbar::apbar(QWidget *parent) : QWidget(parent)
{
  setFixedHeight(defaults::tb_height);
  //setFixedHeight(defaults::tc_height);

  setFixedWidth(1);

  dc = new dclock(this, Qt::FramelessWindowHint);

  if(defaults::apbarStyle == "win")
    dc->setFixedHeight(height() - 8);
  else
    dc->setFixedHeight(height());
  //  dc->show();

  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  mainLayout->setMargin(2);
  mainLayout->setSpacing(2);
  mainLayout->addStretch();
  mainLayout->addWidget(dc);
  //  mainLayout->addSpacing(4);
  setLayout(mainLayout);

  // overwrite Qt-defaults because we need SubstructureNotifyMask
  XSelectInput(QX11Info::display(), winId(),
	       PointerMotionMask |
	       EnterWindowMask | LeaveWindowMask |
	       ExposureMask |
	       StructureNotifyMask |
	       SubstructureRedirectMask |
	       SubstructureNotifyMask);

  place_clients();
}

// propagate property event to clients
void apbar::paletteChange(const QPalette &)  
{
  XPropertyEvent xe;
  
  for(int i=0; i < ap.size(); i++)
  {
    xe.type = PropertyNotify;
    xe.window = QX11Info::appRootWindow();
    xe.state = PropertyNewValue;
    xe.atom = qapp::wm_resource_manager;
    XSendEvent(QX11Info::display(), ap.at(i)->w, True, PropertyChangeMask,
	       (XEvent *)&xe);
  }
}


void apbar::paintBG(){
  QImage *bg = new QImage(size(), QImage::Format_RGB32);

  QString apbg = defaults::get_cfile(defaults::appbar_bg);
  if(QFileInfo(apbg).isFile()){
    QImage img(apbg);
    if(! img.isNull()){
      QPainter p(bg);
      if(QApplication::isRightToLeft())
	img = img.mirrored(TRUE,FALSE).scaled(width(), height());

      else
	img = img.scaled(width(), height() );
      
      p.drawImage(0,0, img);
      
      p.end();	
      
      QPalette pal = palette();
      pal.setBrush(QPalette::Background, *bg);
      //  pal.setBrush(QPalette::Button, *bg);
      //  pal.setBrush(QPalette::Window, *bg);
      setPalette(pal);
      delete bg;
      setAutoFillBackground(true);
    }
  }  
}

void apbar::place_clients(void)
{
  WINDOW *cur;
  int twidth=6;  // total width
  int i;
  
  for(i=0; i < ap.size(); i++)
    twidth += 22;
  //twidth += ap.at(i)->width+4;
  
  //twidth -= 2;
  setFixedWidth(twidth + dc->width());
  
  if(! twidth)
    return;
  
  int cx = 2;

  if(QApplication::isRightToLeft())
  {
    cx = dc->width() + 2;
    //    for(cur = ap.last(); cur != NULL; cur = ap.prev()){
    for(int i = ap.size()-1; i >= 0; i--)
    {
      cur = ap.at(i);
      XMoveWindow(QX11Info::display(), cur->w, cx+2, 
		  ((defaults::tc_height-20)/2)+2);
     
      XWindowAttributes attr;
      if(XGetWindowAttributes(QX11Info::display(), cur->w, &attr))
      {
	XMapWindow(QX11Info::display(), cur->w);
	XRaiseWindow(QX11Info::display(), cur->w);
      }
      cx += 22;
      //	      cx += cur->width+2;
    }

    /*
    if(defaults::apbarStyle == "win")
      dc->move ( 2, 4 );
    else
      dc->move ( 2, 0 );
    */
  }else{
    foreach(cur, ap)
    {
      XMoveWindow(QX11Info::display(), cur->w, cx, 
		  ((defaults::tc_height-20)/2)+2);
      //XMoveWindow(QX11Info::display(), cur->w, cx, 0);
    
      XWindowAttributes attr;
      if(XGetWindowAttributes(QX11Info::display(), cur->w, &attr))
      {
	XMapWindow(QX11Info::display(), cur->w);
	XRaiseWindow(QX11Info::display(), cur->w);
      }	
      cx += 22;
      //  cx += cur->width+4;
    }
    /*
    if(defaults::apbarStyle == "win")
      dc->move ( cx-5, 4 );
    else
      dc->move ( cx-2, 0 );
    */
 }

  paintBG();

}

void apbar::release_all(void)
{
  WINDOW *cur;
	
  foreach(cur, ap)
  {
    XReparentWindow(QX11Info::display(), cur->w, QX11Info::appRootWindow(),
		    0, 0);
    delete cur;
  }	
  ap.clear();
  paintBG();
}		

bool apbar::add(Window w, int number, QString &name)
{
  WINDOW *cur;
  int i,i2=2,pnum=1;
  
  foreach(cur, ap)
  {
    if(cur->w == w)
      //if(cur->name == name)
      return FALSE;   // already exists
    
    if(number > cur->number)
      pnum = i2;
    
    i2++;	
  } 

  XWindowAttributes attr;
  if(! XGetWindowAttributes(QX11Info::display(), w, &attr))
    return TRUE;
  
  int twidth=2;  // total width
  for(i=0; i < ap.size(); i++)
    twidth += 22;
  //    twidth += ap.at(i)->width+4;
  
  if(twidth+attr.width+100 > tb_pb->width())
  {
    logmsg << "WM: No space left on toolbar\n";
    return FALSE;
  }
  
  WINDOW *client = new WINDOW;
  
  client->w = w;
  client->name = name;
  //  client->width = attr.width;
  client->width = 20;
  client->number = number;
  ap.insert(pnum-1, client);
  
  XSetWindowBorderWidth(QX11Info::display(), w, 0);
  //XResizeWindow(QX11Info::display(), w, attr.width, defaults::tc_height);
  XResizeWindow(QX11Info::display(), w, 20, 20);
  XReparentWindow(QX11Info::display(), w, winId(), 0, 0);
  
  place_clients();

  paintBG();
  
  return TRUE;
}

bool apbar::client_exists(Window w)
{
  for(int i=0; i < ap.size(); i++)
  {
    if(ap.at(i)->w == w)
      return TRUE;
  }
  return FALSE;
}

bool apbar::remove(Window w)
{
  WINDOW *cur;
  
  for(int i=0; i < ap.size(); i++)
  {
    cur = ap.at(i);
    if(cur->w == w)
    {
      ap.removeAt(i);
      delete cur;
      place_clients();
      return TRUE;
    }
  }
  paintBG();
  return FALSE;
}

void apbar::remove(void)
{
  WINDOW *cur;
  bool place = FALSE;
  Atom type;
  int format;
  unsigned long nitems=0;
  unsigned long extra=0;
  unsigned char *data=NULL;
  
  for(int i=0; i < ap.size(); i++)
  {
    cur = ap.at(i);
    if(qapp::apclients[cur->name] == 0)
    {
      XGetWindowProperty(QX11Info::display(), cur->w, 
			 qapp::kde_net_wm_system_tray_window_for, 0, 1L,
			 FALSE, XA_WINDOW, &type, &format, &nitems, &extra,
			 &data);
      
      if(data != NULL);
      {
	XFree(data);
	data = NULL;
      }	
	
      if(nitems)
      {
	nitems = 0;
	continue;
      }	
	
      ap.removeAt(i--);
      XKillClient(QX11Info::display(), cur->w);
      delete cur;
      place = TRUE;
    }
  }
  if(place)
    place_clients();

  paintBG();
}

void apbar::resizeEvent(QResizeEvent *)
{
  paintBG();
}

