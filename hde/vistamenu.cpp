/****************************************************************************
 **
 **				vistamenu.h
 **			==========================
 **
 **  begin                : Mar 08 2007
 **  copyright            : (C) 2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  The Vista Menu style in hde.
 **
 ****************************************************************************/

#include "vistamenu.h"

#include <libhde.h>

#include <QtGui>
#include <defaults.h>

#include <iostream>
using std:: cout; using std::endl;using std::cerr;

#include "xwindow.h"
#include "qapp.h"


userIcon::userIcon( QWidget* parent )
  : QLabel(parent)
{
  setFixedSize(64,64);
  userPix = true;
}

void userIcon::paintEvent( QPaintEvent * )
{
  //QPixmap px(width(), height());
  QPainter p( this );

  if(!pixmap()->isNull())
  {
    if(userPix)
    {
      QPixmap px(48, 48);
      px = pixmap()->scaled(48,48, Qt::IgnoreAspectRatio, 
			    Qt::SmoothTransformation);
      p.drawPixmap ( 7, 7,px);

      QColor clr(Qt::white);
      clr.setAlpha(127);
      QPen whitePen(clr, 5, Qt::SolidLine, Qt::SquareCap,Qt::RoundJoin);
      p.setPen(whitePen);
      QRect rectangle(4, 4, 52, 52);
      p.drawRoundRect(rectangle, 25, 25);

      whitePen.setWidth(2);
      whitePen.setColor(Qt::white);
      rectangle.setCoords(5, 5, 54, 54);
      p.setPen(whitePen);
      p.drawRoundRect(rectangle, 25, 25);

      rectangle.setCoords(5, 5, 56, 56);
      p.drawRoundRect(rectangle, 25, 25);

      QPen blackPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap,Qt::RoundJoin);
      p.setPen(blackPen);
      rectangle.setCoords(1, 1, 58, 58);
      p.drawRoundRect(rectangle, 25, 25);

      rectangle.setCoords(6, 6, 52, 52);
      p.drawRoundRect(rectangle, 25, 25);

      
    }else{
      QPixmap px(64, 64);
      px = pixmap()->scaled(64,64,Qt::IgnoreAspectRatio,
			    Qt::SmoothTransformation);
      p.drawPixmap ( 0, 0, px);
    }
  }

  p.end();
}

vistaMenu::vistaMenu( QWidget* parent, Qt::WFlags fl )
  : startMenu( parent, fl )

{
  lightHBg = QPixmap( get_cfile( "images/vista/menuWItemH.png") );
  darkHBg = QPixmap( get_cfile( "images/vista/menuDItemH.png") );
  

  initIt();
}

