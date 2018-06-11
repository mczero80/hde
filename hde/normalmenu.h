/****************************************************************************
 **
 **				normalmenu.h
 **			==========================
 **
 **  begin                : Jan 01 2005
 **  copyright            : (C) 2005 -2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  The start Menu widget in hde.
 **
 ****************************************************************************/


#ifndef NORMALMENU_H
#define NORMALMENU_H

#include <smenuitem.h>
#include <startmenu.h>
#include <qvariant.h>
#include <qpixmap.h>
#include <qframe.h>
//Added by qt3to4:
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QPaintEvent>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;

/*******************************************************************
 *
 * BgWidget, is a widget with a Background Color.
 *
 ******************************************************************/
class bgWidget : public QLabel
{
    Q_OBJECT

 public:
  bgWidget( QWidget*  = 0 ){drawIt();};
  ~bgWidget(){};
  void setBgPixmap(QPixmap pix){ bgPixmap = pix; drawIt();};
  void setBgColor(QColor clr){ bgColor = clr; drawIt();};
  void drawIt();

 protected:
  virtual void resizeEvent ( QResizeEvent *){ drawIt();};

 private:
  QPixmap bgPixmap;
  QColor bgColor;
};


class sideLabel : public bgWidget
{
    Q_OBJECT

 public:
  sideLabel( QWidget*  = 0 ){changeIt();};
  void setColor1(QColor clr){ color1 = clr; changeIt();};
  void setColor2(QColor clr){ color2 = clr; changeIt();};
  void setText(QString txt){ capText = txt; changeIt();};
  void changeIt();

 protected:
  virtual void resizeEvent ( QResizeEvent *){ changeIt();};


 private:
  QPixmap bgPixmap;
  QColor color1;
  QColor color2;
  QString capText;
};


/****************************************************************************
 *
 * Startmenu, The main frame of the start menu.
 *
 ***************************************************************************/

class normalMenu : public startMenu
{
  Q_OBJECT

 public:
  normalMenu( QWidget* parent = 0, Qt::WFlags fl = 0 );
  virtual void readRecents();
  
   
 protected slots:
  virtual void languageChange();
  
 public slots:
  void closeMenu(int){close();};
  
 private:
  void initIt();
  
 protected: 
  QHBoxLayout *mainLayout; 
  sMenuItem *docItem;
  sMenuItem *runItem;
  sMenuItem *settingItem;
  sMenuItem *searchItem;
  sMenuItem *helpItem;
};

#endif
