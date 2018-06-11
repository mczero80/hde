/****************************************************************************
 **
 **				hcloseframe.cpp
 **			=========================
 **
 **  begin                : Tue Jul 02 2002
 **  copyright            : (C) 2002-2006 by Haydar Alkaduhimi, under GPL
 **  email                : haydar@haydarnet.nl
 **
 **  A frame with close button
 **
 ****************************************************************************/

#include "hcloseframe.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qtoolbutton.h>
#include <qmime.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "defaults.h"

static QPixmap load_pixmap( const QString &name )
{
  //  QString nam = ":/images/" + name;
  QPixmap pix(":/images/" + name);
  return pix;
}

HCloseFrame::HCloseFrame( QWidget* parent,  const char* name, Qt::WFlags fl )
    : QWidget( parent, fl )
{
  //    if ( !name )
  //	setName( "HCloseFrame" );
    QPalette palette;
    resize( 178, 344 ); 
    //    setCaption( trUtf8( "HCloseFrame" ) );

    //    widgetList.setAutoDelete( TRUE );
    hidden = false;

    //    wdgetLayout = new QVBoxLayout( this, 0, 0, "wdgetLayout"); 
    wdgetLayout = new QVBoxLayout( this);
    wdgetLayout->setMargin(0);
    wdgetLayout->setSpacing(0);
    //    captionLayout = new QHBoxLayout( this, 0, 0, "captionLayout"); 
    captionLayout = new QHBoxLayout( 0); 
    captionLayout->setMargin(0);
    captionLayout->setSpacing(0);

    // Ad a caption label
    captionLable = new QLabel( this );
    captionLable->setMinimumSize( QSize( 20, 20 ) );
    captionLable->setMaximumSize( QSize( 32767, 20 ) );
    captionLable->setText( trUtf8( "Caption" ) );
    //    captionLable->setPaletteForegroundColor(QColor("white"));
    //    captionLable->setPaletteBackgroundColor(QColor("darkGray"));
    palette.setColor(captionLable->foregroundRole(), QColor("white"));
    captionLable->setPalette(palette);
    palette.setColor(captionLable->backgroundRole(), QColor("darkGray"));
    captionLable->setPalette(palette);
    captionLayout->addWidget( captionLable );

    // Make a close button
    closeBtn = new QToolButton( this );
    closeBtn->setMinimumSize( QSize( 20, 20 ) );
    closeBtn->setMaximumSize( QSize( 20, 20 ) );
    //closeBtn->setPaletteBackgroundColor(QColor("darkGray"));
    palette.setColor(closeBtn->backgroundRole(), QColor("darkGray"));
    closeBtn->setPalette(palette);


    hideBtn = new QToolButton( this );
    hideBtn->setMinimumSize( QSize( 20, 20 ) );
    hideBtn->setMaximumSize( QSize( 20, 20 ) );
    //    hideBtn->setPaletteBackgroundColor(QColor("darkGray"));
    palette.setColor(hideBtn->backgroundRole(), QColor("darkGray"));
    hideBtn->setPalette(palette);

    QPixmap actx;
    actx = QPixmap( defaults::get_cfile("images/tactivex.png") );
    // the close button should have a bold X caption
    if(actx.isNull()){
	actx = 	load_pixmap("tactivex.png");
    }
    if(actx.isNull()){
      QFont closeBtn_font(  hideBtn->font() );
      closeBtn_font.setBold( TRUE );
      closeBtn->setFont( closeBtn_font );  
      closeBtn->setText(  "x"  );	    
    }else{
      closeBtn->setIcon(QIcon(actx));
    }
    
    QPixmap actup;
    actup = QPixmap( defaults::get_cfile("images/tactiveup.png") );
    // the close button should have a bold X caption
    if(actup.isNull()){
	actup = 	load_pixmap("tactiveup.png");
    }
    if(actup.isNull()){
	QFont hideBtn_font(  hideBtn->font() );
        hideBtn_font.setBold( TRUE );
        hideBtn->setFont( hideBtn_font );  
        hideBtn->setText(  "-"  );	    
    }else{
	hideBtn->setIcon(QIcon(actup));
    }
    

    // Make it flat
    closeBtn->setAutoRaise(true);
    hideBtn->setAutoRaise(true);

    captionLayout->addWidget( hideBtn );
    captionLayout->addWidget( closeBtn );
    wdgetLayout->addLayout( captionLayout );

    wdgetLayout->setAlignment( Qt::AlignTop );

    // Hide on click
    connect( closeBtn, SIGNAL( clicked() ), this, SLOT( hide() ) );
    connect( hideBtn, SIGNAL( clicked() ), this, SLOT( showHideWidgets() ) );
}

HCloseFrame::~HCloseFrame()
{
}

void HCloseFrame::changeCaption(const QString &cap){ 
  //setCaption(" " + cap); 
    captionLable->setText(" " + cap);
}

void HCloseFrame::addWidget(QWidget *w){
    widgetList.append(w);
    wdgetLayout->addWidget(w);
}

QString HCloseFrame::caption() const
{
  return captionLable->text();
}

void HCloseFrame::hideWidgets()
{
    QWidget *w;
    for (int i = 0; i < widgetList.size(); ++i) {
      w = widgetList.at(i);
      if (w)
	w->hide();
    }
    /*
    for ( w = widgetList.first(); w; w = widgetList.next() )
	w->hide();
    */

    QPixmap actdown;
    actdown = QPixmap( defaults::get_cfile("images/tactivedown.png") );
    // the close button should have a bold X caption
    if(actdown.isNull()){
	actdown = 	load_pixmap("tactivedown.png");
    }
    if(actdown.isNull()){
	QFont hideBtn_font(  hideBtn->font() );
        hideBtn_font.setBold( TRUE );
        hideBtn->setFont( hideBtn_font );  
        hideBtn->setText(  "-"  );	    
    }else{
	hideBtn->setIcon(QIcon(actdown));
    }
    hidden = true;

}

void HCloseFrame::showWidgets()
{
  QWidget *w;
  for (int i = 0; i < widgetList.size(); ++i) {
    w = widgetList.at(i);
    if (w)
      w->show();
  }
  /*
    for ( w = widgetList.first(); w; w = widgetList.next() )
	w->show();
    */
    QPixmap actup;
    actup = QPixmap( defaults::get_cfile("images/tactiveup.png") );
    // the close button should have a bold X caption
    if(actup.isNull()){
	actup = 	load_pixmap("tactiveup.png");
    }
    if(actup.isNull()){
	QFont hideBtn_font(  hideBtn->font() );
        hideBtn_font.setBold( TRUE );
        hideBtn->setFont( hideBtn_font );  
        hideBtn->setText(  "-"  );	    
    }else{
	hideBtn->setIcon(QIcon(actup));
    }
    
    hidden = false;

}

void HCloseFrame::showHideWidgets()
{
    if( hidden )
	showWidgets();
    else
	hideWidgets();
}

