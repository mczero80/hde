/****************************************************************************
 **
 **				normalmenu.cpp
 **			==========================
 **
 **  begin                : Jan 01 2005
 **  copyright            : (C) 2005 -2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  The start Menu widget in hde.
 **
 ****************************************************************************/



#include "normalmenu.h"

#include <libhde.h>

#include <QtGui>
#include <defaults.h>

#include <iostream>
using std:: cout; using std::endl;using std::cerr;


void bgWidget::drawIt()
{
  if(bgColor.isValid())
  {
    QPalette palette;
    palette.setBrush(QPalette::Background, bgColor);
    palette.setBrush(QPalette::Button, bgColor);
    palette.setBrush(QPalette::Window, bgColor);
    setPalette(palette);
  }

  if(!bgPixmap.isNull())
  {
    QPalette palette;
    palette.setBrush(QPalette::Background, bgPixmap);
    palette.setBrush(QPalette::Button, bgPixmap);
    palette.setBrush(QPalette::Window, bgPixmap);
    setPalette(palette);
  }
  setAutoFillBackground(true);
}


void sideLabel::changeIt()
{
  if(capText.isNull())
    capText = "Haydar Desktop Envorement";
  if(!color1.isValid())
    color1 = Qt::blue;
  if(!color2.isValid())
    color2 = Qt::black;

  QPixmap pix(size());



  QPainter p(&pix);
  
  //  p.fillRect(rect(), color1);


  QLinearGradient linearGrad(QPoint(0, 0), QPoint(rect().width(), 
						  rect().height()));
  linearGrad.setColorAt(0.0, color2);
  linearGrad.setColorAt(0.9, color1);
  linearGrad.setColorAt(1, color2);

  p.fillRect(rect(), linearGrad);


  p.rotate(270);


  p.setPen( Qt::white );
  QFont fnt = font();
  fnt.setBold(true);
  fnt.setWeight(QFont::Black);
  fnt.setPixelSize(18);

  p.setFont ( fnt );

  QRect r( 25-rect().height(), rect().y(),
	  rect().height(), rect().width());

  if(QApplication::isRightToLeft() )
    p.drawText( r, Qt::AlignVCenter|Qt::AlignRight, capText);
  else
    p.drawText( r, Qt::AlignVCenter|Qt::AlignLeft, capText);

  //p.drawText( 0, 0,capText);

  //  paint.setPen( Qt::white );
  //  paint.drawText( rect(), AlignCenter, "The Text" );


  p.rotate(-90);

  p.end();



  setBgPixmap(pix);
  drawIt();
}


normalMenu::normalMenu( QWidget* parent, Qt::WFlags fl )
  : startMenu( parent, fl )
{
  cout << "Initing" << endl;
  initIt();
  cout << "Finished Initing" << endl;
}


