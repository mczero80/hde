/****************************************************************************
 **
 **				vistamenu.h
 **			==========================
 **
 **  begin                : Mar 08 2007
 **  copyright            : (C) 2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  The Vista Menu style in hde.
 **
 ****************************************************************************/

#ifndef VISTAMENU_H
#define VISTAMENU_H


#include <startmenu.h>
#include <QLabel>

class userIcon : public QLabel
{
  Q_OBJECT

 public:
  userIcon( QWidget* parent = 0 );
  ~userIcon(){};
  void setUserPix(bool up){userPix = up;};

 protected:
  virtual void paintEvent( QPaintEvent * );
  bool userPix;
};


class vistaMenu : public startMenu
{
  Q_OBJECT

 public:
  vistaMenu( QWidget* parent = 0, Qt::WFlags fl = 0 );
  void readRecents();

 protected slots:
  virtual void languageChange();
  void selectItem(sMenuItem *);

 private:
  void initIt();
  virtual void resizeEvent ( QResizeEvent *);
  virtual void moveEvent ( QMoveEvent * ); 
  virtual void showEvent ( QShowEvent * );
  void paintBg();


  userIcon *usericon; 

  sMenuItem *internetBrowser;
  sMenuItem *emailClient;
  sMenuItem *recent1;
  sMenuItem *recent2;
  sMenuItem *recent3;
  sMenuItem *recent4;
  sMenuItem *recent5;
  sMenuItem *recent6;
  sMenuItem *recent7;
  sMenuItem *recent8;
  sMenuItem *recent9;
  sMenuItem *recent10;


  sMenuItem *userItem;
  sMenuItem *docItem;
  sMenuItem *picItem;
  sMenuItem *soundItem;
  sMenuItem *findItem;
  sMenuItem *recentItem;
  sMenuItem *mypcItem;
  sMenuItem *netItem;

  sMenuItem *controlItem;
  sMenuItem *runItem;

  QPixmap lightHBg;
  QPixmap darkHBg;
};


#endif
