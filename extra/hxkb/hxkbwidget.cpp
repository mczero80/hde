
#include <qmenu.h>
#include <qcursor.h>
#include "hxkbwidget.h"
#include <libhde.h>
#include <QX11Info>
#include <iostream>
using std:: cout; using std::endl;using std::cerr;
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

hXkbWidget::hXkbWidget( QWidget* parent, const char* name )
    : QLabel( parent )
{
  
  Display *dsp = QX11Info::display(); // get the display
  WId win = winId();           // get the window
  int r;
  int data = 1;
  r = XInternAtom(dsp, "KWM_DOCKWINDOW", false);
  XChangeProperty(dsp, win, r, r, 32, 0, (uchar *)&data, 1);
  r = XInternAtom(dsp, "_KDE_NET_WM_SYSTEM_TRAY_WINDOW_FOR", false);
  XChangeProperty(dsp, win, r, XA_WINDOW, 32, 0, (uchar *)&data, 1);

    setMouseTracking( TRUE );
    languageChange();

    setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    setText ( "us" );
    
    menu = new QMenu(this);
    QAction *action;
    action = menu->addAction( "ar" );
    action = menu->addAction( "us" );
    menu->addSeparator(); 
    action = menu->addAction( tr("&Properties") );
    connect(menu, SIGNAL(triggered( QAction *)), this,
	    SLOT(changeXkb(QAction*)));
  /*  
    clearWState( WState_Polished );

    //    setBackgroundMode(Qt::NoBackground);
    setPaletteBackgroundColor(QColor("blue"));
    setPaletteForegroundColor(QColor("white"));
    setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    setText ( "us" );
    
    menu = new QPopupMenu(this, "hXkbMenu");
    menu->insertItem( "ar", this, SLOT(changeXkb(int)) );
    menu->insertItem( "us", this,SLOT(changeXkb(int)) );
    menu->insertSeparator(); 
    menu->insertItem( "&Properties" );
*/
}



/*
 *  Destroys the object and frees any allocated resources
 */
hXkbWidget::~hXkbWidget()
{
    // no need to delete child widgets, Qt does it all for us
}



/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void hXkbWidget::languageChange()
{
  setText( QString::null );
}


void hXkbWidget::changeXkb(QAction *action)
{
  //QAction * action = menu->activeAction();
  cout << action->text().toAscii().data() << endl;
  if(action->text() == tr("&Properties"))
  {
    cout << "\"Properties\" has been called" << endl;
  }else{
    execCmd("setxkbmap " +  action->text());
    setText(action->text());
  }
  /*
  cout << QString::number(item) << endl;
  cout << menu->text( item ) << endl;
  execCmd("setxkbmap " +  menu->text( item ));
  setText(menu->text( item ));
  */
}

void hXkbWidget::setNextXkb()
{
  cout << "Next Xkb\n";
}


void hXkbWidget::mousePressEvent( QMouseEvent * e )
{
  cout << "mouse pressed\n";
  menu->exec(mapToGlobal( QPoint(0,0) ) );
  /*
  cout << "mouse pressed\n";
  //  menu->exec( QCursor::pos() );
  menu->exec(mapToGlobal( QPoint(0,0) ) );
  */
}

void hXkbWidget::mouseReleaseEvent( QMouseEvent * e )
{
  cout << "mouse released\n";

}
