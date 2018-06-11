/****************************************************************************
 **
 **				xwindow.cpp
 **			=========================
 **
 **  begin                : 2001 based on qlwm
 **  copyright            : (C) 2001 - 2007 by Haydar Alkaduhimi, 
 **  email                : haydar@haydarnet.nl
 **  License              : GPL
 **
 **  This is constructed for every normal window
 **
 **  Special Thanks to Alexander Linden <alinden@gmx.de>
 **
 ***************************************************************************/

#include "defs.h"
#include "defaults.h"
#include "qapp.h"
#include "winfo.h"
#include "toolbar.h"
#include "rubber.h"
#include "desktp.h"

#include <QBuffer>

bool toolAdded;
bool drawChanges;
int tmpflags = 0;
bool has_own_pos;
int  pre_pos_x;
int  pre_pos_y;

bool xwindow::checkDecoration(void){
  
  //test
#include <X11/Xproto.h>

  //Atom XA_MOTIF_WM_HINTS = 0;
  struct MWMHints {
    ulong mwmFlags;
    ulong mwmFunctions;
    ulong mwmDecorations;
    long mwmInputMode;
  };  


  //
  //
#define MWM_HINTS_FUNCTIONS           (1L << 0)
#define MWM_HINTS_DECORATIONS         (1L << 1)

#define MWM_FUNC_ALL            (1L << 0)
#define MWM_FUNC_RESIZE         (1L << 1)
#define MWM_FUNC_MOVE           (1L << 2)
#define MWM_FUNC_MINIMIZE       (1L << 3)
#define MWM_FUNC_MAXIMIZE       (1L << 4)
#define MWM_FUNC_CLOSE          (1L << 5)

#define MWM_DECOR_ALL                 (1L << 0)
#define MWM_DECOR_BORDER              (1L << 1)
#define MWM_DECOR_RESIZEH             (1L << 2)
#define MWM_DECOR_TITLE               (1L << 3)
#define MWM_DECOR_MENU                (1L << 4)
#define MWM_DECOR_MINIMIZE            (1L << 5)
#define MWM_DECOR_MAXIMIZE            (1L << 6)


  //
  //
 
  MWMHints* hints = NULL;
  //    unsigned long flags = 0;
  Atom atype;
  int aformat;
  unsigned long nitems, bytes_remain;
  
  
  //  XA_MOTIF_WM_HINTS = XInternAtom(QX11Info::display(), "_MOTIF_WM_HINTS", 
  //			  TRUE);
  
  XGetWindowProperty(QX11Info::display(), clientid, qapp::XA_MOTIF_WM_HINTS,
		     0, 5, FALSE, qapp::XA_MOTIF_WM_HINTS, &atype, &aformat,
		     &nitems, &bytes_remain, (uchar **)&hints);
  
  if (hints) {
    cout << "Checking decoration\n";
    
    if (hints->mwmFlags & MWM_HINTS_FUNCTIONS) {
      //bool set_value = (( hints->mwmFunctions & MWM_FUNC_ALL ) == 0 );
      
      if( hints->mwmFunctions & MWM_FUNC_RESIZE ){
	cout<< "MWM_FUNC_RESIZE\n";
	
      }if( hints->mwmFunctions & MWM_FUNC_MOVE ){
	cout<< "MWM_FUNC_MOVE\n";
	
      }if( hints->mwmFunctions & MWM_FUNC_MINIMIZE ){
	cout<< "MWM_FUNC_MINIMIZE\n";
	//	iconify();
      }if( hints->mwmFunctions & MWM_FUNC_MAXIMIZE ){
	cout<< "startMAX\n";
	//t_maximize();
	//startMax = true;
      }if( hints->mwmFunctions & MWM_FUNC_CLOSE ){
	cout<< "MWM_FUNC_CLOSE\n";	
      }
    }


    if (hints->mwmFlags & MWM_HINTS_DECORATIONS) {
      //cout << hints->mwmDecorations << "\n\n";
      bool notdecor =false;
      if(hints->mwmDecorations == 0)
      {
	cout << "no decoration\n";
	hasMenu = false;
	hasMinBtn = false;
	hasMaxBtn = false;
	hasHelpBtn = false;
	decorated = false;

	XFree(hints);
	//XA_MOTIF_WM_HINTS = 0;
	return false;
      }

      if (hints->mwmDecorations & MWM_DECOR_ALL){
	cout << "decore all\n";
	hasTitle = true;
	hasMenu = true;
	hasMinBtn = true;
	hasMaxBtn = true;
	//	hasHelpBtn = true;
	decorated = true;

	XFree(hints);
	//XA_MOTIF_WM_HINTS = 0;
	return true;
      }
      
      
      if (hints->mwmFlags &  MWM_DECOR_TITLE ){
	cout<< "TITLE\n";
	hasTitle = true;
	decorated = false;
	notdecor = false;
      }
      
      if (hints->mwmFlags &  MWM_DECOR_BORDER){
	cout<< "BORDER\n";
	decorated = true;
	notdecor = true;
      }
      
      
      if (hints->mwmFlags & MWM_DECOR_MENU ){
	cout<< "MENU\n";
	hasMenu = true;
	decorated = true;
	notdecor = true;
      }

      if (hints->mwmFlags & MWM_DECOR_MINIMIZE){
	cout<< "MINIMIZE\n";
	hasMinBtn = true;
	decorated = true;
	notdecor = true;
      }
      
      if (hints->mwmFlags  & MWM_DECOR_MAXIMIZE){
	cout<< "MAX\n";
	hasMaxBtn = true;
	decorated = true;
	notdecor = true;
      }
      
      XFree(hints);
      //XA_MOTIF_WM_HINTS = 0;
      return notdecor;
    }
    
    
    XFree(hints);
  }
  //XA_MOTIF_WM_HINTS = 0;
  //test
  return true;
}

xwindow::xwindow(Window w, QWidget *parent) 
  : QWidget(parent) 
{
  startMax = false;
  toolAdded = false;
  has_own_pos = false;
  pre_pos_x = -1;
  pre_pos_y = -1;

  //  bg = new QImage(size(), QImage::Format_RGB32);
  //screenShot = QImage(size(), QImage::Format_RGB32);

  dt = QApplication::desktop();
  titleOrder = defaults::titleOrder;
  hasHelpBtn = false;

  maxstate = 0;
  mrb = NULL;
  clientid = w;
  actpal = TRUE;
  urgpal = FALSE;
  cmapwins = NULL;
  sstate = FALSE;
  tstate = FALSE;
  trsize = FALSE;
  ncmaps = 0;
  withdrawnstate = unmapped = TRUE;
  borderSize  = defaults::lowerborderheight;


  qapp::free_grabbedmouse();


  iconmenu = new QMenu(this);
  Q_CHECK_PTR(iconmenu);
  
  restAct = iconmenu->addAction(*qapp::restorebtnpix, tr("&Restore"), this, 
		       SLOT(t_maximize()));

  iconmenu->addAction(*qapp::minbtnpix,tr("&Iconify"), this, 
		       SLOT(iconify()));
  maxAct = iconmenu->addAction(*qapp::maxbtnpix,tr("Ma&ximize"), this, 
		       SLOT(t_maximize()));
  iconmenu->addSeparator();
  iconmenu->addAction(*qapp::closepix,tr("Close") + "\t\t ALT + F4",
		       this, SLOT(wdestroy()) );
  
  restAct->setEnabled( false );
  maxAct->setEnabled( true );
  
  // get ClassHint
  get_classhint();
  clientname = res_class;
  
  // get flags for WM_COMMAND


	
  char **argv;
  int argc;
  if(XGetCommand(QX11Info::display(), w, &argv, &argc) && argc)
  {
    int ncm=0;
    while(1)
    {
      command += argv[ncm];
      
      if(argc > ++ncm)
	command += ' ';
      else
	break;
    }
		
    if(clientname.isEmpty() && ! command.isEmpty())
    {
      char *base;
      if((base = strrchr(argv[0], '/')) == NULL)
	base = argv[0];
      else
	base++;
      
      clientname = base;
    }	
    XFreeStringList(argv);
  }
  clientname = clientname.simplified();
  pflags = get_clientflags();
  if(pflags & qapp::SmallFrame)
  {
    uborderh = borderSize;
    borderh = 2*uborderh;
  }
  else
  {
    uborderh = defaults::titlebarHeight+borderSize;
    borderh = uborderh+borderSize;
  }
  if(defaults::sideBorders)
  {
    //    cout << "HAS SIDE BORDERS" << endl;
    borderw = 2*borderSize;
  }else
    borderw = 0;
  // check for nonrectangular window
  shaped = (qapp::servershapes)?(query_shape()):(FALSE);
   decorated = checkDecoration();
 
  if(pflags & qapp::NoResize)
  {
    borderh -= borderSize;
    borderw = 0;
  }

  if( shaped || !decorated )
  {
    borderSize = 0;
    uborderh = 0;
    borderh = 0;
    borderw = 0;    
  }
  
  // save window geometry
  Window root;
  uint bwidth,depth;
  XGetGeometry(QX11Info::display(), w, &root, &pos_x, &pos_y, &init_w, 
	       &init_h, &bwidth, &depth);
  base_w = init_w;
  base_h = init_h;
  init_h += borderh;
  init_w += borderw;
	
  // reparent
  XSetWindowBorderWidth(QX11Info::display(), w, 0);
  XSetWindowBorderWidth(QX11Info::display(), winId(), 0);
  //  XReparentWindow(QX11Info::display(), w, winId(), 0, uborderh);
  XReparentWindow(QX11Info::display(), w, winId(), borderw/2, uborderh);

  XAddToSaveSet(QX11Info::display(), w);
  
  // get TransientForHint
  transfor = None;
  XGetTransientForHint(QX11Info::display(), w, &transfor);
  
  // set Font
  setFont(defaults::borderfont);
  
  // get colormap and check for WM_COLORMAP_WINDOWS property
  get_colormaps();
  
  // get WM_CLIENT_MACHINE
  XTextProperty prop;
  if(XGetWMClientMachine(QX11Info::display(), w, &prop) && prop.nitems 
     && prop.format == 8)
  {
    clientfqdn = (char *)prop.value;
    
    if(defaults::showclientmachines)
    {
      int pos = clientfqdn.indexOf('.');
      if(pos == -1)
	clientmachine = clientfqdn;
      else	
	clientmachine = clientfqdn.left(pos);
    }
  }	

  // get WMHints
  get_wmhints();
  
  // get WMNormalhints
  get_wmnormalhints();
  
  int cw = init_w;
  int ch = init_h;
  getsize(&cw, &ch);
  
  // window position
  if( (wmnflags & USPosition) || (wmnflags & PPosition) )
  {
    if(has_own_pos)
    {
      pos_x = pre_pos_x;
      pos_y = pre_pos_y;
    }

    if(wmnflags & PWinGravity && 
       (wingrav == SouthWestGravity || wingrav == SouthEastGravity)){
      pos_y -= uborderh;
      if(defaults::sideBorders)
      {
	pos_x -= defaults::lowerborderheight;
      }
    }

  }
  
  //a transient window with program specified position looks like a dialog box
  // otherwise use autoplacement
  else if(! defaults::start_restart && (transfor == None || ! (wmnflags & 
							       PPosition)))
  {
//      int cx = QApplication::desktop()->screenGeometry( QApplication::desktop()->screenNumber(this) ).x();
//      int cy = QApplication::desktop()->screenGeometry( QApplication::desktop()->screenNumber(this) ).y();
    if(qapp::next_x+cw > dt->width())
    {
	  // pos_x = 0;
      pos_x = QApplication::desktop()->screenGeometry( QApplication::desktop()->screenNumber(this) ).x();
      if(cw < dt->width())
	qapp::next_x = 2*defaults::titlebarHeight;
    }
    else
    {
      pos_x = qapp::next_x;
      qapp::next_x += 2*defaults::titlebarHeight;
    }	
    
    int sy,ey;
    if(defaults::toolbar_top)
    {
      sy = defaults::tb_height;
      ey = dt->height();
    }
    else
    {
	  //sy = 0;
      sy = QApplication::desktop()->screenGeometry( QApplication::desktop()->screenNumber(this) ).y();
      ey = dt->height()-defaults::tb_height;
    }
    
    if(qapp::next_y+ch > ey)
    {
      pos_y = sy;
      if(ch < dt->height())
	qapp::next_y = sy+2*defaults::titlebarHeight;
    }
    else
    {
      pos_y = qapp::next_y;
      qapp::next_y += 2*defaults::titlebarHeight;
    }
  }
  
  // move and resize
  XResizeWindow(QX11Info::display(), clientid, cw-borderw, ch-borderh);

  // Small hack for java based progeams.
  resize(cw, ch);
  XMoveWindow(QX11Info::display(), clientid, borderw/2, uborderh);
 
  if(pos_y < 0)
	  pos_y = QApplication::desktop()->screenGeometry( QApplication::desktop()->screenNumber(this) ).y();
    //pos_y = 0;

  if(! defaults::start_restart)
  {
    if(pos_x < 0)
	  pos_x = QApplication::desktop()->screenGeometry( QApplication::desktop()->screenNumber(this) ).x();
      //pos_x = 0;

    while(pos_x > dt->width())
      pos_x -= dt->width();
  
  }

  setGeometry(pos_x, pos_y, cw, ch);
  //setGeometry(pos_x, pos_y, cw+borderw, ch+borderh);
  
  // overwrite Qt-defaults because we need SubstructureNotifyMask
  XSelectInput(QX11Info::display(), winId(),
	       KeyPressMask | KeyReleaseMask |
	       ButtonPressMask | ButtonReleaseMask |
	       KeymapStateMask |
	       ButtonMotionMask |
	       PointerMotionMask |
	       EnterWindowMask | LeaveWindowMask |
	       FocusChangeMask |
	       ExposureMask |
	       StructureNotifyMask |
	       SubstructureRedirectMask |
	       SubstructureNotifyMask);

  XSetWindowAttributes attr;
  //attr.event_mask = ColormapChangeMask;
  attr.event_mask = ColormapChangeMask|PropertyChangeMask;
  XChangeWindowAttributes(QX11Info::display(), w, CWEventMask, &attr);

  // get WM protocols
  getwmprotocols();

  // create window borders
  create_wborder();
  
  // add client to lookup tables
  
  qapp::cwindows.insert(w, this);
  qapp::pwindows.insert(winId(), this);
  
  // get WM_NAME and set window title
  get_wmname();

  if(shaped)
    reshape();

  // init autofocus timer
  
  focustimer = new QTimer(this);
  Q_CHECK_PTR(focustimer);
  focustimer->setSingleShot(TRUE);
  connect(focustimer, SIGNAL(timeout()), SLOT(raise()));
  
  tfocustimer = new QTimer(this);  // used for tiled mode
  Q_CHECK_PTR(tfocustimer);
  tfocustimer->setSingleShot(TRUE);
  connect(tfocustimer, SIGNAL(timeout()), SLOT(tile_maximize()));

    
  screenshotTimer = new QTimer(this);  // used screenshot
  Q_CHECK_PTR(screenshotTimer);
  screenshotTimer->setSingleShot(TRUE);
  connect(screenshotTimer, SIGNAL(timeout()), SLOT( updateScreenShot() ));
  

  bgTimer = new QTimer(this);  // used screenshot
  Q_CHECK_PTR(bgTimer);
  bgTimer->setSingleShot(TRUE);
  connect(bgTimer, SIGNAL(timeout()), SLOT( repaintBG() ));


  qapp::send_configurenotify(this);
  
  if(! urgent && ! defaults::starturgent)
  {
    setinactive();
  }
  else 
  {
    seturgent();
  }	
  
  if(defaults::start_restart)  // restore original state
  {
    int clstate = get_clientstate();
    
    if(clstate == IconicState)
    {
      iconify();
    }	
    else if(clstate == WithdrawnState)
    {
      withdraw();
    }
    else map();
  }	
  else map();

  if(defaults::start_restart)  // restore original state
    updateScreenShot();
  else
    trayUpdateScreenShot();
  //  if( !screenshotTimer->isActive() )
  //screenshotTimer->start ( 250 );
  //repaintBG();
  
  XSetInputFocus(QX11Info::display(), client_id(),
  		 RevertToPointerRoot, CurrentTime);
  //setactive();
  //qapp::focus_window(this);

#ifdef DEBUGMSG
  logmsg << "class xwindow constructed (WId:" << winId() << ")\n";
#endif	
}




