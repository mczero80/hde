/****************************************************************************
 **
 **				hdestyle.h
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2006 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **
 **  The primary style for libhde.
 **
 ****************************************************************************/


#ifndef HDESTYLE_H
#define HDESTYLE_H

#include <QtGui/qcommonstyle.h>
#include <QPixmap>
#include <QEvent>

QT_MODULE(Gui)


class hdeStyle : public QCommonStyle
{
  Q_OBJECT
 public:
  hdeStyle();
  ~hdeStyle();

  void polish(QWidget* widget);
  void polish ( QApplication * app ) ;
  void polish ( QPalette & pal ) ;
  void unpolish(QWidget* widget) ;
  void unpolish ( QApplication * app );

  void drawComplexControl( ComplexControl control, 
			   const QStyleOptionComplex * option, 
			   QPainter * painter,
			   const QWidget * widget = 0 ) const;
  void drawControl ( ControlElement element, const QStyleOption * option, 
		     QPainter * painter, const QWidget * widget = 0 ) const;
  void drawItemPixmap ( QPainter * painter, const QRect & rect, int alignment, 
			const QPixmap & pixmap ) const; 
  void drawItemText ( QPainter * painter, const QRect & rect, int alignment,
		      const QPalette & pal, bool enabled, const QString & text,
		      QPalette::ColorRole textRole = QPalette::NoRole ) const ;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
		       QPainter *painter, const QWidget *widget) const;

    QSize sizeFromContents ( ContentsType type, const QStyleOption * option,
			     const QSize & contentsSize, 
			     const QWidget * widget = 0 ) const; 
    QIcon standardIcon ( StandardPixmap standardIcon, 
			 const QStyleOption * option = 0, 
			 const QWidget * widget = 0 ) const; 
    QPalette standardPalette () const; 
    QPixmap standardPixmap ( StandardPixmap standardPixmap, 
			     const QStyleOption * option = 0, 
			     const QWidget * widget = 0 ) const;
    int styleHint ( StyleHint hint, const QStyleOption * option = 0,
		    const QWidget * widget = 0, 
		    QStyleHintReturn * returnData = 0 ) const;
    int pixelMetric ( PixelMetric metric, const QStyleOption * option = 0,
		      const QWidget * widget = 0 ) const; 
    QRect subControlRect ( ComplexControl control,
			   const QStyleOptionComplex * option, 
			   SubControl subControl, 
			   const QWidget * widget = 0 ) const; 
    QRect subElementRect ( SubElement element, const QStyleOption * option,
			   const QWidget * widget = 0 ) const; 
    SubControl hitTestComplexControl(ComplexControl control, const QStyleOptionComplex *option,
				     const QPoint &pos, const QWidget *widget = 0) const;


 protected:
    bool hdestyle;
//    bool eventFilter( QObject *object, QEvent *event );
    QWidget *hoverWidget;

 private:	
    hdeStyle( const hdeStyle & );
    hdeStyle& operator=( const hdeStyle & );
    QStyle *winstyle;
};




#endif // HDESTYLE_H 
