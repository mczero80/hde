/****************************************************************************
 **
 **				smenuitem.h
 **			=========================
 **
 **  begin                : Jan 01 2005
 **  copyright            : (C) 2005 -2006 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  Qpopup menu items look alike for start menu.
 **
 ****************************************************************************/

#ifndef SMENUITEM_H
#define SMENUITEM_H

#include <qframe.h>
#include <qpixmap.h>
#include <qmenu.h>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QEvent>

class sMenuItem : public QWidget
{
  Q_OBJECT
 public:
  sMenuItem( QWidget *parent=0 );
  void setPixmap(QPixmap pic);
  void setBGPixmap(QPixmap pic){bgpix = pic;}; // Background Pixmap
  void setHBGPixmap(QPixmap pic){hbgpix=pic;}; // Highlighted Background Pixmap
  void setText(QString st){ str = st;};
  QPixmap pixmap(){ return pix;};
  inline void setPopup(QMenu *pop){ popup = pop; haspopup = true;};
  ~sMenuItem(){};
  bool connectItem ( const QObject * receiver, const char * member );
  bool disconnectItem ( const QObject * receiver, const char * member );
  //  void drawIt(void);
  void setCommand(QString com);
  void setPixSize(int pw, int ph ){ pixWidth=pw; pixHeight=ph;repaint();};
  void setDrawPixmap(bool dp){drawPixmap = dp;};
  void setFont(QFont font){ mfont = font;};

 signals:
  void clicked(void);
  void highlighted(sMenuItem *);

  public slots:
  void pop(void);
  void execCommand(void);
  
 private:
  bool insidePainting;
  QPixmap pix;
  QPixmap orig_pic;
  QPixmap bgpix;
  QPixmap hbgpix;
  
  QString str;
  QString command;
  QMenu *popup;
  bool haspopup;
  bool drawPixmap;
  int pixWidth;
  int pixHeight;
  QFont mfont;

 protected:
  virtual void paintEvent( QPaintEvent * );
  virtual void mouseMoveEvent ( QMouseEvent * ){ repaint(); };
  virtual void enterEvent ( QEvent * event );
  virtual void leaveEvent ( QEvent * ){ repaint(); };
  virtual void mouseReleaseEvent( QMouseEvent * e );
  virtual void resizeEvent ( QResizeEvent * ){ repaint(); };

};

#endif // SMENUITEM_H
