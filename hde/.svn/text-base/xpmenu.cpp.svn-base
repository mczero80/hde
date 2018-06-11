/****************************************************************************
 **
 **				xpmenu.h
 **			==========================
 **
 **  begin                : Mar 04 2007
 **  copyright            : (C) 2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  The XP Menu style in hde.
 **
 ****************************************************************************/

#include "xpmenu.h"

#include <libhde.h>

#include <QtGui>
#include <defaults.h>

#include <iostream>
using std:: cout; using std::endl;using std::cerr;
#include "xwindow.h"
#include "qapp.h"


/*******************************************************************
 *
 * Top widget, where your name and photo appears.
 *
 ******************************************************************/
topWidget::topWidget( QWidget* parent )
  : QWidget( parent )
{
}

void topWidget::paintEvent( QPaintEvent * )
{
  QPixmap px(width(), height());
  QPainter p( this );

  QImage img( get_cfile( "images/menutop.png") );

  if( QApplication::isRightToLeft() )
    img = img.mirrored(true, false);

  QPixmap pix;
  pix = QPixmap::fromImage(img.scaled(width(), height(), Qt::IgnoreAspectRatio,
				     Qt::SmoothTransformation));
  p.drawPixmap ( 0, 0, pix);//, width()-1, height()-1);
  
  setFont( QFont(font().family(), 18, QFont::Bold) );

  int i = 0;
  if( QApplication::isRightToLeft() ){
    if(! pixmap.isNull()){
     p.drawPixmap( width() - 68, 10, pixmap);
      i = 58;
    }
    
    if(!text.isEmpty()){
      p.setPen( Qt::white );

      p.drawText( 10 +1, (height()/2 ) - (QFontMetrics(font()).height()/2)
		  +1, width() - i - 20, height(), Qt::AlignRight, text );
      
      p.setPen( Qt::black );
      p.drawText( 10 -1, (height()/2 ) - (QFontMetrics(font()).height()/2)
		  -1, width() - i - 20, height(), Qt::AlignRight, text );
    
    }
    
  }else{
    if(! pixmap.isNull()){
      p.drawPixmap( 10, 10, pixmap);
      i = 58;
    }
    
    if(!text.isEmpty()){
      p.setPen( Qt::white );

      QRect r( i + 10 + 1, 
	       (height()/2 ) - (QFontMetrics(font()).height()/2) +1,
	       width() - 20, 
	       height());

      p.drawText(r, text );

      p.setPen( Qt::black );
      QRect r2(i + 10 - 1, 
	       (height()/2 ) - (QFontMetrics(font()).height()/2) -1,
	       width() - 20,
	       height());
      p.drawText(r2, text );
    }
  }
  
  p.end();
}












xpMenu::xpMenu( QWidget* parent, Qt::WFlags fl )
  : startMenu( parent, fl )

{
  initIt();
}