void xwindow::moveEvent( QMoveEvent *e)
{
  QWidget::moveEvent(e);

  /*  
  QRect oldRect = QRect(e->oldPos().x(), e->oldPos().y(), width(), height());
  if(!shaped || decorated)
   qapp::setUpdateRect( oldRect, this); 
  */
}


void xwindow::resizeEvent( QResizeEvent * e )
{
  QWidget::resizeEvent(e);
}
 //void xwindow::paintEvent ( QPaintEvent *e)


void xwindow::trayUpdateScreenShot()
{
  if(!screenshotTimer->isActive())
    screenshotTimer->start( 50 );
  else
  {
    screenshotTimer->stop();
    screenshotTimer->start( 50 );
  }
}

void xwindow::trayRepaintBG()
{
  if(bgTimer->isActive())
  {
    bgTimer->stop();
    bgTimer->start(50);
  }else
    bgTimer->start(50);
}

bool updatingScreenShot;

void xwindow::updateScreenShot(void)
{
  if(updatingScreenShot)
    return;

  if( shaped || !decorated )
    return;

  repaintBG();

  updatingScreenShot = true;
  //screenshotTimer->stop();
  QPixmap sShot = QPixmap::grabWindow(winId());
  //QPixmap sShot = QPixmap::grabWindow(client_id());

  //  QByteArray bytes;
  QBuffer buffer(&screenBytes);
  buffer.open(QIODevice::WriteOnly);
  sShot.save(&buffer, "PNG"); // writes pixmap into bytes in PNG format  /*
  tb_pb->setScreenPixmap(this, sShot);

  updatingScreenShot = false;
}