void normalMenu::initIt()
{
  
  resize(250,300);
  setFrameStyle(QFrame::Panel | QFrame::Raised);
  mainLayout = new QHBoxLayout(this); 
  mainLayout->setMargin( 0 );
  mainLayout->setSpacing( 0 );


  sideLabel *sLabel = new sideLabel(this);
  sLabel->setFixedWidth(25);
  sLabel->setBgColor(Qt::blue);
  sLabel->setText("Haydar Desktop Enverment");

  mainLayout->addWidget(sLabel);

  
  QWidget *itemsWidget = new QWidget(this);
  mainLayout->addWidget(itemsWidget);
  
  QVBoxLayout *itemsLayout = new QVBoxLayout(itemsWidget); 
  itemsLayout->setMargin( 0 );
  itemsLayout->setSpacing( 0 );


  programs = new sMenuItem( itemsWidget );
  programs->setMinimumHeight( 38  );
  progsPop = new QMenu;
  programs->setPopup(progsPop);
  {
    QImage img = QImage( get_cfile( "images/grp.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));


    programs->setPixmap( pix );
    programs->setPixSize( 32, 32 );
  }
  itemsLayout->addWidget( programs );


  //itemsLayout->addStretch();

  docItem = new sMenuItem( itemsWidget );
  docItem->setMinimumHeight( 34 );
  docItem->connectItem( this, SLOT(close()) );
  itemsLayout->addWidget( docItem );
  {
    QImage img;// = QImage(get_ifile("folder_txt.png", "mid", "filesystems"));
    if(img.isNull())
      img = QImage( get_cfile( "images/recent.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));


    docItem->setPixmap( pix );
    docItem->setPixSize( 32, 32 );
  }


  settingItem = new sMenuItem( itemsWidget );
  settingItem->setMinimumHeight( 34 );
  settingItem->connectItem( this, SLOT(close()) );
  itemsLayout->addWidget( settingItem );
  {
    QImage img = QImage( get_cfile( "images/setting.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));
    
    settingItem->setPixmap( pix ); 
    settingItem->setPixSize( 32, 32 );
  }


  searchItem = new sMenuItem( itemsWidget );
  searchItem->setMinimumHeight( 34 );
  searchItem->connectItem( this, SLOT(close()) );
  itemsLayout->addWidget( searchItem );
  {
    QImage img = QImage( get_cfile( "images/find.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));
    
    searchItem->setPixmap( pix ); 
    searchItem->setPixSize( 32, 32 );
  }

  helpItem = new sMenuItem( itemsWidget );
  helpItem->setMinimumHeight( 34 );
  helpItem->connectItem( this, SLOT(close()) );
  itemsLayout->addWidget( helpItem );
  {
    QImage img = QImage( get_cfile( "images/help.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));
    
    helpItem->setPixmap( pix ); 
    helpItem->setPixSize( 32, 32 );
  }

  runItem = new sMenuItem( itemsWidget );
  runItem->setMinimumHeight( 34  );
  itemsLayout->addWidget( runItem );
  runItem->connectItem( this, SLOT(close()) );
  runItem->setCommand("hrun");
  {
    QImage img = QImage( get_cfile( "images/exec.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));
    
    runItem->setPixmap( pix ); 
    runItem->setPixSize( 32, 32 );
  }



  QFrame *seperator = new QFrame( itemsWidget );
  seperator->setFrameShape( QFrame::HLine );
  seperator->setFrameShadow( QFrame::Sunken );
  itemsLayout->addWidget( seperator );


  killItem = new sMenuItem( itemsWidget );
  killItem->connectItem( this, SLOT(close()) );
  killItem->setMinimumHeight(34);
  itemsLayout->addWidget( killItem );
  {
    QImage img = QImage( get_cfile( "images/xkill.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));


    killItem->setPixmap( pix );
    killItem->setPixSize( 32, 32 );
  }


  exitItem = new sMenuItem( itemsWidget );
  exitItem->connectItem( this, SLOT(close()) );
  exitItem->setMinimumHeight(34);
  itemsLayout->addWidget( exitItem );
  {
    QImage img = QImage( get_cfile( "images/exit-32.png") );
    if(QApplication::isRightToLeft())
      img = img.mirrored(TRUE,FALSE);
    //QPixmap pix;
    QPixmap pix(32,32);
    pix = pix.fromImage(img.scaled(32,32));

    exitItem->setPixmap( pix );
    exitItem->setPixSize( 32, 32 );
  }


  itemsWidget->setLayout(itemsLayout);

  setLayout(mainLayout);
  languageChange();
  
}


void normalMenu::languageChange()
{
  programs->setText( tr( "All Programs" ) );
  docItem->setText( tr( "Documents" ) );
  settingItem->setText( tr( "Settings" ) );
  searchItem->setText( tr( "Search" ) );
  helpItem->setText( tr( "Help and Support" ) );
  runItem->setText( tr( "Run program" ) );
  killItem->setText( tr( "Kill window" ) );
  exitItem->setText( tr( "End Session" ) );

  readRecents();
}



/***********************************************************************
 *
 * Read recent used programs.
 *
 **********************************************************************/
void normalMenu::readRecents()
{
}
