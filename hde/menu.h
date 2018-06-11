/**********************************************************************
 **
 **				 menu.h
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2006 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **  Thanks to            : alinden@gmx.de
 **
 **  Creates menu button and the XKill function
 **
 *********************************************************************/

#ifndef MENU_H
#define MENU_H

#include <QPushButton>
#include <QDateTime>
#include <QFile>
#include <xdgmenu.h>


class menu : public QPushButton
{
  Q_OBJECT
	
  menuMenu *basemenu;
  QPixmap mainpix;
  QPixmap maintxt;
  bool killop;                  // window kill operation active
  QAction *act_quit;
  QAction *act_kill;
  QAction *act_rest;
  void run_cmd(QByteArray &);
  QDateTime lmtime;             // last file modification time
  static uchar kcursor_bits[];  // cursor bitmap
  static uchar kcursor_mask[];  // cursor bitmap
  
 private slots:	
  void winkill(void);
  void winkill_all(void);

protected:
  virtual void mousePressEvent(QMouseEvent *);
  virtual void paintEvent( QPaintEvent * );

public:
  menu(QWidget *parent);
  void start_popup(void);
  void readmenu(void);
};
#endif