bool repaintingBG;
void xwindow::repaintBG()
{
  if(repaintingBG)
    return;

  if( shaped || !decorated )
    return;

  repaintingBG = true;
     
  if(defaults::bordersTransparency < 255)
  {
    QImage *bg = new QImage(size(), QImage::Format_RGB32);
    {
      xwindow *client;
      
      QPainter p(bg);
      QRectF target0(0,0, width(), height());
      QRectF source0(geometry().x(), geometry().y(), geometry().width(), 
		     geometry().height());
      p.drawImage(target0, qapp::Desktop->desktopBG, source0);
      
      // foreach(client, clients)
      for (int i = clients.size()-1; i >=0 ; i--)
      {
	client = clients.at(i);
	
	bool curdesk;
	int dwidth = QApplication::desktop()->width();
	//int dheight = QApplication::desktop()->height();
	curdesk = client->x() <= dwidth && client->x() >= 0;
	
	if(client->isVisible() && curdesk && (client != this))
	{
	
	  int cx = client->x();
	  int cy = client->y();
	  int cw = client->width();
	  int ch = client->height();
	  
	  QRect s(cx, cy, cw, ch);
	  QRect t(x(), y(), width(), height());
	  
	  if(t.intersects(s))
	  {
	    QRect intrs = t & s;
	    cw = intrs.width();
	    ch = intrs.height();

	    
	    if(x() >= client->x())
	    {
	      cx = 0;
	    }
	    else
	    {
	      cx = client->x() - x();
	    }
	    if(y() >= client->y())
	    {
	      cy = 0;
	    }
	    else
	    {
	      cy = client->y() - y();
	    }

	    int ix = 0;
	    int iy = 0;

	    if(x() > client->x())
	      ix = x() - client->x();
	    if(y() > client->y())
	      iy = y() - client->y();
	    
	    QRect irect(ix, iy, client->width()-ix, client->height()-iy);
	    QImage img = QImage::fromData(client->screenBytes);
	    img = img.copy(irect);

	    p.drawImage(QRect(cx,cy,irect.width(),irect.height()), img, 
			QRect(0, 0, irect.width(), irect.height()));
	  }
	}
      }
      
      p.end();
    }

    QImage bgImg(size(),
		 QImage::Format_RGB32);
    
    //  QColor semiTransparentColor = curPal.button().color();
    //  semiTransparentColor.setAlpha(175);
    
    QPainter painter(&bgImg);

    QRect target(0,0,geometry().width(), geometry().height());
    if(!bg->isNull())
      painter.drawImage(target, *bg);

    // BORDERS
      int tl_width = 0;
      int tr_width = 0;
      int topHeight = 0;
    if(actpal)
    {
      if(defaults::topBorder && (maxstate != 1))
	topHeight = defaults::titlebarHeight+defaults::lowerborderheight;
      else
	topHeight = defaults::titlebarHeight;

      if(defaults::topBorder && (maxstate != 1))
      {
	if(!qapp::border_tlimage->isNull())
	{
	  tl_width = qapp::border_tlimage->width();

	  painter.drawImage(0,0, *qapp::border_tlimage);
	}
      
	if(!qapp::border_trimage->isNull())
	{
	  tr_width = qapp::border_trimage->width();
	  painter.drawImage(QRect(width()- tr_width, 0, tr_width, topHeight)
			    , *qapp::border_trimage);
	}
      
	if(!qapp::topborderimage->isNull())
	{
	  painter.drawImage(QRect(tl_width, 0 , width()- tl_width - tr_width,
				  qapp::topborderimage->height()),
			    *qapp::topborderimage);
	}
      }

      int bl_width = 0;
      int br_width = 0;
      int bl_height = 0;
      int br_height = 0;
      if(!qapp::border_blimage->isNull())
      {
	bl_width = qapp::border_blimage->width();
	bl_height = qapp::border_blimage->height();
	painter.drawImage(QRect(0, height()-bl_height, bl_width, bl_height),
			  *qapp::border_blimage);
      }


      if(!qapp::border_brimage->isNull())
      {
	br_width = qapp::border_brimage->width();
	br_height = qapp::border_brimage->height();
	painter.drawImage(QRect(width()- br_width, height() - br_height, 
				br_width, br_height), *qapp::border_brimage);
      }

      if(!qapp::border_leftimage->isNull())
      {
	painter.drawImage(QRect(0, topHeight, defaults::lowerborderheight, 
				height() - topHeight - bl_height),
			  *qapp::border_leftimage);
      }

      if(!qapp::border_rightimage->isNull())
      {
	painter.drawImage(QRect(width() -defaults::lowerborderheight,
				topHeight, defaults::lowerborderheight, 
				height() - topHeight - br_height),
			  *qapp::border_rightimage);
      }

      if(!qapp::bottomborderimage->isNull())
      {
	painter.drawImage(QRect(bl_width, height()
				-defaults::lowerborderheight,
				width() - bl_width - br_width, 
				defaults::lowerborderheight),
			  *qapp::bottomborderimage);
      }

    }else{
      if(defaults::topBorder && (maxstate != 1))
	topHeight = defaults::titlebarHeight+defaults::lowerborderheight;
      else
	topHeight = defaults::titlebarHeight;

      if(defaults::topBorder && (maxstate != 1))
      {
	if(!qapp::uborder_tlimage->isNull())
	{
	  tl_width = qapp::uborder_tlimage->width();

	  painter.drawImage(0,0, *qapp::uborder_tlimage);
	}
      
	if(!qapp::uborder_trimage->isNull())
	{
	  tr_width = qapp::uborder_trimage->width();
	  painter.drawImage(QRect(width()- tr_width, 0, tr_width, topHeight)
			    , *qapp::uborder_trimage);
	}
      
	if(!qapp::utopborderimage->isNull())
	{
	  painter.drawImage(QRect(tl_width, 0 , width()- tl_width - tr_width,
				  qapp::utopborderimage->height()),
			    *qapp::utopborderimage);
	}
      }

      int bl_width = 0;
      int br_width = 0;
      int bl_height = 0;
      int br_height = 0;
      if(!qapp::uborder_blimage->isNull())
      {
	bl_width = qapp::uborder_blimage->width();
	bl_height = qapp::uborder_blimage->height();
	painter.drawImage(QRect(0, height() - bl_height, bl_width, bl_height)
			  , *qapp::uborder_blimage);
      }


      if(!qapp::uborder_brimage->isNull())
      {
	br_width = qapp::uborder_brimage->width();
	br_height = qapp::uborder_brimage->height();
	painter.drawImage(QRect(width()- br_width, height() - br_height, 
				br_width, br_height),
			  *qapp::uborder_brimage);
      }

      if(!qapp::uborder_leftimage->isNull())
      {
	painter.drawImage(QRect(0, topHeight, defaults::lowerborderheight, 
				height() - topHeight - bl_height), 
			  *qapp::uborder_leftimage);
      }

      if(!qapp::uborder_rightimage->isNull())
      {
	painter.drawImage(QRect(width() -defaults::lowerborderheight,
				topHeight, defaults::lowerborderheight, 
				height() - topHeight - br_height),
			  *qapp::uborder_rightimage);
      }

      if(!qapp::ubottomborderimage->isNull())
      {
	painter.drawImage(QRect(bl_width, height() 
				- defaults::lowerborderheight,
				width() - bl_width - br_width, 
				defaults::lowerborderheight),
			  *qapp::ubottomborderimage);
      }


    }
    // BORDERS


    int title_x = 0;
    int title_y = 0;
    int titleHeight = 0;
    
    if(defaults::topBorder && (maxstate != 1))
    {
      title_x = defaults::lowerborderheight;
      title_y = defaults::lowerborderheight;
    }
    // TITLEBAR
    if(QApplication::isRightToLeft())
    {
      //      painter.drawPixmap(0, 0, width(), defaults::titlebarHeight, 
      //			 *qapp::titlepix);
      if(actpal)
      {
	painter.drawImage(QRect(title_x,
				title_y,
				width() - qapp::titlerightpix->width() 
				- (2*title_x),
				defaults::titlebarHeight), *qapp::titlepix);
	painter.drawImage(QRect(width()-qapp::titlerightpix->width()
				- title_x, 
				title_y, 
				qapp::titlerightpix->width(),
				defaults::titlebarHeight),
			  *qapp::titlerightpix);
      }else{
	painter.drawImage(QRect(title_x,
				title_y,
				width()-qapp::untitlerightpix->width()
				- (2*title_x),
				defaults::titlebarHeight),
			  *qapp::untitlepix);
	painter.drawImage(QRect(width()-qapp::untitlerightpix->width() 
				- title_x, 
				title_y, 
				qapp::untitlerightpix->width(),
				defaults::titlebarHeight),
			  *qapp::untitlerightpix);
      }

    }else{
      if(actpal)
      {
	painter.drawImage(QRect(title_x,
				title_y,
				width() - qapp::titlerightpix->width()
				- (2*title_x),
				defaults::titlebarHeight), *qapp::titlepix);
	painter.drawImage(QRect(width()-qapp::titlerightpix->width() 
				- title_x, 
				title_y, 
				qapp::titlerightpix->width(),
				defaults::titlebarHeight),
			  *qapp::titlerightpix);
      }else{
	painter.drawImage(QRect(title_x,
				title_y,
				width()-qapp::untitlerightpix->width() 
				- (2*title_x),
				defaults::titlebarHeight),
			  *qapp::untitlepix);
	painter.drawImage(QRect(width()-qapp::untitlerightpix->width()
				- title_x, 
				title_y, 
				qapp::untitlerightpix->width(),
				defaults::titlebarHeight),
			  *qapp::untitlerightpix);
      }
    }



    if(qapp::titlepix->isNull())
      painter.fillRect(target, curColor);

    painter.end();



    QPalette pal = palette();
    pal.setBrush(QPalette::Background, bgImg);

    if(actpal)
      pal.setBrush(QPalette::Foreground, defaults::active_fg);
    else
      pal.setBrush(QPalette::Foreground, defaults::inactive_fg);

    pal.setBrush(QPalette::Button,bgImg);
    pal.setBrush(QPalette::Window, bgImg);
    setPalette(pal);

    delete bg;
    setAutoFillBackground(true);
  }else{
    QPalette pal = palette();
    pal.setBrush(QPalette::Background, curColor);
    pal.setBrush(QPalette::Button, curColor);
    pal.setBrush(QPalette::Window, curColor);
    setPalette(pal);
    setAutoFillBackground(true);
  }
  repaintingBG = false;
}

