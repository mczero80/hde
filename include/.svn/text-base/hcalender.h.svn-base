/****************************************************************************
**
**	hcalender.h
**
****************************************************************************/
#ifndef HCALENDER_H
#define HCALENDER_H

#include <qvariant.h>
#include <qwidget.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qstringlist.h> 
//#include <qdatetm.h>
#include <QDate>
#include <qpainter.h>
#include <QTableWidget> 
//#include "defs.h"

#include <qhijri.h> 
//Added by qt3to4:
#include <QVBoxLayout>
#include <QHBoxLayout>


class calFrame : public QTableWidget
{ 
    Q_OBJECT
public:
    calFrame( QWidget* parent = 0, const char* name = 0, 
	      QDate date=QDate::currentDate(), bool hijri = 0 );
    ~calFrame();

    void setDate(QDate date);
    void refresh();
    void paintCell( QPainter * p, int row, int col, const QRect & cr,
			    bool selected );

    void setHijri(bool h){isHijri=h;};
    virtual void paintFocus( QPainter * p, const QRect & cr );

protected:
    QDate dt;
    Qhijri hd;
    //    virtual void drawContents ( QPainter * );
    bool isHijri;
};

class HCalender : public QWidget
{ 
    Q_OBJECT

 public:
    HCalender( QWidget* parent = 0, const char* name = 0, bool hijri = 0 );

    bool showLines;
    QStringList monthNames;
    QComboBox* monthCombo;
    QSpinBox* yearSpin;
    calFrame* Cal;

    void reset(void);
    void setHijri(bool h){isHijri=h; Cal->setHijri(h);Cal->refresh();reset();};

 public slots:
    void changed();
    void calChanged( int, int, int, int );

 signals:
    void dateChanged(QDate);
 
 protected:
    QVBoxLayout* cLayout;
    QHBoxLayout* dateLayout;
    QDateTime dt;
    Qhijri hd;
    bool isHijri;

};

#endif // HCALENDER_H
