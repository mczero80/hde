/**********************************************************************
 **
 **				toolbar.h
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **  Thanks to            : alinden@gmx.de
 **
 **  Draw the toolbar and place items on it
 **
 *********************************************************************/

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "pager.h"
#include "winlist.h"
#include "menu.h"
#include "procbar.h"
#include "apbar.h"

extern pager   *tb_pg;     // pager
extern winlist *tb_wl;     // winlist
extern menu    *tb_mn;     // menu
extern procbar *tb_pb;     // procbar
extern apbar   *tb_ap;     // apbox

class Toolbar : public QFrame
{
  QBoxLayout *layout;
  void addsep(void);              // add separator

 public:
  Toolbar(QWidget *parent=0);

 protected:
  virtual void enterEvent ( QEvent * );
  virtual void leaveEvent ( QEvent * );

 protected slots:
  void paintBg();
};
#endif
