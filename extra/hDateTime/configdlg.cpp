/****************************************************************************
** Form implementation generated from reading ui file 'configdlg.ui'
**
** Created: Sun Oct 28 21:19:24 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "configdlg.h"
#include <hcalender.h>
#include <hclock.h>
#include <defaults.h>


HCalender *hc;

configDlg::configDlg( QWidget* parent,  const char* name, bool modal)
    : QDialog( parent )
{
  
    //    resize( 470, 240 );
  setModal(modal);
  resize( 470, 240 );

  setWindowTitle( tr( "Clock Configuration" ) );
  /*
    XClassHint ch;
    ch.res_name = "Clock Configuration";
    ch.res_class = "Clock Configuration";

    XSetClassHint(qt_xdisplay(), winId(), &ch);
  */

    QBoxLayout * hl = new QHBoxLayout( 0 );
    hl->setMargin( 6 );
    hl->setSpacing( 6 ); 
    
    QGroupBox *calGroup = new QGroupBox(this);
    calGroup->setTitle( trUtf8("Calender") );
    calGroup->setFixedSize( 310, 210 ); 
    
    
    hc = new HCalender(calGroup, "HCalender", defaults::hijriDate);
    
    hc->setGeometry( QRect( 10, 20, 285, 178 ) ); 
    //    if( defaults::hijriDate )
    //    hc->setHijri(defaults::hijriDate);
    //      cout << "hijriDate" << endl;
    //QVBoxLayout *vbox = new QVBoxLayout;
    // vbox->addWidget(hc);
    //vbox->addWidget();
    //calGroup->setLayout(vbox);

    hl->addWidget( calGroup );
    
    
    QGroupBox *clockGroup = new QGroupBox(this);
    clockGroup->setTitle( trUtf8("Clock") );
    clockGroup->setFixedSize( 150, 210  );
    HClock *hcl = new HClock(clockGroup, "hcl" );
    //    hcl->setGeometry( QRect( 10, 20, 150, 170 ) );
    hcl->setGeometry( QRect( 10, 20, 130, 180 ) );
    hl->addWidget( clockGroup );

    
    QBoxLayout * vl = new QVBoxLayout( this );
    vl->setMargin( 2 );
    vl->setSpacing( 2 ); 
    vl->addLayout(hl);
    vl->addSpacing(10);

    

    // QBoxLayout *Layout1 = new QHBoxLayout( this );
    QBoxLayout *Layout1 = new QHBoxLayout( 0 );
    Layout1->setMargin( 0 );
    Layout1->setSpacing( 6 ); 
    QSpacerItem* spacer = new QSpacerItem( 0, 0, QSizePolicy::Expanding,
					   QSizePolicy::Minimum );
    Layout1->addItem( spacer );

    
    QPushButton *okBtn = new QPushButton( this );
    okBtn->setText( trUtf8( "OK" ) );
    okBtn->setDefault( TRUE );
    Layout1->addWidget( okBtn );

    QPushButton *cancelBtn = new QPushButton( this );
    cancelBtn->setText( trUtf8( "Cancel" ) );
    Layout1->addWidget( cancelBtn );
    
    QPushButton *applyBtn = new QPushButton( this );
    applyBtn->setEnabled( FALSE );
    applyBtn->setText( trUtf8( "apply" ) );
    Layout1->addWidget( applyBtn );
    vl->addLayout( Layout1 );

    connect( cancelBtn, SIGNAL( clicked() ), this, SLOT( close() ) );
  
}

/*  
 *  Destroys the object and frees any allocated resources
 */
configDlg::~configDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

