/****************************************************************************
**
**	hclock.h
**
*****************************************************************************/

#ifndef HCLOCK_H
#define HCLOCK_H

#include <qwidget.h>
#include <qdatetime.h>
#include <qlayout.h> 
//#include <q3datetimeedit.h> 
//Added by qt3to4:
#include <QPaintEvent>
#include <QMouseEvent>
class QTimeEdit;


class AnalogClock : public QWidget		// analog clock widget
{
    Q_OBJECT
public:
    AnalogClock( QWidget *parent=0, const char *name=0, QTime tm=QTime::currentTime());
    void setAutoMask(bool b);

public slots:    
    void setTime( const QTime & t );
    
protected:
    void updateMask();
    void paintEvent( QPaintEvent *);
    void mousePressEvent( QMouseEvent *);
    void mouseMoveEvent( QMouseEvent *);
    
private slots:
    void drawClock( QPainter* );
//void	timeout();

private:
    QPoint clickPos;
    QTime	time;
};

class HClock : public QWidget		// analog clock widget
{
    Q_OBJECT
 public:
    HClock( QWidget *parent=0, const char *name=0, 
	    QTime tm=QTime::currentTime() );

 protected:
    AnalogClock *aclock;
    QTimeEdit *te;
    QTime	time;

public slots:    
    void setTime( const QTime & t );

private slots:
    void timeout();

};


#endif // HCLOCK_H