void xpMenu::initIt()
{
  setFixedSize( QSize(380, 486) );
  setFrameShape( QFrame::NoFrame );

  mainLayout = new QVBoxLayout( this); 
  mainLayout->setMargin( 0 );
  mainLayout->setSpacing( 0 );
  
  personalFrame = new topWidget( this );
  personalFrame->setFixedSize( QSize( 380, 65 ) );
  {
    QImage img( defaults::get_cfile( "images/hl.png") );
    QPixmap pix(48,48);
    pix = pix.fromImage(img.scaled(48,48));
    personalFrame->setPixmap( pix );
  }
  mainLayout->addWidget( personalFrame );


  QHBoxLayout *midLayout = new QHBoxLayout( 0 ); 
  midLayout->setMargin( 0 );
  midLayout->setSpacing( 0 );

  /*****************************************************************
   *
   * Programs
   *
   ****************************************************************/
  QFrame *programsFrame = new QFrame( this );
  programsFrame->setFixedSize( QSize( 190, 381 ) );
  programsFrame->setFrameShape( QFrame::NoFrame );
  programsFrame->setFrameShadow( QFrame::Plain );
  {
    QImage img = QImage( get_cfile( "images/progsmenu.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix = pix.fromImage(img.scaled(190, 381));
    QPalette p(programsFrame->palette());
    p.setBrush(QPalette::Background, pix);
    programsFrame->setPalette(p);
    programsFrame->setAutoFillBackground(true);
  }

  QVBoxLayout *programsLayout = new QVBoxLayout( programsFrame ); 
  programsLayout->setMargin( 0 );
  programsLayout->setSpacing( 6 );

  programsLayout->addSpacing(5);
  
  internetBrowser = new sMenuItem( programsFrame );
  internetBrowser->setMinimumSize( QSize( 180, 35 ) );
  internetBrowser->setCommand("firefox");
  {
    QPixmap pix = QPixmap(get_ifile("firefox.png", "mid"));
    if(pix.isNull())
      pix = get_cfile( "images/firefox.png");
    internetBrowser->setPixmap(pix);
  }

  programsLayout->addWidget( internetBrowser );
  internetBrowser->connectItem( this, SLOT(close()) );
  
  emailClient = new sMenuItem( programsFrame );
  emailClient->setMinimumSize( QSize( 180, 35 ) );
  emailClient->setCommand("thunderbird");
  {
    QPixmap pix = QPixmap(get_ifile("thunderbird.png", "mid"));
    if(pix.isNull())
      pix = get_cfile( "images/thunderbird.png");
    emailClient->setPixmap(pix);
  }
  programsLayout->addWidget( emailClient );
  emailClient->connectItem( this, SLOT(close()) );
  
  QFrame *seperator = new QFrame( programsFrame );
  seperator->setFrameShape( QFrame::HLine );
  seperator->setFrameShadow( QFrame::Sunken );
  programsLayout->addWidget( seperator );
  seperator->setFixedWidth(120);
  programsLayout->setAlignment(seperator, Qt::AlignCenter);
  
  recent1 = new sMenuItem( programsFrame );
  recent1->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent1 );
  recent1->connectItem( this, SLOT(close()) );
  
  recent2 = new sMenuItem( programsFrame );
  recent2->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent2 );
  recent2->connectItem( this, SLOT(close()) );
  
  recent3 = new sMenuItem( programsFrame );
  recent3->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent3 );
  recent3->connectItem( this, SLOT(close()) );
  
  recent4 = new sMenuItem( programsFrame );
  recent4->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent4 );
  recent4->connectItem( this, SLOT(close()) );

  recent5 = new sMenuItem( programsFrame );
  recent5->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent5 );
  recent5->connectItem( this, SLOT(close()) );

  recent6 = new sMenuItem( programsFrame );
  recent6->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent6 );
  recent6->connectItem( this, SLOT(close()) );
  
  programsLayout->addStretch(100);
  
  QFrame *seperator1 = new QFrame( programsFrame );
  seperator1->setFrameShape( QFrame::HLine );
  seperator1->setFrameShadow( QFrame::Sunken );
  
  programsLayout->addWidget( seperator1 );
  seperator1->setFixedWidth(120);
  programsLayout->setAlignment(seperator1, Qt::AlignCenter);
  
  programs = new sMenuItem( programsFrame );
  programs->setMinimumSize( QSize( 180, 20 ) );
  progsPop = new QMenu;
  programs->setPopup(progsPop);
  {
    QPixmap pix = QPixmap(get_ifile("grp.png", "mid"));
    if(pix.isNull())
      pix = get_cfile( "images/grp.png");
    programs->setPixmap(pix);
  }
  programsLayout->addWidget( programs );

  programsLayout->addSpacing( 7 );
  
  midLayout->addWidget( programsFrame );




  /*****************************************************************
   *
   * Configs
   *
   ****************************************************************/
  QFrame *configsFrame = new QFrame( this );
  configsFrame->setFixedSize( QSize( 190, 381 ) );
  configsFrame->setFrameShape( QFrame::NoFrame );
  configsFrame->setFrameShadow( QFrame::Raised );
  {  
    QImage img = QImage( get_cfile( "images/confsmenu.png" ) );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix = pix.fromImage(img);
    
    QPalette p(configsFrame->palette());
    p.setBrush(QPalette::Background, pix);
    configsFrame->setPalette(p);
    configsFrame->setAutoFillBackground(true);
  }



  QVBoxLayout *configsLayout = new QVBoxLayout( configsFrame); 
  configsLayout->setMargin( 0 );
  configsLayout->setSpacing( 6 );
  configsLayout->addSpacing(5);

  docItem = new sMenuItem( configsFrame );
  docItem->setMinimumSize( QSize( 180, 32 ) );
  docItem->connectItem( this, SLOT(close()) );
  configsLayout->addWidget( docItem );
  {
    QImage img;
     if(img.isNull())
       img = QImage( get_cfile( "images/mydocs.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));


    docItem->setPixmap( pix );
    docItem->setPixSize( 32, 32 );
  }



  recentItem = new sMenuItem( configsFrame );
  recentItem->setMinimumSize( QSize( 180, 32 ) );
  recentItem->connectItem( this, SLOT(close()) );
  configsLayout->addWidget( recentItem );
  {
    QImage img;
    if(img.isNull())
       img = QImage( get_cfile( "images/recent.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));


    recentItem->setPixmap( pix );
    recentItem->setPixSize( 32, 32 );
  }
  

  picItem = new sMenuItem( configsFrame );
  picItem->setMinimumSize( QSize( 180, 32 ) );
  picItem->connectItem( this, SLOT(close()) );
  configsLayout->addWidget( picItem );
  {
    QImage img;
     if(img.isNull())
       img = QImage( get_cfile( "images/mypics.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));


    picItem->setPixmap( pix );
    picItem->setPixSize( 32, 32 );
  }


  soundItem = new sMenuItem( configsFrame );
  soundItem->setMinimumSize( QSize( 180, 32 ) );
  soundItem->connectItem( this, SLOT(close()) );
  configsLayout->addWidget( soundItem );
  {
    QImage img;
     if(img.isNull())
       img = QImage( get_cfile( "images/mymusic.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));


    soundItem->setPixmap( pix );
    soundItem->setPixSize( 32, 32 );
  }



  QFrame *seperator_2 = new QFrame( configsFrame );
  seperator_2->setFrameShape( QFrame::HLine );
  seperator_2->setFrameShadow( QFrame::Sunken );
  seperator_2->setFixedWidth(120);
  configsLayout->addWidget( seperator_2 );
  configsLayout->setAlignment(seperator_2, Qt::AlignCenter);

  controlItem = new sMenuItem( configsFrame );
  controlItem->setMinimumSize( QSize( 180, 32 ) );
  controlItem->connectItem( this, SLOT(close()) );
  configsLayout->addWidget( controlItem );
  controlItem->setCommand("kcontrol");
   {
     QImage img;
     if(img.isNull())
       img = QImage( get_cfile( "images/setting.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));


    controlItem->setPixmap( pix );
    controlItem->setPixSize( 32, 32 );
  }
 
  QFrame *seperator_3 = new QFrame( configsFrame );
  seperator_3->setFrameShape( QFrame::HLine );
  seperator_3->setFrameShadow( QFrame::Sunken );
  seperator_3->setFixedWidth(120);
  configsLayout->addWidget( seperator_3 );
  configsLayout->setAlignment(seperator_3, Qt::AlignCenter);

  runItem = new sMenuItem( configsFrame );
  runItem->setMinimumSize( QSize( 180, 35 ) );
  runItem->connectItem( this, SLOT(close()) );
  runItem->setCommand("hrun");
  configsLayout->addWidget( runItem );
  {
    QImage img = QImage( get_cfile( "images/exec.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));
    
    runItem->setPixmap( pix ); 
    runItem->setPixSize( 32, 32 );
  }

  configsLayout->addStretch(100);

  midLayout->addWidget( configsFrame );
  mainLayout->addLayout(midLayout);


  /******************************************************************
   *
   * Exit Frame
   *
   *****************************************************************/
  QFrame *exitFrame = new QFrame( this );
  exitFrame->setFixedSize( QSize( 380, 42 ) );
  exitFrame->setFrameShape( QFrame::NoFrame );
  exitFrame->setFrameShadow( QFrame::Raised );
  {
    QPalette p(exitFrame->palette());
    p.setBrush(QPalette::Background,
	       QPixmap(get_cfile("images/menubuttom.png")));
    exitFrame->setPalette(p);
    exitFrame->setAutoFillBackground(true);
  }

  QHBoxLayout *exitLayout = new QHBoxLayout( exitFrame); 
  exitLayout->setMargin( 0 );
  exitLayout->setSpacing(2);
  exitLayout->addSpacing( 150 );


  killItem = new sMenuItem( exitFrame );
  killItem->connectItem( this, SLOT(close()) );
  exitLayout->addWidget( killItem );
  {
    QImage img = QImage( get_cfile( "images/xkill.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(24,24);
    pix = pix.fromImage(img.scaled(24,24));

    killItem->setPixmap( pix );
    killItem->setPixSize( 24, 24 );
  }


  exitItem = new sMenuItem( exitFrame );
  exitItem->connectItem( this, SLOT(close()) );
  exitLayout->addWidget( exitItem );
  {  
    QImage img = QImage( get_cfile( "images/exit.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(24,24);
    pix = pix.fromImage(img.scaled(24,24));

    exitItem->setPixmap( pix );
    exitItem->setPixSize( 24, 24 );
  }




  mainLayout->addWidget( exitFrame );

  setLayout(mainLayout);
  languageChange();
}

void xpMenu::readRecents()
{
  if(defaults::cfdir.isNull()){
    QString fname(getenv("HOME"));
    
    if(! fname.isNull())
      defaults::cfdir = fname + "/.config/hde2";
  }
  QString cmp( defaults::cfdir + "/recentPrograms" );
  
  QFile file( cmp );
  if(!file.exists()){
    if ( file.open( QIODevice::WriteOnly ) ) {
      QTextStream stream( &file );
      stream << "";
      file.close();
      return;
    }
  }

  QStringList list;
  if ( file.open( QIODevice::ReadOnly ) ) {
    QTextStream stream( &file );
    while (!stream.atEnd()) {
      QString line = stream.readLine();
      list << line;
    }
    file.close();
  }


  if(list.size() > 0)
  {
    QString Recent1 = list.at(0);
    hdeItem item =  defaults::readItem(Recent1);
    if(item.error.isNull()){
      recent1->setText( item.name );
      recent1->setPixmap(QPixmap(getIconFile(item.icon, "mid")));
      recent1->setCommand(Recent1);
    }
  }
  if(list.size() > 1)
  {
    QString Recent2 = list.at(1);
    hdeItem item =  defaults::readItem(Recent2);
    if(item.error.isNull()){
      recent2->setText( item.name );
      recent2->setPixmap(QPixmap(getIconFile(item.icon, "mid")));
      recent2->setCommand(Recent2);
    }
  }
  if(list.size() > 2)
  {
    QString Recent3 = list.at(2);
    hdeItem item =  defaults::readItem(Recent3);
    if(item.error.isNull()){
      recent3->setText( item.name );
      recent3->setPixmap(QPixmap(getIconFile(item.icon, "mid")));
      recent3->setCommand(Recent3);
    }
  }
  if(list.size() > 3)
  {
    QString Recent4 = list.at(3);
    hdeItem item =  defaults::readItem(Recent4);
    if(item.error.isNull()){
      recent4->setText( item.name );
      recent4->setPixmap(QPixmap(getIconFile(item.icon, "mid")));
      recent4->setCommand(Recent4);
    }
  }
  if(list.size() > 4)
  {
    QString Recent5 = list.at(4);
    hdeItem item =  defaults::readItem(Recent5);
    if(item.error.isNull()){
      recent5->setText( item.name );
      recent5->setPixmap(QPixmap(getIconFile(item.icon, "mid")));
      recent5->setCommand(Recent5);
    }
  }
  if(list.size() > 5)
  {
    QString Recent6 = list.at(5);
    hdeItem item =  defaults::readItem(Recent6);
    if(item.error.isNull()){
      recent6->setText( item.name );
      recent6->setPixmap(QPixmap(getIconFile(item.icon, "mid")));
      recent6->setCommand(Recent6);
    }
  }
}


void xpMenu::languageChange()
{
  QString fullname = defaults::get_fullname();
  
  if(fullname.isNull())
  {
    personalFrame->setText( tr( "Your Name" ) );
  }
  else
    personalFrame->setText( fullname );
  
  //    internetBrowser->setText( tr( "Internet Browser" ) );
  internetBrowser->setText( tr( "Mozilla Firefox" ) );
  //    emailClient->setText( tr( "Email Client" ) );
  emailClient->setText( tr( "Mozilla Thunderbird" ) );
  programs->setText( tr( "All Programs" ) );


  docItem->setText( tr( "My Documents" ) );
  recentItem->setText( tr( "Recent Docoments" ) );

  picItem->setText( tr( "My Pictures" ) );
  soundItem->setText( tr( "My Sound Files" ) );
  controlItem->setText( tr( "Control Panel" ) );
  runItem->setText( tr( "Run program" ) );

  killItem->setText( tr( "Kill window" ) );
  exitItem->setText( tr( "End Session" ) );
  readRecents();
}


//void xpMenu::paintEvent( QPaintEvent *e )
void xpMenu::moveEvent ( QMoveEvent * event )
{
  QWidget::moveEvent ( event );
  paintBg();
}

void xpMenu::resizeEvent( QResizeEvent *e )
{
  QWidget::resizeEvent(e);
  paintBg();
}

void xpMenu::paintBg()
{
  xwindow *client;
  QImage *bg = new QImage(size(), QImage::Format_RGB32);
  
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
    
    if(client->isVisible() && curdesk )
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
	//	QImage img = client->screenShot->copy(irect);
	QImage img = QImage::fromData(client->screenBytes);
	img = img.copy(irect);
	p.drawImage(QRect(cx,cy,irect.width(),irect.height()), img, 
		    QRect(0, 0, irect.width(), irect.height()));
      }
    }
  }
      
  p.end();

  QImage bgImg(size(), QImage::Format_RGB32);
    
  //  QColor semiTransparentColor = curPal.button().color();
  //  semiTransparentColor.setAlpha(175);
    
  QPainter painter(&bgImg);
  //painter.setBackground(curColor);
  painter.fillRect(0,0,geometry().width(), geometry().height(),
		   Qt::black);
  //if(!bg->isNull())
  QRectF target(0,0,geometry().width(), geometry().height());
  //QRectF source(cx, cy, cw, ch);
  painter.drawImage(target, *bg);
  //  painter.drawPixmap(0,0,geometry().width(), geometry().height(), 
  //  		     bg->copy(0,0,geometry().width(), geometry().height()));
  //painter.fillRect(0,0,geometry().width(), geometry().height(), curColor);
    
  painter.end();
  delete bg;
  //QPixmap pix = bg.copy( geometry());
  
  QPalette pal = palette();
  pal.setBrush(QPalette::Background, bgImg);
  pal.setBrush(QPalette::Button,bgImg);
  pal.setBrush(QPalette::Window, bgImg);
  setPalette(pal);
  //  setAutoFillBackground(true);
}

