/****************************************************************************
 **
 **				main.cpp
 **			=========================
 **
 **  begin                : 2001 based on qlwm
 **  copyright            : (C) 2001 - 2007 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **  License              : GPL
 **
 **  Our Main Class, here begins everything.
 **
 **  Special Thanks to Alexander Linden <alinden@gmx.de>
 **
 ****************************************************************************/
        

#include "defs.h"
#include "conf.h"
#include "keyboard.h"
#include "winfo.h"
#include "qapp.h"
#include "desktp.h"
#include <defaults.h>
#include <libhde.h>
#include <QTranslator>

bool wm_init=TRUE;

#define ChildMask (SubstructureRedirectMask|SubstructureNotifyMask)
#define ButtonMask (ButtonPressMask|ButtonReleaseMask)
#define MouseMask (ButtonMask|PointerMotionMask)

void make_bpixmaps(void){
    int hh;

    if ( defaults::titleStyle == "win")
	hh = defaults::iconsize-2;
    else
	hh = defaults::iconsize;

    int wh = defaults::iconsize;

    if(defaults::windowButtonPos == "Top")
      wh = defaults::windowButtonSize;

    QImage limg(defaults::get_cfile(defaults::left_icon.toAscii().data()));
    QImage ulimg(defaults::get_cfile(defaults::uleft_icon.toAscii().data()));
    QImage cimg(defaults::get_cfile(defaults::close_icon.toAscii().data()));
    QImage ucimg(defaults::get_cfile(defaults::uclose_icon.toAscii().data()));
    QImage nimg(defaults::get_cfile(defaults::min_icon.toAscii().data()));
    QImage unimg(defaults::get_cfile(defaults::umin_icon.toAscii().data()));
    QImage ximg(defaults::get_cfile(defaults::max_icon.toAscii().data()));
    QImage uximg(defaults::get_cfile(defaults::umax_icon.toAscii().data()));
    QImage himg(defaults::get_cfile(defaults::help_icon.toAscii().data()));
    QImage uhimg(defaults::get_cfile(defaults::uhelp_icon.toAscii().data()));
    QImage eimg(defaults::get_cfile(defaults::rest_icon.toAscii().data()));
    QImage ueimg(defaults::get_cfile(defaults::urest_icon.toAscii().data()));

    QImage pimg(defaults::get_cfile(defaults::deficon.toAscii().data()));

    /*
    QImage timg(defaults::get_cfile(defaults::titleimage.toAscii().data()));
    QImage trimg(defaults::get_cfile(defaults::titlerimage.toAscii().data()));
    QImage tlimg(defaults::get_cfile(defaults::titlelimage.toAscii().data()));
    QImage utimg(defaults::get_cfile(defaults::untitleimage.toAscii().data()));
    QImage utrimg(defaults::get_cfile(defaults::untitlerimage.toAscii()
				      .data()));
    QImage utlimg(defaults::get_cfile(defaults::untitlelimage.toAscii()
				      .data()));
    */

    qapp::minmaxpix = new QPixmap();
    qapp::uminmaxpix = new QPixmap();
    qapp::closepix = new QPixmap();
    qapp::uclosepix = new QPixmap();
    qapp::minbtnpix = new QPixmap();
    qapp::uminbtnpix = new QPixmap();
    qapp::maxbtnpix = new QPixmap();
    qapp::umaxbtnpix = new QPixmap();
    qapp::helpbtnpix = new QPixmap();
    qapp::uhelpbtnpix = new QPixmap();
    qapp::restorebtnpix = new QPixmap();
    qapp::urestorebtnpix = new QPixmap();
    qapp::defaultpix = new QPixmap();

    /*	
    qapp::titlepix = new QPixmap();
    qapp::titlerightpix = new QPixmap();
    qapp::titleleftpix = new QPixmap();
    qapp::untitlepix = new QPixmap();
    qapp::untitlerightpix = new QPixmap();
    qapp::untitleleftpix = new QPixmap();
    */

    qapp::titlepix = new QImage(defaults::get_cfile(defaults::titleimage));
    qapp::titlerightpix = new QImage
      (defaults::get_cfile(defaults::titlerimage));
    qapp::titleleftpix = new QImage
      (defaults::get_cfile(defaults::titlelimage));
    qapp::untitlepix = new QImage
      (defaults::get_cfile(defaults::untitleimage));
    qapp::untitlerightpix = new QImage
      (defaults::get_cfile(defaults::untitlerimage));
    qapp::untitleleftpix = new QImage
      (defaults::get_cfile(defaults::untitlelimage));


    qapp::border_tlimage = new QImage
      (defaults::get_cfile(defaults::border_tlimage));
    qapp::border_trimage = new QImage
      (defaults::get_cfile(defaults::border_trimage));
    qapp::topborderimage = new QImage
      (defaults::get_cfile(defaults::topborderimage));
    qapp::border_leftimage =  new QImage
      (defaults::get_cfile(defaults::border_leftimage));
    qapp::border_rightimage =  new QImage
      (defaults::get_cfile(defaults::border_rightimage));
    qapp::border_blimage =  new QImage
      (defaults::get_cfile(defaults::border_blimage));
    qapp::border_brimage =  new QImage
      (defaults::get_cfile(defaults::border_brimage));
    qapp::bottomborderimage =  new QImage
      (defaults::get_cfile(defaults::bottomborderimage));

    qapp::uborder_tlimage = new QImage
      (defaults::get_cfile(defaults::uborder_tlimage));
    qapp::uborder_trimage = new QImage
      (defaults::get_cfile(defaults::uborder_trimage));
    qapp::utopborderimage = new QImage
      (defaults::get_cfile(defaults::utopborderimage));
    qapp::uborder_leftimage =  new QImage
      (defaults::get_cfile(defaults::uborder_leftimage));
    qapp::uborder_rightimage =  new QImage
      (defaults::get_cfile(defaults::uborder_rightimage));
    qapp::uborder_blimage =  new QImage
      (defaults::get_cfile(defaults::uborder_blimage));
    qapp::uborder_brimage =  new QImage
      (defaults::get_cfile(defaults::uborder_brimage));
    qapp::ubottomborderimage =  new QImage
      (defaults::get_cfile(defaults::ubottomborderimage));



    if(! limg.isNull())
      *qapp::minmaxpix = 
	QPixmap::fromImage(limg.scaled(wh, hh, Qt::IgnoreAspectRatio,
				       Qt::SmoothTransformation));
    if(! ulimg.isNull())
      *qapp::uminmaxpix = 
	QPixmap::fromImage(ulimg.scaled(wh, hh, Qt::IgnoreAspectRatio, 
					Qt::SmoothTransformation));

      if(! cimg.isNull())
	*qapp::closepix = 
	  QPixmap::fromImage(cimg.scaled(defaults::closeButtonWidth, hh,
					 Qt::IgnoreAspectRatio, 
					 Qt::SmoothTransformation));
      if(! ucimg.isNull())
	*qapp::uclosepix =
	  QPixmap::fromImage(ucimg.scaled(defaults::closeButtonWidth, hh,
					  Qt::IgnoreAspectRatio, 
					  Qt::SmoothTransformation));
      //}

    if(! nimg.isNull())
	*qapp::minbtnpix = 
	  QPixmap::fromImage(nimg.scaled(wh, hh, Qt::IgnoreAspectRatio,
					 Qt::SmoothTransformation));
    if(! unimg.isNull())
      *qapp::uminbtnpix = 
	QPixmap::fromImage(unimg.scaled(wh, hh, Qt::IgnoreAspectRatio,
					  Qt::SmoothTransformation));

    if(! ximg.isNull())
      *qapp::maxbtnpix =
	QPixmap::fromImage(ximg.scaled(wh, hh, Qt::IgnoreAspectRatio,
				       Qt::SmoothTransformation));
    if(! uximg.isNull())
      *qapp::umaxbtnpix =
	QPixmap::fromImage(uximg.scaled(wh, hh, Qt::IgnoreAspectRatio,
				       Qt::SmoothTransformation));

    if(! himg.isNull())
      *qapp::helpbtnpix = 
	QPixmap::fromImage(himg.scaled(wh, hh, Qt::IgnoreAspectRatio,
				       Qt::SmoothTransformation));
    if(! uhimg.isNull())
      *qapp::uhelpbtnpix = 
	QPixmap::fromImage(uhimg.scaled(wh, hh, Qt::IgnoreAspectRatio,
				       Qt::SmoothTransformation));


    if(! eimg.isNull())
	*qapp::restorebtnpix = 
	  QPixmap::fromImage(eimg.scaled(wh, hh, Qt::IgnoreAspectRatio, 
					 Qt::SmoothTransformation));
    if(! ueimg.isNull())
      *qapp::urestorebtnpix = 
	QPixmap::fromImage(ueimg.scaled(wh, hh, Qt::IgnoreAspectRatio, 
				       Qt::SmoothTransformation));


    if(! pimg.isNull())
      *qapp::defaultpix = 
	QPixmap::fromImage(pimg.scaled(defaults::windowButtonSize-3, 
				       defaults::windowButtonSize-3, 
				       Qt::IgnoreAspectRatio,
				       Qt::SmoothTransformation));



    if(! qapp::titlepix->isNull())
      *qapp::titlepix = qapp::titlepix->scaled(qapp::titlepix->width(),
					      defaults::iconsize,
					      Qt::IgnoreAspectRatio,
					      Qt::SmoothTransformation);
    if(! qapp::titlerightpix->isNull())
	*qapp::titlerightpix = qapp::titlerightpix
	  ->scaled(qapp::titlerightpix->width(),  defaults::iconsize,
		   Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    if(! qapp::titleleftpix->isNull())
	  *qapp::titleleftpix = qapp::titleleftpix->
	    scaled(qapp::titleleftpix->width(), defaults::iconsize,
		   Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    if(! qapp::untitlepix->isNull())
	*qapp::untitlepix = qapp::untitlepix->
	  scaled(qapp::untitlepix->width(),defaults::iconsize,
		 Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    if(! qapp::untitlerightpix->isNull())
	*qapp::untitlerightpix = qapp::untitlerightpix->
	  scaled(qapp::untitlerightpix->width(), defaults::iconsize,
		 Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    if(! qapp::untitleleftpix->isNull())
	  *qapp::untitleleftpix = qapp::untitleleftpix->
	    scaled(qapp::untitleleftpix->width(), defaults::iconsize,
		   Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

}

void getrunprocs(void)  // get already running clients
{
  Window w,w1,w2,*wins;
  uint nwins,cwin;
  XWindowAttributes attr;
  
  if(XQueryTree(QX11Info::display(), QX11Info::appRootWindow(), &w1, &w2,
		&wins, &nwins) == 0 || ! nwins)
    return;
	
  bool surgent = defaults::starturgent;
  defaults::starturgent = FALSE;
  
  for(cwin=0; cwin < nwins; cwin++)
  {
    w = wins[cwin];
    
    if(w == qapp::tb->winId())
      continue;

    if(w == qapp::Desktop->winId())
      continue;

    
    XGetWindowAttributes(QX11Info::display(), w, &attr);
    
    if(attr.map_state == IsViewable && ! attr.override_redirect)
      qapp::run_client(w);
  }
  XSync(QX11Info::display(), FALSE);
  defaults::starturgent = surgent;
}

void sig_hup(int)
{
  qapp::sighup = TRUE;
}

void sig_term(int)  // terminate
{
  tb_pb->remove_all();
  
  for(int i=0; i < clients.size(); i++)
    XReparentWindow(QX11Info::display(), clients.at(i)->winId(), 
		    QX11Info::appRootWindow(), 0, 0);
		
  XSync(QX11Info::display(), FALSE);
  
  exit(0);
}

void startprg(void)  // start programs from init stack
{
  pid_t pid;
  //  QByteArray *prg;
  QString prg;
  while(! defaults::initexec.isEmpty())
  {
    prg = defaults::initexec.pop();
    logmsg << qPrintable(prg) << "\n";

    if((pid = fork()) == 0)
    {
      //execl("/bin/sh", "sh", "-c", (const char *)prg.toAscii().data(),
      // NULL);
      execl("/bin/sh", "sh", "-c", qPrintable(prg), NULL);
      perror("Exec");
      exit(1);
    }
    
    if(pid == -1)
      perror("fork");
    
    //delete prg;	
  }
}
/*
void make_bpixmaps(void)   // create scaled window button pixmaps
{
	int wh = defaults::windowbuttonsize-4;
	QImage limg(qapp::get_cfile("button_left.xpm"));
	QImage rimg(qapp::get_cfile("button_right.xpm"));

	qapp::leftwinpix = new QPixmap();
	qapp::rightwinpix = new QPixmap();
	
	if(! limg.isNull())
		*qapp::leftwinpix = QPixmap::fromImage(limg.scaled(wh, wh, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	
	if(! rimg.isNull())
		*qapp::rightwinpix = QPixmap::fromImage(rimg.scaled(wh, wh, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	
}
*/
int xerrors(Display *d, XErrorEvent *event)
{
  char	msg[100];
  char	req[100];
  char	nmb[100];
  
  if(wm_init == TRUE && event->error_code == BadAccess)
  {
    logmsg << "Another WM is already running\n";
    exit(1);
  }

#ifndef DEBUGMSG
  if(event->error_code == BadWindow || event->error_code == BadMatch)
    return 0;
#endif

  XGetErrorText(d, event->error_code, msg, sizeof(msg));
  sprintf(nmb, "%d", event->request_code);
  XGetErrorDatabaseText(d, "XRequest", nmb, nmb, req, sizeof(req));
  
  logmsg << "WM: " << req << " on resource " << event->resourceid 
	 << " failed: " << msg << '\n';
  
  return 0;
}

int main(int argc, char **argv)
{
  for(int i=1; i < argc; i++)
  {
    if(strcmp(argv[i], "--version") == 0 || strcmp(argv[i],"-v") == 0)
    {
      logmsg << "Haydar Windows Manager version: " << DVERSION;
      return(0);
    }
		
    if(strcmp(argv[i], "-restart") == 0)
      defaults::start_restart = TRUE;
    
    if(strcmp(argv[i], "-c") == 0 && argc > i+1)
      defaults::cfdir = argv[++i];
  }

  if(defaults::cfdir.isNull())  // get config dir
  {
    QString fname(getenv("HOME"));
    
    if(! fname.isNull())
      defaults::cfdir = fname + "/.config/hde2";
  }

  if(!QFileInfo( defaults::cfdir + "/temp" ).exists() ){
    execCmd( "mkdir -p " + defaults::cfdir  + "/temp" );
  }

  QString homedir(getenv("HOME"));
  if( !QFileInfo( defaults::cfdir + "/Desktop" ).exists() ){
    if(QFileInfo( homedir + "/Desktop" ).exists())
      execCmd( "ln -s " + homedir + "/Desktop " + defaults::cfdir 
	       + "/Desktop" );	
    else
      execCmd( "cp -aR " + QString(CONFDIR) + "/userfiles/Desktop " +
	       defaults::cfdir );
  }
  if(!QFileInfo( defaults::cfdir + "/appdefaults" ).exists())
    execCmd( "cp -aR " + QString(CONFDIR) + "/appdefaults " + 
	     defaults::cfdir );
  if(!QFileInfo( defaults::cfdir + "/defaults" ).exists())
    execCmd( "cp -aR " + QString(CONFDIR) + "/defaults " + defaults::cfdir );



  defaults::argc = argc;
  defaults::argv = argv;
  
  qapp a(argc, argv);
  
  defaults::read_config();

  QTranslator translator( 0 );
  QTranslator qt_translator( 0 );
  translator.load( "hde_" + defaults::lng , defaults::get_cfile("lng") );
  
  QTranslator libtranslator( 0 );
  libtranslator.load( "libhde_" + defaults::lng ,defaults::get_cfile("lng"));

  QString QTDIR = getenv( "QTDIR" );

  qt_translator.load( QString( "qt_%1" ).arg( defaults::lng ), 
		      QTDIR + "/translations" );
  
  a.installTranslator( &qt_translator );
  a.installTranslator( &translator );
  a.installTranslator( &libtranslator );
  
  a.setOverrideCursor( QCursor(Qt::WaitCursor) );

  //    qapp::dsktp = new desktp(); 
  qapp::Desktop = new desktp();
    //  qapp::Desktop->setBackground();
  qapp::tb = new Toolbar();
  qapp::manageTray();
  qapp::read_cprops();
  make_bpixmaps();
  qapp::winf = new winfo(0);

  XSetErrorHandler(xerrors);
  
  XIconSize *isize;
  if((isize = XAllocIconSize()) != NULL)
  {
    isize->min_width = isize->min_height = 2;
    isize->max_width = isize->max_height = 200;
    isize->width_inc = isize->height_inc = 1;
    
    XSetIconSizes(QX11Info::display(), QX11Info::appRootWindow(), isize, 1);
    XFree(isize);
  }	
  

  XClearWindow(QX11Info::display(), QX11Info::appRootWindow());
  
  //qapp::upal = new QPalette(defaults::urgent_bg);
  
  //qapp::ipal = new QPalette(defaults::inactive_bg);

  if(defaults::bordersTransparency < 255)
  {
    defaults::active_bg.setAlpha(defaults::bordersTransparency);
    defaults::inactive_bg.setAlpha(defaults::bordersTransparency);
  }
  
  XSelectInput(QX11Info::display(), QX11Info::appRootWindow(),
	       SubstructureRedirectMask);
  XSync(QX11Info::display(), FALSE);

  if(defaults::sttiled[0])
  {
    qapp::tdesks[0] = TRUE;
    defaults::sttiled[0] = FALSE;
  }
  tb_wl->set_pixmap();
  getrunprocs();
  defaults::start_restart = FALSE;
  
  XSelectInput(QX11Info::display(), QX11Info::appRootWindow(),
	       SubstructureNotifyMask|SubstructureRedirectMask| 
	       ButtonPressMask|
	       PropertyChangeMask|
	       KeyPressMask|
	       ColormapChangeMask|
	       EnterWindowMask);
  
  XSync(QX11Info::display(), FALSE);
  
  struct sigaction act;
  
  act.sa_handler = sig_hup;
  act.sa_flags = SA_RESTART;
  sigaction(SIGHUP, &act, NULL);
  
  act.sa_handler = sig_term;
  sigaction(SIGTERM, &act, NULL);
  
  keyboard::init();
  wm_init = FALSE;
  startprg();

  a.restoreOverrideCursor();
  
  return(a.exec());
}