void xwindow::create_wborder(void)
{
  lbdr = NULL;
  ubdr = NULL;
  slbdr = NULL;
  srbdr = NULL;

  if( shaped || !decorated )
    return;


  layout = new QVBoxLayout(this);
  Q_CHECK_PTR(layout);
  layout->setMargin(0);

  hlayout = new QHBoxLayout(0);
  Q_CHECK_PTR(hlayout);
  hlayout->setMargin(0);

  if(pflags & qapp::SmallFrame)
  {
    /**********************************************************
     *
     * It is a SMALL frame, no uborder but midmove instead
     *
     *********************************************************/
    midmove = new wframe(this);
    Q_CHECK_PTR(midmove);
    midmove->setFixedHeight(borderSize);
    layout->addWidget(midmove);
    
    connect(midmove, SIGNAL(left_press(QMouseEvent *)), 
	    SLOT(press_move(QMouseEvent *)));
    connect(midmove, SIGNAL(left_release(QMouseEvent *)), 
	    SLOT(release_move(QMouseEvent *)));
    connect(midmove, SIGNAL(right_press()), SLOT(s_maximize()));
    connect(midmove, SIGNAL(mid_press()), SLOT(show_info()));
    connect(midmove, SIGNAL(mouse_move(QMouseEvent *)), 
	    SLOT(move_move(QMouseEvent *)));
  }
  else
  {
    // Create Upper Frame
    
    if(transfor != None)
    {
      titleOrder.removeAll("MinMax");
      titleOrder.removeAll("Minimize");
      titleOrder.removeAll("Maximize");
    }
    if(!hasHelpBtn)
      titleOrder.removeAll("Help");

    //    ubdr = new uborder((transfor == None), this);
    ubdr = new uborder(this, titleOrder);
    Q_CHECK_PTR(ubdr);
    layout->addWidget(ubdr);
    midmove = ubdr->midframe;
		
    if(transfor == None)
    {
      if(titleOrder.contains("MinMax"))
      {
	connect(ubdr->minmaxframe, SIGNAL(right_clicked()), 
		SLOT(t_maximize()));
	connect(ubdr->minmaxframe, SIGNAL(mid_clicked()), 
		SLOT(toggle_tiled()));
	connect(ubdr->minmaxframe, SIGNAL(left_clicked()), SLOT(iconify()));
      }
      if(titleOrder.contains("Minimize"))
      {
	connect(ubdr->minframe, SIGNAL(left_clicked()), SLOT(iconify()));
      }
      if(titleOrder.contains("Maximize"))
      {
	connect(ubdr->maxframe, SIGNAL(left_clicked()), SLOT(t_maximize()));
      }
    }
    if(titleOrder.contains("Menu"))
    {
      connect(ubdr->menuframe, SIGNAL(left_press()), SLOT( menuexec() ));
    }

    if(hasHelpBtn && titleOrder.contains("Help")){
      connect(ubdr->helpframe, SIGNAL(left_clicked()), SLOT(showhelp() ));
    }
    // Connect buttons on the Upper frame
    connect(ubdr->closeframe, SIGNAL(left_clicked()), SLOT(wdestroy()));
    connect(midmove, SIGNAL(right_press()), SLOT(s_maximize()));
    connect(midmove, SIGNAL(left_press(QMouseEvent *)), 
	    SLOT(press_move(QMouseEvent *)));
    connect(midmove, SIGNAL(left_release(QMouseEvent *)), 
	    SLOT(release_move(QMouseEvent *)));
    connect(midmove, SIGNAL(mid_press()), SLOT(show_info()));
    connect(midmove, SIGNAL(mouse_move(QMouseEvent *)), 
	    SLOT(move_move(QMouseEvent *)));

    if( defaults::topBorder && !(pflags & qapp::NoResize))
    {
      /********************************************************
       *
       * Top Left and Upper Left Frame
       *
       *******************************************************/
      connect(ubdr->topleftframe, SIGNAL(press(QMouseEvent *)), 
	      SLOT(press_topleft(QMouseEvent *)));
      connect(ubdr->topleftframe, SIGNAL(release(QMouseEvent *)), 
	      SLOT(release_topleft(QMouseEvent *)));
      connect(ubdr->topleftframe, SIGNAL(mouse_move(QMouseEvent *)), 
	    SLOT(move_topleft(QMouseEvent *)));

      connect(ubdr->upperleftframe, SIGNAL(press(QMouseEvent *)), 
	      SLOT(press_topleft(QMouseEvent *)));
      connect(ubdr->upperleftframe, SIGNAL(release(QMouseEvent *)), 
	      SLOT(release_topleft(QMouseEvent *)));
      connect(ubdr->upperleftframe, SIGNAL(mouse_move(QMouseEvent *)), 
	    SLOT(move_topleft(QMouseEvent *)));


      /********************************************************
       *
       * Upper Frame
       *
       *******************************************************/
      connect(ubdr->topframe, SIGNAL(press(QMouseEvent *)), 
	      SLOT(press_topborder(QMouseEvent *)));
      connect(ubdr->topframe, SIGNAL(release(QMouseEvent *)), 
	      SLOT(release_topborder(QMouseEvent *)));
      connect(ubdr->topframe, SIGNAL(mouse_move(QMouseEvent *)), 
	      SLOT(move_topborder(QMouseEvent *)));


      /********************************************************
       *
       * Top Right and Upper Right Frame
       *
       *******************************************************/
      connect(ubdr->upperrightframe, SIGNAL(press(QMouseEvent *)), 
	      SLOT(press_topright(QMouseEvent *)));
      connect(ubdr->upperrightframe, SIGNAL(release(QMouseEvent *)), 
	      SLOT(release_topright(QMouseEvent *)));
      connect(ubdr->upperrightframe, SIGNAL(mouse_move(QMouseEvent *)), 
	      SLOT(move_topright(QMouseEvent *)));

      connect(ubdr->toprightframe, SIGNAL(press(QMouseEvent *)), 
	      SLOT(press_topright(QMouseEvent *)));
      connect(ubdr->toprightframe, SIGNAL(release(QMouseEvent *)), 
	      SLOT(release_topright(QMouseEvent *)));
      connect(ubdr->toprightframe, SIGNAL(mouse_move(QMouseEvent *)), 
	      SLOT(move_topright(QMouseEvent *)));
    }
  }


  if(pflags & qapp::NoResize)
    layout->addStretch();

  if(!defaults::sideBorders)
    layout->addStretch();
  else
    layout->setSpacing(0);

  if(! (pflags & qapp::NoResize))
  {

    // We Have Borders.
    // Check if we have also side borders??
    if(defaults::sideBorders)
    {
      layout->addLayout(hlayout);


      if(QApplication::isRightToLeft())
      {
	srbdr = new srborder(this);
	Q_CHECK_PTR(srbdr);
	hlayout->addWidget(srbdr);
      }else{
	slbdr = new slborder(this);
	Q_CHECK_PTR(slbdr);
	hlayout->addWidget(slbdr);
      }

      hlayout->addStretch();

      if(QApplication::isRightToLeft())
      {
	slbdr = new slborder(this);
	Q_CHECK_PTR(slbdr);
	hlayout->addWidget(slbdr);
      }else{
	srbdr = new srborder(this);
	Q_CHECK_PTR(srbdr);
	hlayout->addWidget(srbdr);
      }

      connect(slbdr->lowerframe, SIGNAL(press(QMouseEvent *)), 
	      SLOT(press_leftresize(QMouseEvent *)));
      connect(slbdr->lowerframe, SIGNAL(release(QMouseEvent *)), 
	      SLOT(release_leftresize(QMouseEvent *)));
      connect(slbdr->lowerframe, SIGNAL(mouse_move(QMouseEvent *)), 
	    SLOT(move_leftresize(QMouseEvent *)));

      connect(slbdr->midframe, SIGNAL(press(QMouseEvent *)), 
	      SLOT(press_leftborder(QMouseEvent *)));
      connect(slbdr->midframe, SIGNAL(release(QMouseEvent *)), 
	      SLOT(release_leftborder(QMouseEvent *)));
      connect(slbdr->midframe, SIGNAL(mouse_move(QMouseEvent *)), 
	    SLOT(move_leftborder(QMouseEvent *)));


      connect(srbdr->lowerframe, SIGNAL(press(QMouseEvent *)), 
	      SLOT(press_rightresize(QMouseEvent *)));
      connect(srbdr->lowerframe, SIGNAL(release(QMouseEvent *)), 
	      SLOT(release_rightresize(QMouseEvent *)));
      connect(srbdr->lowerframe, SIGNAL(mouse_move(QMouseEvent *)), 
	      SLOT(move_rightresize(QMouseEvent *)));

      connect(srbdr->midframe, SIGNAL(press(QMouseEvent *)), 
	      SLOT(press_rightborder(QMouseEvent *)));
      connect(srbdr->midframe, SIGNAL(release(QMouseEvent *)), 
	      SLOT(release_rightborder(QMouseEvent *)));
      connect(srbdr->midframe, SIGNAL(mouse_move(QMouseEvent *)), 
	      SLOT(move_rightborder(QMouseEvent *)));




    }
    // Now Add Lower Border
    lbdr = new lborder(this);
    Q_CHECK_PTR(lbdr);
    layout->addWidget(lbdr);
		
    connect(lbdr->leftframe, SIGNAL(press(QMouseEvent *)), 
	    SLOT(press_leftresize(QMouseEvent *)));
    connect(lbdr->leftframe, SIGNAL(release(QMouseEvent *)), 
	    SLOT(release_leftresize(QMouseEvent *)));
    connect(lbdr->leftframe, SIGNAL(mouse_move(QMouseEvent *)), 
	    SLOT(move_leftresize(QMouseEvent *)));
    connect(lbdr->rightframe, SIGNAL(press(QMouseEvent *)), 
	    SLOT(press_rightresize(QMouseEvent *)));
    connect(lbdr->rightframe, SIGNAL(release(QMouseEvent *)), 
	    SLOT(release_rightresize(QMouseEvent *)));
    connect(lbdr->rightframe, SIGNAL(mouse_move(QMouseEvent *)), 
	    SLOT(move_rightresize(QMouseEvent *)));
    connect(lbdr->midframe, SIGNAL(press(QMouseEvent *)), 
	    SLOT(press_midresize(QMouseEvent *)));
    connect(lbdr->midframe, SIGNAL(release(QMouseEvent *)), 
	    SLOT(release_midresize(QMouseEvent *)));
    connect(lbdr->midframe, SIGNAL(mouse_move(QMouseEvent *)), 
	    SLOT(move_midresize(QMouseEvent *)));
  }	
  setLayout(layout);

  if(startMax)
  {
    cout << "Should maximize it\n" << endl;
    maxstate = 0;
    t_maximize();
  }
}

void xwindow::showhelp(void){
  if (hasHelpBtn) {
    XEvent ev;
    long mask;
    
    memset(&ev, 0, sizeof(ev));
    ev.xclient.type = ClientMessage;
    ev.xclient.window = clientid;
    ev.xclient.message_type = qapp::wm_protocols;
    ev.xclient.format = 32;
    ev.xclient.data.l[0] = qapp::net_wm_context_help;
    ev.xclient.data.l[1] = CurrentTime;
    mask = 0L;
    
    if (clientid == QX11Info::appRootWindow())
      mask = SubstructureRedirectMask;	    /* magic! */
    XSendEvent(QX11Info::display(), clientid, False, mask, &ev);

  }

}


void xwindow::menuexec(void){ 
  if( QApplication::isRightToLeft() )
  {
    QSize s(iconmenu->sizeHint());
    iconmenu->popup(QPoint(x()+width()-s.width(),y()+ uborderh));
  }else
    iconmenu->popup( QPoint(x(),y()+ uborderh) );
}

// adjust for possible width and height including border
void xwindow::getsize(int *pw, int *ph)   
{
  int w = *pw;
  int h = *ph;

  if(inc_w == 0)
    w = init_w;

  if(inc_h == 0)
    h = init_h;

  if(w > max_w)
    w = max_w;

  if(h > max_h)
    h = max_h;
  
  if(w < min_w)
    w = min_w;
  
  if(h < min_h)
    h = min_h;
  
  if(inc_w > 1)
  {
    int i = (w-base_w)/inc_w;
    w = base_w+i*inc_w;
    
    if(w < min_w)
      w += inc_w;
  }

  if(inc_h > 1)	
  {
    int j = (h-base_h)/inc_h;
    h = base_h+j*inc_h;
    
    if(h < min_h)
      h += inc_h;
  }	
  *pw = w;
  *ph = h;
}

void xwindow::enable_disable_menu(void)
{
  if(maxstate == 1)
  {
    restAct->setEnabled( true );
    maxAct->setEnabled( false );
    
    if(ubdr != NULL)
    {
      //      ubdr->set_max(true);
      if(titleOrder.contains("Maximize"))
      {
	ubdr->maxframe->setPixmap(*qapp::restorebtnpix);
      }
    }
  }
  else
  {
    restAct->setEnabled( false );
    maxAct->setEnabled( true );
    if(ubdr != NULL)
    {
      //      ubdr->set_max(false);
      if(titleOrder.contains("Maximize"))
      {
	ubdr->maxframe->setPixmap(*qapp::maxbtnpix);
      }
    }
  }
}

// client requested resize
void xwindow::resize_request(int cx, int cy, int cw, int ch)
{
  /*
  if(cy-=uborderh < 0)
    cy = 0;
  
  if(cx-=(borderh/2) < 0)
    cx = 0;
  */

  if(cy < 0)
    cy = 0;
  
  //  if(cx < 0)
  //    cx = 0;

  ch += borderh;
  cw += borderw;
  
  getsize(&cw, &ch);
  
  setGeometry(cx, cy, cw, ch);
  XResizeWindow(QX11Info::display(), clientid, cw-borderw, ch-borderh);

  if(maxstate == 1)
    maximizeFrame(false);

  maxstate = 0;
  enable_disable_menu();
  /*
  //repaintBG();
  if( !screenshotTimer->isActive() )
    screenshotTimer->start(50);
  */
}

// dimensions include borders
void xwindow::resize_client(int px, int py, int pw, int ph)
{
  int nw = width();
  int nh = height();

  int brdrh = borderh;
  int brdrw = borderw;

  if(shaped || !decorated || (pflags & qapp::NoResize) ){
    brdrw = 0;
    brdrh = 0;
  }

  if(px != x() || py != y() || pw != nw || ph != nh)  // parent
    setGeometry(px, py, pw, ph);

  if(pw != nw || ph != nh) // client
  {
#ifdef DEBUGMSG
    logmsg << "resize child window (WId:" << clientid << ")\n";
#endif
    //    XResizeWindow(QX11Info::display(), clientid, pw-borderw,
    //		  ph-borderh);
    XResizeWindow(QX11Info::display(), clientid, pw-brdrw,
		  ph-brdrh);
  }
  //repaintBG();
  trayUpdateScreenShot();
  /*
  if( !screenshotTimer->isActive() )
    screenshotTimer->start(50);
  */
}

void xwindow::maximizeFrame(bool max)
{
  if(max)
  {
    int tstflags = 0;
    tmpflags = pflags;
    tstflags  |= qapp::NoResize;
    pflags = tstflags;
    //set_pflags(tstflags);

    //    layout->addStretch();
    //hlayout->addStretch();
    
    borderh = defaults::titlebarHeight;
    uborderh = defaults::titlebarHeight;
    borderSize = 0;
    borderw = 0;

    if( shaped || !decorated )
    {
      borderSize = 0;
      uborderh = 0;
      borderh = 0;
      borderw = 0;    
    }

    if(defaults::topBorder)
      if(ubdr != NULL)
	ubdr->set_max(true);
    if(defaults::sideBorders)
    {
      if(srbdr!=NULL)
	srbdr->setFixedWidth(0);
      if(slbdr!=NULL)
	slbdr->setFixedWidth(0);
    }
    if(lbdr!=NULL)
      lbdr->setFixedHeight(0);
    
  }else
  {
    int tstflags = 0;
    //pflags = tmpflags;
    tstflags = tmpflags;
    //    set_pflags(tstflags);
    borderSize = defaults::lowerborderheight;
    //borderh =  uborderh + borderSize;
    if(defaults::topBorder)
      uborderh =  uborderh +  borderSize;

    borderh =  uborderh + borderSize;

    if(defaults::sideBorders)
      borderw = 2* borderSize;
    else
      borderw = 0;

    if( shaped || !decorated )
    {
      borderSize = 0;
      uborderh = 0;
      borderh = 0;
      borderw = 0;    
    }

    if(defaults::topBorder)
      if(ubdr != NULL)
	ubdr->set_max(false);

    if(defaults::sideBorders)
    {
      if(slbdr != NULL)
	slbdr->setFixedWidth(borderSize);
      if(srbdr != NULL)
	srbdr->setFixedWidth(borderSize);
    }
    if(lbdr != NULL)
     lbdr->setFixedHeight(borderSize);
    
    XMoveWindow(QX11Info::display(), clientid, borderw/2, uborderh);
  }
}

