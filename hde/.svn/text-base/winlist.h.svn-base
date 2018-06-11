/**********************************************************************
 **
 **				winlist.h
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2006 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **  Thanks to            : alinden@gmx.de
 **
 **  Creates the winlist button
 **
 *********************************************************************/


#ifndef WINLIST_H
#define WINLIST_H

#include "xwindow.h"

class winlist : public QPushButton
{
  Q_OBJECT
    
  QMenu *wmenu;
  QIcon winlisticn,tiledicn;
  void popup_list(void);    // popup window list
  bool isobscured(xwindow *, Window *, uint);
  bool isbottom(xwindow *, Window *, uint);
  
private slots:
  void highlight_pager(QAction *);

protected:
  virtual void mousePressEvent(QMouseEvent *);
  virtual void mouseReleaseEvent(QMouseEvent *);
  virtual void paintEvent( QPaintEvent * );

public:
  void start_popup(void);
  void hidden_win(void);
  void set_pixmap(void);
  winlist(QWidget *parent);
};
#endif