void vistaMenu::initIt()
{
  setFixedSize( QSize(406, 575) );
  setFrameShape( QFrame::NoFrame );

  /********************************************************************
   *
   * Draw BG, later also in resize.....
   *
   *******************************************************************/
  {
    QImage img = QImage( get_cfile( "images/vista/vistaMenuBG.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix = pix.fromImage(img.scaled(406, 575, Qt::IgnoreAspectRatio,
					   Qt::SmoothTransformation));
    QPalette p(palette());
    p.setBrush(QPalette::Background, pix);
    setPalette(p);
    setAutoFillBackground(true);
  }


  QVBoxLayout *mainLayout = new QVBoxLayout( this); 
  mainLayout->setMargin( 0 );
  mainLayout->setSpacing( 0 );


  QHBoxLayout *topLayout = new QHBoxLayout( 0 ); 
  topLayout->setMargin( 0 );
  topLayout->setSpacing( 0 );
  topLayout->addSpacing( 14 );

  
  /*****************************************************************
   *
   * Programs
   *
   ****************************************************************/
  QFrame *programsFrame = new QFrame( this );
  programsFrame->setFixedSize( QSize( 241, 536 ) );
  programsFrame->setFrameShape( QFrame::NoFrame );
  programsFrame->setFrameShadow( QFrame::Plain );
  

  QVBoxLayout *programsLayout = new QVBoxLayout( programsFrame ); 
  programsLayout->setMargin( 0 );
  programsLayout->setSpacing( 2 );

  programsLayout->addSpacing(45);

  QPalette programsPal = palette();
  programsPal.setColor ( QPalette::Text, Qt::black );
  programsPal.setColor ( QPalette::HighlightedText, Qt::black );

  internetBrowser = new sMenuItem( programsFrame );
  internetBrowser->setMinimumSize( QSize( 180, 35 ) );
  internetBrowser->setCommand("firefox");
  internetBrowser->setHBGPixmap(lightHBg);
  internetBrowser->setPalette(programsPal);
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
  emailClient->setHBGPixmap(lightHBg);
  emailClient->setPalette(programsPal);
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
  recent1->setHBGPixmap(lightHBg);
  recent1->setPalette(programsPal);
  
  recent2 = new sMenuItem( programsFrame );
  recent2->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent2 );
  recent2->connectItem( this, SLOT(close()) );
  recent2->setHBGPixmap(lightHBg);
  recent2->setPalette(programsPal);
  
  recent3 = new sMenuItem( programsFrame );
  recent3->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent3 );
  recent3->connectItem( this, SLOT(close()) );
  recent3->setHBGPixmap(lightHBg);
  recent3->setPalette(programsPal);
 
  recent4 = new sMenuItem( programsFrame );
  recent4->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent4 );
  recent4->connectItem( this, SLOT(close()) );
  recent4->setHBGPixmap(lightHBg);
  recent4->setPalette(programsPal);

  recent5 = new sMenuItem( programsFrame );
  recent5->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent5 );
  recent5->connectItem( this, SLOT(close()) );
  recent5->setHBGPixmap(lightHBg);
  recent5->setPalette(programsPal);

  recent6 = new sMenuItem( programsFrame );
  recent6->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent6 );
  recent6->connectItem( this, SLOT(close()) );
  recent6->setHBGPixmap(lightHBg);
  recent6->setPalette(programsPal);
 

  recent7 = new sMenuItem( programsFrame );
  recent7->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent7 );
  recent7->connectItem( this, SLOT(close()) );
  recent7->setHBGPixmap(lightHBg);
  recent7->setPalette(programsPal);

  recent8 = new sMenuItem( programsFrame );
  recent8->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent8 );
  recent8->connectItem( this, SLOT(close()) );
  recent8->setHBGPixmap(lightHBg);
  recent8->setPalette(programsPal);

  recent9 = new sMenuItem( programsFrame );
  recent9->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent9 );
  recent9->connectItem( this, SLOT(close()) );
  recent9->setHBGPixmap(lightHBg);
  recent9->setPalette(programsPal);

  recent10 = new sMenuItem( programsFrame );
  recent10->setMinimumSize( QSize( 180, 35 ) );
  programsLayout->addWidget( recent10 );
  recent10->connectItem( this, SLOT(close()) );
  recent10->setHBGPixmap(lightHBg);
  recent10->setPalette(programsPal);

  programsLayout->addStretch();


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
  programs->setHBGPixmap(lightHBg);
  programs->setPalette(programsPal);
  {
    QPixmap pix = QPixmap(get_ifile("grp.png", "mid"));
    if(pix.isNull())
      pix = get_cfile( "images/grp.png");
    programs->setPixmap(pix);
  }
  programsLayout->addWidget( programs );

  programsLayout->addSpacing( 3 );
  

  topLayout->addWidget( programsFrame );


  topLayout->addSpacing( 7 );

  /*****************************************************************
   *
   * Configs
   *
   ****************************************************************/
  QFrame *configsFrame = new QFrame( this );
  configsFrame->setFrameShape( QFrame::NoFrame );
  configsFrame->setFrameShadow( QFrame::Raised );
  QVBoxLayout *configsLayout = new QVBoxLayout( configsFrame ); 
  configsLayout->setMargin( 0 );
  configsLayout->setSpacing( 2 );

  

  usericon = new userIcon(configsFrame);
  {
    QPixmap pix = QPixmap(get_ifile("hl.png", "mid"));
    if(pix.isNull())
      pix = get_cfile( "images/hl.png");
    usericon->setPixmap(pix);
  }
  configsLayout->addWidget(usericon);
  configsLayout->setAlignment(usericon, Qt::AlignCenter);

  QPalette configsPal = palette();
  configsPal.setColor ( QPalette::Text, Qt::white );
  configsPal.setColor ( QPalette::HighlightedText, Qt::white );
  

  userItem = new sMenuItem( configsFrame );
  userItem->setMinimumSize( QSize( 120, 32 ) );
  userItem->connectItem( this, SLOT(close()) );
  userItem->setPalette(configsPal);
  userItem->setHBGPixmap(darkHBg);

  connect(userItem, SIGNAL(highlighted(sMenuItem *)), this, 
	  SLOT(selectItem(sMenuItem *)));
  configsLayout->addWidget( userItem );

  docItem = new sMenuItem( configsFrame );
  docItem->setMinimumSize( QSize( 120, 32 ) );
  docItem->connectItem( this, SLOT(close()) );
  docItem->setPalette(configsPal);
  docItem->setHBGPixmap(darkHBg);
  connect(docItem, SIGNAL(highlighted(sMenuItem *)), this, 
	  SLOT(selectItem(sMenuItem *)));
  configsLayout->addWidget( docItem );
  {
    QImage img;
    if(img.isNull())
       img = QImage( get_cfile( "images/vista/mydocs.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(64,64);
    pix = pix.fromImage(img.scaled(64,64, Qt::IgnoreAspectRatio,
				   Qt::SmoothTransformation));


    docItem->setPixmap( pix );
    docItem->setDrawPixmap(false);
  }


  picItem = new sMenuItem( configsFrame );
  picItem->setMinimumSize( QSize( 120, 32 ) );
  picItem->connectItem( this, SLOT(close()) );
  picItem->setPalette(configsPal);
  picItem->setHBGPixmap(darkHBg);
  connect(picItem, SIGNAL(highlighted(sMenuItem *)), this, 
	  SLOT(selectItem(sMenuItem *)));
  configsLayout->addWidget( picItem );
  {
    QImage img;// = QImage( get_ifile( "folder_image.png", "mid", 
    //	     "filesystems" ));
     if(img.isNull())
       img = QImage( get_cfile( "images/vista/mypics.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(64,64);
    pix = pix.fromImage(img.scaled(64,64, Qt::IgnoreAspectRatio,
				   Qt::SmoothTransformation));


    picItem->setPixmap( pix );
    picItem->setPixSize( 64, 64 );
    picItem->setDrawPixmap(false);
  }


  soundItem = new sMenuItem( configsFrame );
  soundItem->setMinimumSize( QSize( 120, 32 ) );
  soundItem->connectItem( this, SLOT(close()) );
  soundItem->setPalette(configsPal);
  soundItem->setHBGPixmap(darkHBg);
  connect(soundItem, SIGNAL(highlighted(sMenuItem *)), this, 
	  SLOT(selectItem(sMenuItem *)));
  configsLayout->addWidget( soundItem );
  {
    QImage img;// = QImage( get_ifile( "folder_sound.png", "mid", 
    //	     "filesystems" ));
     if(img.isNull())
       img = QImage( get_cfile( "images/vista/mymusic.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(64,64);
    pix = pix.fromImage(img.scaled(64,64, Qt::IgnoreAspectRatio,
				   Qt::SmoothTransformation));


    soundItem->setPixmap( pix );
    soundItem->setPixSize( 64, 64 );
    soundItem->setDrawPixmap(false);
  }



  QFrame *seperator_2 = new QFrame( configsFrame );
  seperator_2->setFrameShape( QFrame::HLine );
  seperator_2->setFrameShadow( QFrame::Sunken );
  seperator_2->setFixedWidth(90);
  configsLayout->addWidget( seperator_2 );
  configsLayout->setAlignment(seperator_2, Qt::AlignCenter);



  findItem = new sMenuItem( configsFrame );
  findItem->setMinimumSize( QSize( 120, 32 ) );
  findItem->connectItem( this, SLOT(close()) );
  configsLayout->addWidget( findItem );
  findItem->setPalette(configsPal);
  findItem->setHBGPixmap(darkHBg);
  findItem->setCommand("kfind");
  connect(findItem, SIGNAL(highlighted(sMenuItem *)), this, 
	  SLOT(selectItem(sMenuItem *)));
  {
    QImage img;// = QImage( get_ifile( "hwinfo.png", "mid", "filesystems" ));
    if(img.isNull())
      img = QImage( get_cfile( "images/vista/find.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(64,64);
    pix = pix.fromImage(img.scaled(64,64, Qt::IgnoreAspectRatio,
				   Qt::SmoothTransformation));
    

    findItem->setPixmap( pix );
    findItem->setPixSize( 64, 64 );
    findItem->setDrawPixmap(false);
  }
  
  
  recentItem = new sMenuItem( configsFrame );
  recentItem->setMinimumSize( QSize( 120, 32 ) );
  recentItem->connectItem( this, SLOT(close()) );
  configsLayout->addWidget( recentItem );
  recentItem->setPalette(configsPal);
  recentItem->setHBGPixmap(darkHBg);
  connect(recentItem, SIGNAL(highlighted(sMenuItem *)), this, 
	  SLOT(selectItem(sMenuItem *)));
   {
     QImage img;// = QImage( get_ifile( "hwinfo.png", "mid", "filesystems" ));
     if(img.isNull())
       img = QImage( get_cfile( "images/vista/recents.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(64,64);
    pix = pix.fromImage(img.scaled(64,64, Qt::IgnoreAspectRatio,
				   Qt::SmoothTransformation));


    recentItem->setPixmap( pix );
    recentItem->setPixSize( 64, 64 );
    recentItem->setDrawPixmap(false);
  }



  mypcItem = new sMenuItem( configsFrame );
  mypcItem->setMinimumSize( QSize( 120, 32 ) );
  mypcItem->connectItem( this, SLOT(close()) );
  configsLayout->addWidget( mypcItem );
  mypcItem->setPalette(configsPal);
  mypcItem->setHBGPixmap(darkHBg);
  mypcItem->setCommand(defaults::defaultFM + " " + "system:/");
  connect(mypcItem, SIGNAL(highlighted(sMenuItem *)), this, 
	  SLOT(selectItem(sMenuItem *)));
   {
     QImage img;// = QImage( get_ifile( "hwinfo.png", "mid", "filesystems" ));
     if(img.isNull())
       img = QImage( get_cfile( "images/vista/system.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(64,64);
    pix = pix.fromImage(img.scaled(64,64, Qt::IgnoreAspectRatio,
				   Qt::SmoothTransformation));


    mypcItem->setPixmap( pix );
    mypcItem->setPixSize( 64, 64 );
    mypcItem->setDrawPixmap(false);
  }

  netItem = new sMenuItem( configsFrame );
  netItem->setMinimumSize( QSize( 120, 32 ) );
  netItem->connectItem( this, SLOT(close()) );
  configsLayout->addWidget( netItem );
  netItem->setPalette(configsPal);
  netItem->setHBGPixmap(darkHBg);
  netItem->setCommand(defaults::defaultFM + " " + "remote:/");
  connect(netItem, SIGNAL(highlighted(sMenuItem *)), this, 
	  SLOT(selectItem(sMenuItem *)));
   {
     QImage img;// = QImage( get_ifile( "hwinfo.png", "mid", "filesystems" ));
     if(img.isNull())
       img = QImage( get_cfile( "images/vista/network.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(64,64);
    pix = pix.fromImage(img.scaled(64,64, Qt::IgnoreAspectRatio,
				   Qt::SmoothTransformation));


    netItem->setPixmap( pix );
    netItem->setPixSize( 64, 64 );
    netItem->setDrawPixmap(false);
  }


  controlItem = new sMenuItem( configsFrame );
  controlItem->setMinimumSize( QSize( 120, 32 ) );
  controlItem->connectItem( this, SLOT(close()) );
  configsLayout->addWidget( controlItem );
  controlItem->setCommand("kcontrol");
  controlItem->setPalette(configsPal);
  controlItem->setHBGPixmap(darkHBg);
  connect(controlItem, SIGNAL(highlighted(sMenuItem *)), this, 
	  SLOT(selectItem(sMenuItem *)));
   {
     QImage img;// = QImage( get_ifile( "hwinfo.png", "mid", "filesystems" ));
     if(img.isNull())
       img = QImage( get_cfile( "images/setting.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(64,64);
    pix = pix.fromImage(img.scaled(64,64, Qt::IgnoreAspectRatio,
				   Qt::SmoothTransformation));


    controlItem->setPixmap( pix );
    controlItem->setPixSize( 64, 64 );
    controlItem->setDrawPixmap(false);
  }
 

  QFrame *seperator_3 = new QFrame( configsFrame );
  seperator_3->setFrameShape( QFrame::HLine );
  seperator_3->setFrameShadow( QFrame::Sunken );
  seperator_3->setFixedWidth(90);
  configsLayout->addWidget( seperator_3 );
  configsLayout->setAlignment(seperator_3, Qt::AlignCenter);

  runItem = new sMenuItem( configsFrame );
  runItem->setMinimumSize( QSize( 120, 35 ) );
  runItem->connectItem( this, SLOT(close()) );
  runItem->setCommand("hrun");
  runItem->setPalette(configsPal);
  runItem->setHBGPixmap(darkHBg);
  connect(runItem, SIGNAL(highlighted(sMenuItem *)), this, 
	  SLOT(selectItem(sMenuItem *)));
  configsLayout->addWidget( runItem );
  {
    QImage img = QImage( get_cfile( "images/exec.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(64,64);
    pix = pix.fromImage(img.scaled(64,64, Qt::IgnoreAspectRatio,
				   Qt::SmoothTransformation));
    
    runItem->setPixmap( pix ); 
    runItem->setPixSize( 64, 64 );
    runItem->setDrawPixmap(false);
  }





  configsLayout->addStretch();




  topLayout->addWidget( configsFrame );
  topLayout->addSpacing( 3 );


  mainLayout->addLayout(topLayout);
  mainLayout->addStretch();

  /******************************************************************
   *
   * Exit Frame
   *
   *****************************************************************/
  QFrame *exitFrame = new QFrame( this );
  exitFrame->setFixedSize( QSize( 406, 30 ) );
  exitFrame->setFrameShape( QFrame::NoFrame );
  exitFrame->setFrameShadow( QFrame::Raised );

  QHBoxLayout *exitLayout = new QHBoxLayout( exitFrame); 
  exitLayout->setMargin( 0 );
  exitLayout->setSpacing(2);
  //    layout8->addStretch(10);
  exitLayout->addSpacing( 265 );


  killItem = new sMenuItem( exitFrame );
  killItem->connectItem( this, SLOT(close()) );
  killItem->setPalette(configsPal);
  killItem->setHBGPixmap(darkHBg);
  killItem->setBGPixmap(darkHBg);
  exitLayout->addWidget( killItem );
  {
    QImage img = QImage( get_cfile( "images/xkill.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    //QPixmap pix;
    QPixmap pix(24,24);
    pix = pix.fromImage(img.scaled(24,24, Qt::IgnoreAspectRatio,
				   Qt::SmoothTransformation));

    killItem->setPixmap( pix );
    killItem->setPixSize( 24, 24 );
  }


  exitItem = new sMenuItem( exitFrame );
  exitItem->connectItem( this, SLOT(close()) );
  exitItem->setPalette(configsPal);
  exitItem->setHBGPixmap(darkHBg);
  exitItem->setBGPixmap(darkHBg);
  exitLayout->addWidget( exitItem );
  {  
    QImage img = QImage( get_cfile( "images/exit.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    //QPixmap pix;
    QPixmap pix(24,24);
    pix = pix.fromImage(img.scaled(24,24, Qt::IgnoreAspectRatio,
				   Qt::SmoothTransformation));

    exitItem->setPixmap( pix );
    exitItem->setPixSize( 24, 24 );
  }




  mainLayout->addWidget( exitFrame );

  mainLayout->addStretch();


  setLayout(mainLayout);
  languageChange();
}

void vistaMenu::readRecents()
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
  if(list.size() > 6)
  {
    QString Recent7 = list.at(6);
    hdeItem item =  defaults::readItem(Recent7);
    if(item.error.isNull()){
      recent7->setText( item.name );
      recent7->setPixmap(QPixmap(getIconFile(item.icon, "mid")));
      recent7->setCommand(Recent7);
    }
  }
  if(list.size() > 7)
  {
    QString Recent8 = list.at(7);
    hdeItem item =  defaults::readItem(Recent8);
    if(item.error.isNull()){
      recent8->setText( item.name );
      recent8->setPixmap(QPixmap(getIconFile(item.icon, "mid")));
      recent8->setCommand(Recent8);
    }
  }
  if(list.size() > 8)
  {
    QString Recent9 = list.at(8);
    hdeItem item =  defaults::readItem(Recent9);
    if(item.error.isNull()){
      recent9->setText( item.name );
      recent9->setPixmap(QPixmap(getIconFile(item.icon, "mid")));
      recent9->setCommand(Recent9);
    }
  }

  if(list.size() > 9)
  {
    QString Recent10 = list.at(9);
    hdeItem item =  defaults::readItem(Recent10);
    if(item.error.isNull()){
      recent10->setText( item.name );
      recent10->setPixmap(QPixmap(getIconFile(item.icon, "mid")));
      recent10->setCommand(Recent10);
    }
  }

}


void vistaMenu::languageChange()
{
  programs->setText( tr( "All Programs" ) );


  QString fullname = defaults::get_fullname();
  if(fullname.isNull())
    userItem->setText( tr( "Your Name" ) );
  else
    userItem->setText( fullname );

  internetBrowser->setText( tr( "Mozilla Firefox" ) );
  emailClient->setText( tr( "Mozilla Thunderbird" ) );




  docItem->setText( tr("Documents") );
  picItem->setText( tr( "My Pictures" ) );
  soundItem->setText( tr( "My Sound Files" ) );
  //
  findItem->setText( tr( "Search" ) );
  recentItem->setText( tr( "Recent Items" ) );
  mypcItem->setText( tr( "Computer" ) );
  netItem->setText( tr( "Network" ) );
  controlItem->setText( tr( "Control Panel" ) );
  runItem->setText( tr( "Run program" ) );
  readRecents();
}


void vistaMenu::moveEvent ( QMoveEvent * event )
{
  QWidget::moveEvent ( event );
  paintBg();
}

void vistaMenu::showEvent( QShowEvent * e )
{
  QWidget::showEvent(e);
  paintBg();
  selectItem(0);
}

void vistaMenu::resizeEvent( QResizeEvent *e )
{
  QWidget::resizeEvent(e);
  paintBg();
}

void vistaMenu::paintBg()
{
    
  xwindow *client;
  QImage *bg = new QImage(size(), QImage::Format_RGB32);
  
  QPainter p(bg);
  QRectF target0(0,0, width(), height());
  QRectF source0(geometry().x(), geometry().y(), geometry().width(), 
		 geometry().height());
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

  QImage bgImg(size(), QImage::Format_RGB32);
  QPainter painter(&bgImg);
  QRectF target(0,0,geometry().width(), geometry().height());
  painter.drawImage(target, *bg);

  {
    QImage img = QImage( get_cfile( "images/vista/vistaMenuBG.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    img = img.scaled(406, 575, Qt::IgnoreAspectRatio,
		     Qt::SmoothTransformation);
    painter.drawImage(target, img);

  }

    
  painter.end();
  delete bg;  
  
  QPalette pal = palette();
  pal.setBrush(QPalette::Background, bgImg);
  pal.setBrush(QPalette::Button,bgImg);
  pal.setBrush(QPalette::Window, bgImg);
  setPalette(pal);
  setAutoFillBackground(true);  
}

void vistaMenu::selectItem(sMenuItem *item)
{

  if( (item == userItem) || (item == NULL))
  {
    QPixmap pix = QPixmap(get_ifile("hl.png", "mid"));
    if(pix.isNull())
      pix = get_cfile( "images/hl.png");
    usericon->setUserPix(true);
    usericon->setPixmap(pix);
  }else{
    usericon->setUserPix(false);
    usericon->setPixmap(item->pixmap());
  }

}