void xwindow::t_maximize(void)
{
  int cw,ch;
	
  if(qapp::smode)
  {
    focus_mouse();
    //    updateScreenShot();
    trayUpdateScreenShot();
    //repaintBG();
    return;
  }

  if(maxstate != 1)  // maximize
  {
    maximizeFrame(true);
    if(maxstate == 0)
    {
      icx = x();
      icy = y();
      icw = width();
      ich = height();
    }

    // not user configured
    if(defaults::tmx1 == -1 || tstate || ((pflags & qapp::NoTile) && 
					  qapp::is_tileddesk()))
    {
      cw = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen()).width();//dt->width();
      //      ch = dt->height()-defaults::tb_height-1;
      ch = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen()).height();
      if(QApplication::desktop()->screenNumber(this) == QApplication::desktop()->primaryScreen())
	      ch = ch - defaults::tb_height;
      //ch = dt->height()-defaults::tb_height;
      //getsize(&cw, &ch);
      int cx = QApplication::desktop()->screenGeometry( QApplication::desktop()->screenNumber(this) ).x();
      int cy = QApplication::desktop()->screenGeometry( QApplication::desktop()->screenNumber(this) ).y();
      //resize_client(0, defaults::toolbar_top?defaults::tb_height+1:0, cw, ch);
      if( (QApplication::desktop()->screenNumber(this) == QApplication::desktop()->primaryScreen()) &&
	      (defaults::toolbar_top) )
      	cx = cx + defaults::tb_height+1;
      resize_client(cx, cy, cw, ch);
    }
    else
    {
      cw = defaults::tmx2-defaults::tmx1;
      ch = defaults::tmy2-defaults::tmy1;
      getsize(&cw, &ch);
      
      resize_client(defaults::tmx1, defaults::tmy1, cw, ch);
    }
    XMoveWindow(QX11Info::display(), clientid, borderw/2, uborderh);
    maxstate = 1;
    enable_disable_menu();
  }
  else
  {
    maximizeFrame(false);
    resize_client(icx, icy, icw, ich);
    maxstate = 0;
    enable_disable_menu();
  }

  raise();
  //repaintBG();
  qapp::focus_window(this);
  //updateScreenShot();
}

void xwindow::s_maximize(void)
{
  int cw,ch;
  
  if(qapp::smode)
  {
    focus_mouse();
    trayUpdateScreenShot();
    //    updateScreenShot();
    return;
  }

  if(tstate)
  {
    qapp::tile_maximize(this);
    trayUpdateScreenShot();
    //    updateScreenShot();
    return;
  }
	
  if(maxstate != 2)  // maximize
  {
    if(maxstate == 0)
    {
      icx = x();
      icy = y();
      icw = width();
      ich = height();
    }

    if(defaults::smx1 == -1 || ((pflags & qapp::NoTile) && 
				qapp::is_tileddesk()))
    {
      cw = dt->width();
      ch = dt->height();
      getsize(&cw, &ch);
      
      resize_client(0, 0, cw, ch);
    }
    else
    {
      cw = defaults::smx2-defaults::smx1;
      ch = defaults::smy2-defaults::smy1;
      getsize(&cw, &ch);
      
      resize_client(defaults::smx1, defaults::smy1, cw, ch);
    }

    if(maxstate == 1)
      maximizeFrame(false);

    maxstate = 2;
  }
  else
  {
    resize_client(icx, icy, icw, ich);

    if(maxstate == 1)
      maximizeFrame(false);

    maxstate = 0;
  }
  enable_disable_menu();
  raise();
  qapp::focus_window(this);
  //  updateScreenShot();
  //  setactive();
  //  repaintBG();
}

void xwindow::press_move(QMouseEvent *event)
{
  if(mrb != NULL)
    return;
  
  mousepos = event->pos()+midmove->pos();  // offset
  midmove->grabMouse(QCursor(Qt::SizeAllCursor));
  mrb = new rubber(0);
  move_move(event);   // draw frame
}

void xwindow::release_move(QMouseEvent *event)
{
  QRect oldRect = rect();

  if(mrb == NULL)
    return;
  
  delete mrb;
  mrb = NULL;
  midmove->releaseMouse();
  move(event->globalPos()-mousepos);

  if(maxstate == 1)
    maximizeFrame(false);

  maxstate = 0;
  enable_disable_menu();
  qapp::focus_window(this);
  qapp::send_configurenotify(this);
  
  if(tstate && ! qapp::is_curdesk(this))
    tstate = FALSE;


  repaintBG();
  /*
  if( !screenshotTimer->isActive() )
    screenshotTimer->start( 150 );
  */
  trayUpdateScreenShot();

  if(!shaped || decorated)
   qapp::setUpdateRect( oldRect, this); 

}

void xwindow::move_move(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
  
  QPoint p = event->globalPos()-mousepos;
  mrb->draw(p.x(), p.y(), width(), height());
}

void xwindow::press_leftresize(QMouseEvent *event)
{
  if(mrb != NULL)
    return;
  
  mousepos = event->globalPos();
  lbdr->leftframe->grabMouse(QCursor(Qt::SizeAllCursor));
  mrb = new rubber(base_w, base_h, inc_w, inc_h, 0);
  move_leftresize(event);   // draw frame
}

void xwindow::release_leftresize(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
		
  delete mrb;
  mrb = NULL;
  lbdr->leftframe->releaseMouse();
  QPoint dpos = event->globalPos()-mousepos;
  int resw = width()-dpos.x();
  int resh = height()+dpos.y();
  
  getsize(&resw, &resh);
  int resx = x()-resw+width();
  
  if(resx > x()+width())
    resx = x()+width();
  
  resize_client(resx, y(), resw, resh);

  if(maxstate == 1)
    maximizeFrame(false);

  maxstate = 0;
  enable_disable_menu();
  raise();
  qapp::focus_window(this);
  
  if(tstate && ! qapp::is_curdesk(this))
    tstate = FALSE;

  //updateScreenShot();
  //repaintBG(true,true);
}

void xwindow::move_leftresize(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
  
  QPoint dpos = event->globalPos()-mousepos;
  int resw = width()-dpos.x();
  int resh = height()+dpos.y();
  
  getsize(&resw, &resh);
  int resx = x()-resw+width();
  
  if(resx+min_w > x()+width())
    resx = x()+width()-min_w;
  
  mrb->draw(resx, y(), resw, resh);
}

void xwindow::press_rightresize(QMouseEvent *event)
{
  if(mrb != NULL)
    return;
  
  mousepos = event->globalPos();
  lbdr->rightframe->grabMouse(QCursor(Qt::SizeAllCursor));
  mrb = new rubber(base_w, base_h, inc_w, inc_h, 0);
  move_rightresize(event);   // draw frame
}

void xwindow::release_rightresize(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
  
  delete mrb;
  mrb = NULL;	
  lbdr->rightframe->releaseMouse();
  QPoint dpos = event->globalPos()-mousepos;
  int resw = width()+dpos.x();
  int resh = height()+dpos.y();
  
  getsize(&resw, &resh);
  resize_client(x(), y(), resw, resh);

  if(maxstate == 1)
    maximizeFrame(false);

  maxstate = 0;
  enable_disable_menu();
  raise();
  qapp::focus_window(this);
  //   setactive();
 
  if(tstate && ! qapp::is_curdesk(this))
    tstate = FALSE;

  //updateScreenShot();
  //repaintBG(true,true);
}

void xwindow::move_rightresize(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
		
  QPoint dpos = event->globalPos()-mousepos;
  int resw = width()+dpos.x();
  int resh = height()+dpos.y();

  getsize(&resw, &resh);
  mrb->draw(x(), y(), resw, resh);
}

void xwindow::press_midresize(QMouseEvent *event)
{
  if(mrb != NULL)
    return;
		
  mousepos = event->globalPos();
  lbdr->midframe->grabMouse(QCursor(Qt::SizeAllCursor));
  mrb = new rubber(base_w, base_h, inc_w, inc_h, 0);
  move_midresize(event);   // draw frame
}

void xwindow::release_midresize(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
		
  delete mrb;
  mrb = NULL;
  lbdr->midframe->releaseMouse();
  QPoint dpos = event->globalPos()-mousepos;
  int resh = height()+dpos.y();
  int resw = width();
		
  getsize(&resw, &resh);	
  resize_client(x(), y(), resw, resh);

  if(maxstate == 1)
    maximizeFrame(false);

  maxstate = 0;
  enable_disable_menu();
  raise();
  qapp::focus_window(this);
  //  setactive();
	
  if(tstate && ! qapp::is_curdesk(this))
    tstate = FALSE;

  //updateScreenShot();
  //repaintBG(true,true);
}

void xwindow::move_midresize(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
		
  QPoint dpos = event->globalPos()-mousepos;
  int resh = height()+dpos.y();
  int resw = width();

  getsize(&resw, &resh);
  mrb->draw(x(), y(), resw, resh);
}


// start resize left
void xwindow::press_leftborder(QMouseEvent *event)
{
  if(mrb != NULL)
    return;
		
  mousepos = event->globalPos();
  slbdr->midframe->grabMouse(QCursor(Qt::SizeAllCursor));
  mrb = new rubber(base_w, base_h, inc_w, inc_h, 0);
  move_leftborder(event);   // draw frame
}

// set new window size on mouse but
void xwindow::release_leftborder(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
	
  delete mrb;
  mrb = NULL;
  slbdr->midframe->releaseMouse();
  QPoint dpos = event->globalPos()-mousepos;
  int resh = height();
  int resw = width()-dpos.x();
		
  getsize(&resw, &resh);	
  resize_client(x()+dpos.x(), y(), resw, resh);

  if(maxstate == 1)
    maximizeFrame(false);

  maxstate = 0;
  enable_disable_menu();
  raise();
  qapp::focus_window(this);
	
  if(tstate && ! qapp::is_curdesk(this))
    tstate = FALSE;
}

// mouse move for left resize
void xwindow::move_leftborder(QMouseEvent *event)
{
  if(mrb == NULL)
  {
    logmsg << "LOST MRB!!!!!!!" << endl;
    return;
  }
		
  QPoint dpos = event->globalPos()-mousepos;
  int resh = height();
  int resw = width()-dpos.x();

  //getsize(&resw, &resh);
  mrb->draw(x()+dpos.x(), y(), resw, resh);

}

// start resize right
void xwindow::press_rightborder(QMouseEvent *event)
{
  if(mrb != NULL)
    return;
		
  mousepos = event->globalPos();
  srbdr->midframe->grabMouse(QCursor(Qt::SizeAllCursor));
  mrb = new rubber(base_w, base_h, inc_w, inc_h, 0);
  move_rightborder(event);   // draw frame

}

