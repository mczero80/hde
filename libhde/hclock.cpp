/****************************************************************************
**
**	hclock.cpp
**
*****************************************************************************/

#include <QTimeEdit>
#include "hclock.h"
#include <qtimer.h>
#include <qpainter.h>
#include <qbitmap.h>
//Added by qt3to4:
#include <QHBoxLayout>
#include <QVBoxLayout>
/*
#include <Q3PointArray>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
*/
#include <QMouseEvent>
#include <QPaintEvent>


HClock::HClock( QWidget *parent, const char *name, QTime tm )
    : QWidget( parent )
{
    QBoxLayout * vl = new QVBoxLayout( this );

    aclock = new AnalogClock(this, "AClock");
    aclock->setMinimumSize(100, 100);

    vl->addWidget( aclock );
    vl->setStretchFactor( aclock, 10 );
    vl->addSpacing( 5 );

    QBoxLayout * hl = new QHBoxLayout(0 );
    QSpacerItem* spacer1 = new QSpacerItem( 0, 0, QSizePolicy::Minimum, 
					    QSizePolicy::Expanding );
    hl->addItem( spacer1 );

    te = new QTimeEdit(this);
    hl->addWidget( te );

    QSpacerItem* spacer2 = new QSpacerItem( 0, 0, QSizePolicy::Minimum, 
					    QSizePolicy::Expanding );

    hl->addItem( spacer2 );
    vl->addLayout(hl);

    time = tm;		// get current time
    QTimer *internalTimer = new QTimer( this );	// create internal timer
    connect( internalTimer, SIGNAL(timeout()), SLOT(timeout()) );
    internalTimer->start( 1000 );		// emit signal every 1 seconds

    connect( te, SIGNAL( timeChanged( const QTime& ) ), 
	     SLOT( setTime( const QTime& ) ) );

    timeout();
}

void HClock::timeout()
{
    time = time.addSecs( 1 );
    te->setTime( time );
    aclock->setTime( time );
}

void HClock::setTime( const QTime & t )
{
    time = t;
    aclock->setTime( time );
    //    timeout();
}


AnalogClock::AnalogClock( QWidget *parent, const char *name, QTime tm )
    : QWidget( parent )
{
    //    time = QTime::currentTime();		// get current time
    /*
    time = tm;		// get current time
    QTimer *internalTimer = new QTimer( this );	// create internal timer
    connect( internalTimer, SIGNAL(timeout()), SLOT(timeout()) );
    internalTimer->start( 1000 );		// emit signal every 1 seconds
    */
}

void AnalogClock::mousePressEvent( QMouseEvent *e )
{
    if(isTopLevel()) 
	clickPos = e->pos() + QPoint(geometry().topLeft() - frameGeometry().topLeft());
}

void AnalogClock::mouseMoveEvent( QMouseEvent *e )
{
    if(isTopLevel())
	move( e->globalPos() - clickPos );
}

void AnalogClock::setTime( const QTime & t )
{
    time = t;
    //    timeout();
    update();
}

//
// The QTimer::timeout() signal is received by this slot.
//

/*
void AnalogClock::timeout()
{
    time = time.addSecs( 1 );
	    update();
}
*/

void AnalogClock::paintEvent( QPaintEvent * )
{
  //    if ( autoMask() )
  //	return;
    QPainter paint( this );
    paint.setBrush( palette().color(QPalette::Foreground) );
    drawClock( &paint );
}

// If the clock is transparent, we use updateMask()
// instead of paintEvent()

void AnalogClock::updateMask()	// paint clock mask
{
    QBitmap bm( size() );
    bm.fill( Qt::color0 );			//transparent

    QPainter paint;
    //    paint.begin( &bm, this );
    paint.begin(&bm);
    paint.initFrom(this);
    paint.setBrush( Qt::color1 );		// use non-transparent color
    paint.setPen( Qt::color1 );

    drawClock( &paint );

    paint.end();
    setMask( bm );
}

//
// The clock is painted using a 1000x1000 square coordinate system, in
// the a centered square, as big as possible.  The painter's pen and
// brush colors are used.
//
void AnalogClock::drawClock( QPainter *paint )
{
    paint->save();
    
    paint->setWindow( -500,-500, 1000,1000 );

    QRect v = paint->viewport();
    int d = qMin( v.width(), v.height() );
    paint->setViewport( v.left() + (v.width()-d)/2,
			v.top() + (v.height()-d)/2, d, d );
    
    // time = QTime::currentTime();
     QPolygon pts;
    
    paint->setPen( QColor("#008080") );

    // draw hourse
    paint->save();
    paint->rotate( 30*(time.hour()%12-3) + time.minute()/2 );
    pts.setPoints( 4, -30,0,  0,-30, 300,0, 0,30 );
    paint->drawConvexPolygon( pts );
    paint->restore();

    // draw minutes
    paint->save();
    paint->rotate( (time.minute()-15)*6 );
    pts.setPoints( 4, -20,0, 0,-20, 350,0, 0,20 );
    paint->drawConvexPolygon( pts );
    paint->restore();

    paint->setPen( QColor("black") );
    
    // draw seconds
    paint->save();
    paint->rotate( (time.second() -15)* 6  );
    pts.setPoints( 4, -5,0, 0,-5, 400,0, 0,5 );
    paint->drawConvexPolygon( pts );
    paint->restore();


    int i=0;

    for ( i = 0; i < 60 ; i++ ) {
	paint->drawLine( 450,0, 460,0 );
	paint->rotate( 6 );
    }
 
    paint->setPen( QColor("#008080") );

    for ( i = 0; i <12; i++ ) {
	paint->drawLine( 420,0, 460,0 );
	paint->rotate( 30 );
    }
    

    paint->restore();
}


void AnalogClock::setAutoMask(bool b)
{
  /*
    if (b) 
	setBackgroundMode( Qt::PaletteForeground );
    else 
	setBackgroundMode( Qt::PaletteBackground );
  */
    //QWidget::setAutoMask(b);
    //QWidget::setAutoMask(b);
}
