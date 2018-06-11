/****************************************************************************
 **
 **				xpmenu.h
 **			==========================
 **
 **  begin                : Mar 04 2007
 **  copyright            : (C) 2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  The XP Menu style in hde.
 **
 ****************************************************************************/

#ifndef XPMENU_H
#define XPMENU_H


#include <startmenu.h>

/*******************************************************************
 *
 * Top widget, where your name and photo appears.
 *
 ******************************************************************/
class topWidget : public QWidget
{
    Q_OBJECT

 public:
  topWidget( QWidget* parent = 0 );
  ~topWidget(){};
  void setPixmap(QPixmap pix){ pixmap = pix; repaint();/*drawIt();*/};
  void setText(QString txt){text = txt; repaint();/*drawIt();*/};
  //  void drawIt();

 protected:
  //virtual void resizeEvent ( QResizeEvent *){ drawIt();};
  //virtual void showEvent ( QShowEvent *){ drawIt();};
  virtual void paintEvent( QPaintEvent * );

 private:
  QPixmap pixmap;
  QString text;
};


class xpMenu : public startMenu
{
  Q_OBJECT

 public:
  xpMenu( QWidget* parent = 0, Qt::WFlags fl = 0 );
  void readRecents();
  

  
 protected slots:
  virtual void languageChange();
  
 public slots:
  void closeMenu(int){close();};

 private:
  void initIt();
  sMenuItem *internetBrowser;
  sMenuItem *emailClient;

  sMenuItem *recent1;
  sMenuItem *recent2;
  sMenuItem *recent3;
  sMenuItem *recent4;
  sMenuItem *recent5;
  sMenuItem *recent6;

  sMenuItem *docItem;
  sMenuItem *recentItem;
  sMenuItem *picItem;
  sMenuItem *soundItem;
  sMenuItem *controlItem;
  sMenuItem *runItem;

 protected:
  QVBoxLayout *mainLayout; 
  topWidget *personalFrame;
  virtual void resizeEvent ( QResizeEvent *);
  virtual void moveEvent ( QMoveEvent * event ); 
  void paintBg();
};

#endif