// set new window size on mouse but
void xwindow::release_rightborder(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
		
  delete mrb;
  mrb = NULL;
  srbdr->midframe->releaseMouse();
  QPoint dpos = event->globalPos()-mousepos;
  int resh = height();
  int resw = width()+dpos.x();
		
  getsize(&resw, &resh);	
  resize_client(x(), y(), resw, resh);

  if(maxstate == 1)
    maximizeFrame(false);

  maxstate = 0;
  enable_disable_menu();
  raise();
  qapp::focus_window(this);
  //  setactive();
	
  if(tstate && ! qapp::is_curdesk(this))
    tstate = FALSE;
}

// mouse move for right resize
void xwindow::move_rightborder(QMouseEvent *event)
{
  if(mrb == NULL)
  {
    logmsg << "LOST MRB!!!!!!!" << endl;
    return;
  }
		
  QPoint dpos = event->globalPos()-mousepos;
  int resh = height();
  int resw = width()+dpos.x();

  getsize(&resw, &resh);
  mrb->draw(x(), y(), resw, resh);
}


// start resize top
void xwindow::press_topborder(QMouseEvent *event)
{
  if(mrb != NULL)
    return;
		
  mousepos = event->globalPos();
  ubdr->topframe->grabMouse(QCursor(Qt::SizeAllCursor));
  mrb = new rubber(base_w, base_h, inc_w, inc_h, 0);
  move_topborder(event);   // draw frame
}


// set new window size on mouse but
void xwindow::release_topborder(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
		
  delete mrb;
  mrb = NULL;
  ubdr->topframe->releaseMouse();
  QPoint dpos = event->globalPos()-mousepos;
  int resh = height()-dpos.y();
  int resw = width();
		
  getsize(&resw, &resh);	
  resize_client(x(), y()+dpos.y(), resw, resh);

  if(maxstate == 1)
    maximizeFrame(false);

  maxstate = 0;
  enable_disable_menu();
  raise();
  qapp::focus_window(this);
	
  if(tstate && ! qapp::is_curdesk(this))
    tstate = FALSE;

}


// mouse move for top resize
void xwindow::move_topborder(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
		
  QPoint dpos = event->globalPos()-mousepos;
  int resh = height()-dpos.y();
  int resw = width();

  //  getsize(&resw, &resh);
  mrb->draw(x(), y()+dpos.y(), resw, resh);
}



// start resize topleft
void xwindow::press_topleft(QMouseEvent *event)
{
  if(mrb != NULL)
    return;
  
  mousepos = event->globalPos();
  ubdr->upperleftframe->grabMouse(QCursor(Qt::SizeAllCursor));
  mrb = new rubber(base_w, base_h, inc_w, inc_h, 0);
  move_topleft(event);   // draw frame
}

// set new window size on mouse but
void xwindow::release_topleft(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
		
  delete mrb;
  mrb = NULL;
  ubdr->upperleftframe->releaseMouse();
  QPoint dpos = event->globalPos()-mousepos;
  int resw = width()-dpos.x();
  int resh = height()-dpos.y();
  
  getsize(&resw, &resh);
  int resx = x()-resw+width();
  
  if(resx > x()+width())
    resx = x()+width();
  
  resize_client(resx, y()+dpos.y(), resw, resh);

  if(maxstate == 1)
    maximizeFrame(false);

  maxstate = 0;
  enable_disable_menu();
  raise();
  qapp::focus_window(this);
  
  if(tstate && ! qapp::is_curdesk(this))
    tstate = FALSE;

}

// mouse move for topleft resize
void xwindow::move_topleft(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
  
  QPoint dpos = event->globalPos()-mousepos;
  int resw = width()-dpos.x();
  int resh = height()-dpos.y();
  
  int resx = x()-resw+width();
  
  if(resx+min_w > x()+width())
    resx = x()+width()-min_w;
  
  mrb->draw(resx, y()+dpos.y(), resw, resh);
}


// start resize topright
void xwindow::press_topright(QMouseEvent *event)
{
  if(mrb != NULL)
    return;
  
  mousepos = event->globalPos();
  ubdr->upperrightframe->grabMouse(QCursor(Qt::SizeAllCursor));
  mrb = new rubber(base_w, base_h, inc_w, inc_h, 0);
  move_topright(event);   // draw frame
}


// set new window size on mouse but
void xwindow::release_topright(QMouseEvent *event)
{
  if(mrb == NULL)
    return;
		
  delete mrb;
  mrb = NULL;
  ubdr->upperrightframe->releaseMouse();
  QPoint dpos = event->globalPos()-mousepos;
  int resh = height()-dpos.y();
  int resw = width()+dpos.x();
		
  getsize(&resw, &resh);	
  resize_client(x(), y()+dpos.y(), resw, resh);

  if(maxstate == 1)
    maximizeFrame(false);

  maxstate = 0;
  enable_disable_menu();
  raise();
  qapp::focus_window(this);
	
  if(tstate && ! qapp::is_curdesk(this))
    tstate = FALSE;
}


// mouse move for topright resize
void xwindow::move_topright(QMouseEvent *event)
{
  if(mrb == NULL)
  {
    logmsg << "LOST MRB!!!!!!!" << endl;
    return;
  }
		
  QPoint dpos = event->globalPos()-mousepos;
  int resh = height()-dpos.y();
  int resw = width()+dpos.x();

  mrb->draw(x(), y()+dpos.y(), resw, resh);
}





void xwindow::show_info(void)
{
  qapp::winf->show_info(this, wmname, clientfqdn, command, res_name, res_class,
			inc_w, inc_h, base_w, base_h);
}

void xwindow::unscreen(void)
{
  if(sstate)  // screen mode
  {
    resize_client(scx, scy, scw, sch);
    sstate = FALSE;
  }
}

bool xwindow::is_tileable(void)
{
  if((pflags & (qapp::Sticky|qapp::NoTile)) || transfor != None)
    return FALSE;
  
  return TRUE;	
}

void xwindow::toggle_tiled(void)
{
  qapp::toggle_tiled();
}

void xwindow::tile_maximize(void)
{
  qapp::tile_maximize(this);
  XWarpPointer(QX11Info::display(), None, winId(), 0, 0, 0, 0, width()/2, 
	       uborderh/2);
}

void xwindow::minimize_frame(bool mf)
{
  if(pflags & qapp::SmallFrame)
    return;

  int ch = height()-borderh;
  int cw = width()-borderw;
		
  if(mf)
  {
    if(uborderh == borderSize)
      return;
    
    ubdr->set_small();
    uborderh = borderSize;
    borderh = 2*uborderh;
    if(defaults::sideBorders)
      borderw = 2*borderSize;
    else
      borderw = 0;

    if( shaped || !decorated )
    {
      borderSize = 0;
      uborderh = 0;
      borderh = 0;
      borderw = 0;    
    }
  }
  else
  {
    if(uborderh == defaults::titlebarHeight+borderSize)
      return;

    if(ubdr != NULL)
      ubdr->set_normal();

    uborderh = defaults::titlebarHeight+borderSize;
    borderh = uborderh + borderSize;
    if(defaults::sideBorders)
      borderw = 2*borderSize;
    else
      borderw = 0;

    if( shaped || !decorated )
    {
      borderSize = 0;
      uborderh = 0;
      borderh = 0;
      borderw = 0;    
    }
    set_title();
  }
	
  if(shaped || (pflags & qapp::NoResize))
  {
    borderh -= borderSize;
    borderw = 0;
  }
  
  if( shaped || !decorated )
  {
    borderSize = 0;
    uborderh = 0;
    borderh = 0;
    borderw = 0;    
  }
  get_wmnormalhints();

  resize(cw+borderw, ch+borderh);

  XMoveWindow(QX11Info::display(), clientid, borderw/2, uborderh);

  trayUpdateScreenShot();
  //  updateScreenShot();
  //repaintBG(true,true);
}

int xwindow::set_tile(int cx, int cy, int cw, int ch)
{
  if(tstate == FALSE)
  {
    tcx = x();
    tcy = y();
    tcw = width();
    tch = height();

    tstate = TRUE;
  }

  if(maxstate == 1)
    maximizeFrame(false);

  maxstate = 0;
  
  int cw2 = cw;
  int ch2 = ch;
  
  if(! trsize)
  {
    getsize(&cw2, &ch2);
    
    if(cw2 > cw)
      cw2 = cw;

    if(ch2 > ch)
      ch2 = ch;
    
    resize_client(cx, cy, cw2, ch2);
  }	
  enable_disable_menu();
  raise();
  qapp::focus_window(this);
  
  return(ch - ch2);
}

void xwindow::unset_tile(void)
{
  if(! tstate)
    return;
  
  resize_client(tcx, tcy, tcw, tch);


  if(maxstate == 1)
    maximizeFrame(false);

  maxstate = 0;
  enable_disable_menu();

  minimize_frame(FALSE);
  
  tstate = FALSE;
}

void xwindow::setinactive(void)
{
  tb_pb->upDown(this, false);

  if(actpal || urgpal)
  {
    //setPalette(*qapp::ipal);  // set inactive colors
    curColor = defaults::inactive_bg;
    stopautofocus();
    actpal = FALSE;
    //    updateScreenShot();
    //repaintBG();
    trayRepaintBG();
  }

  if(ubdr != NULL)
    ubdr->setActivePal(false);

  if(urgpal)
  {
    tb_pb->change_palette(QApplication::palette(), this);
    urgpal = FALSE;
    //updateScreenShot();
    trayUpdateScreenShot();
  }	
}

void xwindow::setactive(void)
{
  tb_pb->upDown(this, true);

  if(urgpal || ! actpal)
  {
    //setPalette(QApplication::palette());  // set standard colors
    curColor = defaults::active_bg;
    actpal = TRUE;
    trayRepaintBG();
    //repaintBG();
  }

  if(ubdr != NULL)
    ubdr->setActivePal(true);

  if(urgpal)
  {
    tb_pb->change_palette(QApplication::palette(), this);
    urgpal = FALSE;
    trayUpdateScreenShot();
    //updateScreenShot();
  }	
  clients.move(clients.indexOf(this),0);
  XSetInputFocus(QX11Info::display(), client_id(),
  		 RevertToPointerRoot, CurrentTime);
  //setchildfocus(CurrentTime);
  //setcmapfocus();
}

void xwindow::seturgent(void)
{
  if(! urgpal)
  {
    //setPalette(*qapp::upal);
    curColor = defaults::urgent_bg;

    tb_pb->change_palette(*qapp::upal, this);
    urgpal = TRUE;
    repaintBG();
  }
}

void xwindow::raise()
{
  if(mrb != NULL || qapp::winf->get_client() != NULL)
    return;
		
#ifdef DEBUGMSG
  logmsg << "raise (WId:" << winId() << ")\n";
#endif

  trsize = FALSE;
  XRaiseWindow(QX11Info::display(), winId());
  //setactive();
  //  repaint();
}

void xwindow::map(void)
{

  withdrawnstate = whidden = FALSE;	

  if(!toolAdded)
  {
    tb_pb->add(this);
    toolAdded = true;
  }

  if(map_iconic)  // InitialState WMHint
  {
    set_clientstate(IconicState);
    
    if(urgent || urgpal)
    {
      urgpal = FALSE;
      seturgent();
    }	
  }	
  else
  {
    if(! isVisible())
      ;//tb_pb->set_on(this, true);
    
    map_normal();
  }	
}

void xwindow::map_normal(void)
{
  if(! isVisible())
  {
#ifdef DEBUGMSG
    logmsg << "map client\n";
#endif	
    unmapped = FALSE;
    
    if(is_tileable() && qapp::is_tileddesk()) 
    {
      if(clients.indexOf(this) == -1)
	return;
      
      qapp::tile_order(trsize?this:qapp::tmaxclient);
    }	
    else  // tiled window mapped on untiled desk
    {
      unset_tile();
    }

    show();
    XMapWindow(QX11Info::display(), clientid);
    set_clientstate(NormalState);
    
    XSync(QX11Info::display(), FALSE);
  }
  raise();
}

void xwindow::unmap(void)
{
  stopautofocus();
  
  if(! isVisible())
    return;

  unmapped = TRUE;	
	
  hide();
  XUnmapWindow(QX11Info::display(), clientid);
  
  if(tstate && qapp::is_curdesk(this))
  {
    if(qapp::tmaxclient == this)
      qapp::tmaxclient = NULL;
    
    qapp::tile_order(qapp::tmaxclient);
  }
}

void xwindow::iconify(void)  // transition to iconic
{
  if(qapp::tmaxclient == this && qapp::is_tileddesk())
    trsize = TRUE;
  
  unmap();

  withdrawnstate = FALSE;
  set_clientstate(IconicState);
  
  tb_pb->add(this);  // add to procbar
}

void xwindow::whide(void)  
{
  unmap();
  withdrawnstate = FALSE;
  set_clientstate(IconicState);

  tb_pb->remove(this);
  whidden = TRUE;
}

void xwindow::withdraw(void)
{
  unmap();
  withdrawnstate = TRUE;
  set_clientstate(WithdrawnState);
  tb_pb->remove(this);
  
#ifdef DEBUGMSG
  logmsg << "changed to withdrawn (WId:" << winId() << ")\n";
#endif
}

void xwindow::focus_mouse_wlist(void)
{
  focus_mouse(TRUE);
}

// map and set mouse (generates enter event -> focus)
void xwindow::focus_mouse(bool wlist)
{
  int pw,ph;
  
  if(qapp::smode)  // screen mode
  {
    if(! isVisible())
      return;
			
    if(sstate == FALSE)
    {
      scx = x();
      scy = y();
      scw = width();
      sch = height();
      

      if(defaults::sideBorders)
	pw = dt->width() + borderSize + borderSize;
      else
	pw = dt->width();
      ph = dt->height()+uborderh+borderSize;
      //      setGeometry(0, -uborderh, pw, ph);
      setGeometry(-(borderh/2), -uborderh, pw, ph);
      
      if(inc_w > 1)
      {
	int i = (pw-base_w)/inc_w;
	pw = base_w+i*inc_w;
      }
      
      if(inc_h > 1)	
      {
	int j = (ph-base_h)/inc_h;
	ph = base_h+j*inc_h;
      }	
      
      XResizeWindow(QX11Info::display(), clientid, pw-borderw, ph-borderh);
      sstate = TRUE;
    }
    raise();
    return;
  }
  map();	
  qapp::focus_window(this);
	
  int mid = x()+(width()/2);
  
  if(mid > dt->width())
  {
    tb_pg->change_desk(qapp::adesk+(x()/(dt->width()-1)));
  }	
  else if(mid < 0)
  {
    tb_pg->change_desk(qapp::adesk+(x()/(dt->width()+1))-1);
  }
  else if(defaults::maxontab && ! wlist && tstate)
  {
    // access in tiled state will swap windows after timeout
    
    qapp::stopautofocus();
    tfocustimer->start(defaults::maxontab);
  }	
  XWarpPointer(QX11Info::display(), None, winId(), 0, 0, 0, 0, width()/2,
	       uborderh/2);
}

// set to active and focus to child
void xwindow::setchildfocus(long timestamp) 
{
#ifdef DEBUGMSG
  logmsg << "change active client to (WId:" << winId() << ")\n";
#endif

  setactive();

  if(inputfield)  // InputHint
    XSetInputFocus(QX11Info::display(), clientid, RevertToPointerRoot, 
		   CurrentTime);
		
  if(prot_takefocus)  // WM_TAKE_FOCUS protocol
    send_wmprotocol(qapp::wm_take_focus, timestamp);
}

void xwindow::stopautofocus(void)
{
  if(defaults::autofocustime)
    focustimer->stop();

  if(tstate)
    tfocustimer->stop();
}

void xwindow::startautofocus(void)  // start autofocus timer
{
  if(! defaults::autofocustime || mrb != NULL)
    return;
		
  // do not raise if another window appears within this window

  Window w1,w2,*wins;
  uint nwins,i;
  XWindowAttributes attr;
	
  if(XQueryTree(QX11Info::display(), QX11Info::appRootWindow(), &w1, &w2, 
		&wins, &nwins) && nwins)
  {
    for(i=0; i < nwins; i++)  // find current window
      if(wins[i] == winId())
	break;
				
    int cx2 = x()+width(); int cy2 = y()+height();
		
    while(++i < nwins)
    {
      XGetWindowAttributes(QX11Info::display(), wins[i], &attr);

      if(attr.map_state !=  IsViewable)
	continue;

      int nx2 = attr.x+attr.width; int ny2 = attr.y+attr.height;
			
      if(attr.x >= x() && nx2 <= cx2 && attr.y >= y() && ny2 <= cy2)
      {
	XFree(wins);
	return;
      }	
    }	
    XFree(wins);
  }	
  focustimer->start(defaults::autofocustime);
}

void xwindow::getwmprotocols(void)
{
  Atom *protocols;
  int nprot,i;
	
  prot_delete = FALSE;
  prot_takefocus = FALSE;

  if(XGetWMProtocols(QX11Info::display(), clientid, &protocols, &nprot))
  {
    for(i=0; i < nprot; i++)
    {
      if(protocols[i] == qapp::wm_delete)
      {
	prot_delete = TRUE;
      }	
      else if(protocols[i] == qapp::wm_take_focus)
      {
	prot_takefocus = TRUE;
      }
      else if(protocols[i] == qapp::net_wm_context_help){
	hasHelpBtn = true;
	//cout << "help\n\n";
      }
    }
    XFree(protocols);
  }
}


// send protocol message to child window
void xwindow::send_wmprotocol(long data0, long data1)
{
  XEvent event;
	
  memset(&event, 0, sizeof(event));
  event.xclient.type = ClientMessage;
  event.xclient.window = clientid;
  event.xclient.message_type = qapp::wm_protocols;
  event.xclient.format = 32;
  event.xclient.data.l[0] = data0;
  event.xclient.data.l[1] = data1;
	
  XSendEvent(QX11Info::display(), clientid, False, 0L, &event);
}

int xwindow::get_clientstate(void)
{
  Atom ret_type;
  int format;
  unsigned long n,extra;
  ulong *data;
  int ret_state;

  if(XGetWindowProperty(QX11Info::display(), clientid, qapp::wm_state, 0L, 1L,
			FALSE, qapp::wm_state, &ret_type, &format, &n, &extra,
			(uchar **)&data) != Success || n == 0)
  {
    logmsg << "WM: cannot get wm_state for " << clientid << '\n';
    return(None);
  }	
		
  ret_state = (int)*data;
  XFree(data);
	
  return(ret_state);
}

void xwindow::set_clientstate(int state)
{
  ulong data[2];
  data[0] = (ulong)state;
  data[1] = (ulong)None;

  XChangeProperty(QX11Info::display(), clientid, qapp::wm_state, 
		  qapp::wm_state, 32, PropModeReplace, (uchar *)data, 2);
}

void xwindow::wdestroy(void)  // destroy client
{
  if(prot_delete)  // soft way
  {
    send_wmprotocol(qapp::wm_delete, CurrentTime);
#ifdef DEBUGMSG
    logmsg << "soft kill\n";
#endif
  }
  else 
  { 
    XKillClient(QX11Info::display(), clientid);
    XSync(QX11Info::display(), FALSE);
#ifdef DEBUGMSG
    logmsg << "hard kill\n";
#endif		
  }	
}

void xwindow::get_colormaps(void)
{
  Window *w;
  int nm=0;

  XWindowAttributes attr;
  XGetWindowAttributes(QX11Info::display(), clientid, &attr);
  cmap = attr.colormap;

  if(! XGetWMColormapWindows(QX11Info::display(), clientid, &w, &nm))
    return;

  if(nm > 1000)
  {
    logmsg << "More than 1000 colormaps for " << clientname << 
      " - property rejected\n";
    return;
  }	
	
  if(ncmaps) 
    delete [] cmapwins;

  if(nm == 0)
  {
    cmapwins = NULL;
    ncmaps = 0;
		
    return;
  }

#ifdef DEBUGMSG
  logmsg << "client has WM_COLORMAP_WINDOWS property\n";
#endif	
		
  cmapwins = new Window[nm];
  Q_CHECK_PTR(cmapwins);
  ncmaps = nm;
	
  for(int i=0; i < nm; i++) 
    cmapwins[i] = w[i];
		
  XFree(w);
}

void xwindow::setcmapfocus(void)
{
  XWindowAttributes attr;
  bool installed = FALSE;

  for(int i = ncmaps-1; i >= 0; i--)
  {
    Window w = cmapwins[i];
		
    if(w == clientid)
      installed = TRUE;
			
    XGetWindowAttributes(QX11Info::display(), w, &attr);
    qapp::install_colormap(attr.colormap);
  }	
  if(! installed)
    qapp::install_colormap(cmap);
}

bool xwindow::query_shape(void)
{
  int ns,order;

  XFree(XShapeGetRectangles(QX11Info::display(), clientid, ShapeBounding, &ns, 
			    &order));
  XShapeSelectInput(QX11Info::display(), clientid, ShapeNotifyMask);
	
  if(ns > 1)
    return TRUE;

  return FALSE;
}

void xwindow::reshape(void)
{
#ifdef DEBUGMSG
  logmsg << "reshaping client\n";
#endif

  shaped = TRUE;
  /*XShapeCombineShape(QX11Info::display(), winId(), ShapeBounding, 0, uborderh,
		     clientid, ShapeBounding, ShapeSet);
  */
  XShapeCombineShape(QX11Info::display(), winId(), ShapeBounding, borderw/2,
		       uborderh, clientid, ShapeBounding, ShapeSet);
  
  XRectangle tr;
	
  tr.x = tr.y = 0;
  tr.width = width();
  if(defaults::sideBorders)
    tr.width = borderSize;
  tr.height = uborderh;
  XShapeCombineRectangles(QX11Info::display(), winId(), ShapeBounding, 0, 0, 
			  &tr, 1, ShapeUnion, Unsorted);

  if(! (pflags & qapp::NoResize))
  {
    tr.y = height()-borderSize;
    if(defaults::sideBorders)
    {
      tr.x = width() - borderSize;
      tr.width = borderSize;
    }
     tr.height = borderSize;
    XShapeCombineRectangles(QX11Info::display(), winId(), ShapeBounding, 0, 0, 
			    &tr, 1, ShapeUnion, Unsorted);
  }
}

void xwindow::get_classhint(void)
{
  XClassHint ch;
  
  if(XGetClassHint(QX11Info::display(), clientid, &ch))
  {
    res_name = ch.res_name;
    res_class = ch.res_class;
    
    XFree(ch.res_name);
    XFree(ch.res_class);
		
#ifdef DEBUGMSG
    logmsg << "res_name set to " << res_name << '\n';
#endif

  }	
}

int xwindow::get_clientflags(void)
{
  QString cclname(res_name);   // check for name,class format
  cclname += ',';
  cclname += res_class;
  int clf = qapp::cprops[cclname];
  
  if(clf)
    return(clf);
  
  if((clf = qapp::cprops[clientname]))
    return(clf|qapp::ClassOnly);
  
  return(0);	
}	

void xwindow::set_pflags(int tflags)
{
  if( shaped || !decorated )
    return;

  int flags;
	
  if(tflags == -1)
    flags = get_clientflags();
  else
    flags = tflags;
  
  if(flags == pflags)
    return;

  int oldflags = pflags;
  pflags = flags;
  
  if(pflags & (qapp::NoTile|qapp::Sticky))
    unset_tile();
  
  int mask = qapp::SmallFrame|qapp::NoResize;
  
  if((flags & mask) != (oldflags & mask))  // rebuild window frame
  {
	
#ifdef DEBUGMSG
    logmsg << "rebuilding window frame (WId:" << winId() << ")\n";
#endif	

    cout << "DEL BORDERS\n";
    delete mrb;
    delete midmove;
    delete ubdr;
    delete lbdr;
    delete slbdr;
    delete srbdr;

    cout << "DEL LAYOUTS\n";
    if(hlayout != NULL)
      delete hlayout;

    delete layout;
    cout << "OK\n";

    int ch = height()-borderh;
    int cw = width()-borderw;
    
    if(pflags & qapp::SmallFrame)
    {
      uborderh = borderSize;
      borderh = 2*uborderh;

      if(defaults::sideBorders)
	borderw = 2*borderSize;
      else
	borderw = 0;
    }
    else
    {
      uborderh = defaults::titlebarHeight+borderSize;
      borderh = uborderh+borderSize;
      if(defaults::sideBorders)
	borderw = 2*borderSize;
      else
	borderw = 0;
    }
	
    if(pflags & qapp::NoResize)
    {
      borderh -= borderSize;
      borderw = 0;
    }

    get_wmnormalhints();
    resize(cw+borderw, ch+borderh);
    XMoveWindow(QX11Info::display(), clientid, borderw/2, uborderh);
    
    cout << "CREATE BORDERS\n";
    create_wborder();
    cout << "BORDERS CREATED\n\n";
    wmname = "";
    get_wmname();
    
    if(shaped)
      reshape();
    
    if(ubdr != NULL)
      ubdr->show();
    else
      midmove->show();
    
    if(lbdr != NULL)
      lbdr->show();
    
    if(slbdr != NULL)
      slbdr->show();

    if(srbdr != NULL)
      srbdr->show();

  }

  if(! (oldflags & qapp::Sticky) && (flags & qapp::Sticky))  // move to current desk
  {
    int dx = x()/dt->width();
    
    if(x() < 0)
      dx--;
    
    move(x()-(dx*dt->width()), y());
  }
    cout << "FINISHED SETTING PFLAGS \n\n";
}

void xwindow::get_wmnormalhints(void)
{
  XSizeHints *xsizehints;
  if((xsizehints = XAllocSizeHints()) == NULL)
    sleep(1);
  
#ifdef DEBUGMSG
  logmsg << "reading WMNormalHints (WId:" << winId() << ")\n";
#endif	
		
  long hints;
  if(XGetWMNormalHints(QX11Info::display(), clientid, xsizehints, &hints)
     == 0)
    xsizehints->flags = 0;
  
  wmnflags = xsizehints->flags;
  wingrav = xsizehints->win_gravity;
  
  bool pminsize = FALSE;
  
  // set max,min and base size, results include window borders
  
  if(wmnflags & PMinSize) 
  {
    min_w = xsizehints->min_width+borderw;
    min_h = xsizehints->min_height+borderh;
    pminsize = TRUE;   // to get base size if unspecified
  } 
  else 
  {
    min_w = borderw;//+4;
    min_h = borderh;
  }
  if(wmnflags & PMaxSize)
  {
    max_w = xsizehints->max_width+borderw;
    max_h = xsizehints->max_height+borderh;
    
    if(max_w > dt->width())
      max_w = dt->width();
    
    if(max_h > dt->height())
      max_h = dt->height();
  }
  else
  {
    max_w = dt->width();
    max_h = dt->height();
  }
  
  if(wmnflags & PBaseSize)
  {
    base_w = xsizehints->base_width+borderw;
    base_h = xsizehints->base_height+borderh;
    
    if(! pminsize)  // get from base if unspecified
    {
      min_w = base_w;
      min_h = base_h;
    }
  }
  else if(pminsize)
  {
    base_w = xsizehints->min_width;
    base_h = xsizehints->min_height;
  }
	
  if(wmnflags & PResizeInc)
  {
    inc_w = xsizehints->width_inc;
    inc_h = xsizehints->height_inc;
  }
  else
    inc_w = inc_h = 1;

  if( ( (wmnflags & USPosition) || (wmnflags & PPosition) ) 
      && (!defaults::start_restart) )
  {
    pre_pos_x = xsizehints->x;
    pre_pos_y = xsizehints->y;
    has_own_pos = true;
  }

  
  XFree(xsizehints);
}		

void xwindow::get_wmhints(void)  // get WMHints
{
  XWMHints *xwmhints;
  map_iconic = FALSE;
  inputfield = TRUE;
  urgent = FALSE;
	
  if((xwmhints = XGetWMHints(QX11Info::display(), clientid)) != NULL)
  {
#ifdef DEBUGMSG
    logmsg << "reading WMHints (WId:" << winId() << ")\n";
#endif	
    
    if(xwmhints->flags & StateHint && xwmhints->initial_state == IconicState)
      map_iconic = TRUE;
    
    if(! (xwmhints->flags & InputHint))  // focus
      inputfield = FALSE;
    
    if(xwmhints->flags & IconPixmapHint)
      get_servericon(xwmhints->icon_pixmap, (xwmhints->flags & IconMaskHint)?
		     (xwmhints->icon_mask):(None));
    
    if(xwmhints->flags & (1L << 8))
    {
      urgent = TRUE;
      seturgent();  // set urgent colors on window border and icon
    }
    else if(urgpal)
    {
      if(actpal)
	setactive();
      else
	setinactive();
    }
    XFree(xwmhints);
  }
}

void xwindow::set_title(void)
{
  if((pflags & qapp::SmallFrame) || (uborderh == borderSize))
    return;

  QString *wmn = &wmname;
  QString tnm;
  
  if(tnumber)
  {
    QTextStream tns(&tnm);
    
    tns << wmname << '<' << tnumber << '>';
    wmn = &tnm;
  }

  if(! wicon.isNull()){
    if(titleOrder.contains("Menu"))
    {
      if((ubdr != NULL) && (ubdr->menuframe != NULL))
      {
	QPixmap *iconpix = new QPixmap();
	*iconpix = wicon.scaled(defaults::windowButtonSize-3,
				defaults::windowButtonSize-3,
				Qt::IgnoreAspectRatio,
				Qt::SmoothTransformation);
	ubdr->menuframe->setPixmap(*iconpix);
	delete iconpix;
      }
    }
  }
  midmove->set_text(*wmn, transfor == None);
  //setPalette(actpal?QApplication::palette():*qapp::ipal);
  curColor = actpal?defaults::active_bg:defaults::inactive_bg;
  repaintBG();

}

void xwindow::get_wmname(void)  // get WM_NAME and ICON_NAME and set caption and border pixmap
{
  char *name;
  xwindow *client;
  QString oldwname = wmname;
  QString oldiname = icname;
  Atom type;
  int format;
  unsigned long nitems=0;
  unsigned long extra=0;
  unsigned char *data=NULL;
  
  XGetWindowProperty(QX11Info::display(), clientid, qapp::net_wm_name, 0, 500,
		     FALSE, AnyPropertyType, &type, &format, &nitems, &extra,
		     &data);
  
  if(data != NULL)
  {
    wmname = QString::fromUtf8((char *)data);
    XFree(data);
  }
  else if(XFetchName(QX11Info::display(), clientid, &name) && name != NULL)
  {
    wmname = name;
    XFree(name);
  }
  else  // use class hints
    wmname = res_name;
  
  data = NULL;
  XGetWindowProperty(QX11Info::display(), clientid, qapp::net_wm_icon_name, 0, 
		     500, FALSE, AnyPropertyType, &type, &format, &nitems, 
		     &extra, &data);
	
  if(data != NULL)
  {
    icname = QString::fromUtf8((char *)data);
    XFree(data);
  }
  else if(XGetIconName(QX11Info::display(), clientid, &name) && name != NULL)
  {
    icname = name;
    XFree(name);
  }
  else 
    icname = wmname;
		
#ifdef DEBUGMSG
  logmsg << "WM_NAME set to " << wmname << '\n';
#endif

  if(wmname != oldwname)
  {
    // look for other windows with the same title
    
    tnumber = 0;
    
    QList<xwindow*> clst = clients;
    
    for(int i=0; i < clst.size(); i++)
    {
      client = clst.at(i);
      if(client != this && ! (client->get_pflags() & qapp::SmallFrame) && 
	 wmname == client->ccaption() && client->get_tnumber() >= tnumber)
	tnumber = client->get_tnumber()+1;
    }
    set_title();
  }	
		
  if(icname != oldiname)  // change icon text on procbar
    tb_pb->change_text(&icname, this);
}

// get pixmap from server and scale it
void xwindow::get_servericon(Pixmap icon, Pixmap mask)
{
  int ix,iy;
  uint iw,ih,bwidth,depth;
  Window w;
  GC gc;

  if(! XGetGeometry(QX11Info::display(), icon, &w, &ix, &iy, &iw, &ih, 
		    &bwidth, &depth))
    return;

  QPixmap pix(iw, ih);
  pix.detach();
  gc = XCreateGC(QX11Info::display(), icon, 0, 0);
  XCopyArea(QX11Info::display(), icon, pix.handle(), gc, 0, 0, iw, ih, 0 ,0);
  XFreeGC(QX11Info::display(), gc);

  if(mask != None)
  {
    gc = XCreateGC(QX11Info::display(), mask, 0, 0);
    QBitmap bmap(iw, ih);
    bmap.detach();
    XCopyArea(QX11Info::display(), mask, bmap.handle(), gc, 0, 0, iw, ih, 0,
	      0);
    pix.setMask(bmap);
    XFreeGC(QX11Info::display(), gc);
  }
  wicon = pix;//pix.scaledToHeight(defaults::tc_height-4, Qt::SmoothTransformation);


}

void xwindow::state(bool on)
{
  //if(defaults::withxpmenu)
  defaults::smenu->close();

  if(on){
    map_normal();
    tb_pb->upDown(this, true);
    focus_mouse_wlist();
  }else{
    iconify();
    tb_pb->upDown(this, false);
  }
}

xwindow::~xwindow(void)
{
  delete [] cmapwins;
  delete mrb;
  
  if(qapp::winf->get_client() == this)
    qapp::winf->release_cancel();
  
  tb_pb->remove(this);  // remove from procbar
  qapp::cwindows.remove(clientid);
  qapp::pwindows.remove(winId());

  //  delete bg;
  delete iconmenu;
  delete focustimer;
  delete tfocustimer;

#ifdef DEBUGMSG
  logmsg << "class xwindow destructed (WId:" << winId() << ")\n";
#endif	
}
