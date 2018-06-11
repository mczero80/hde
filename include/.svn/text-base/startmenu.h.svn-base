/****************************************************************************
 **
 **				startmenu.h
 **			==========================
 **
 **  begin                : Jan 01 2005
 **  copyright            : (C) 2005 -2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  The start Menu widget in hde.
 **
 ****************************************************************************/


#ifndef STARTMENU_H
#define STARTMENU_H

#include "smenuitem.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;

/****************************************************************************
 *
 * Startmenu, The main frame of the start menu.
 *
 ***************************************************************************/
class sMenuItem;

class startMenu : public QFrame
{
  Q_OBJECT

 public:
  startMenu( QWidget*parent = 0, Qt::WFlags wf = 0 );
  void setPgramsMenu(QMenu *);
  virtual void readRecents();
  
  sMenuItem* exitItem;
  sMenuItem* killItem;
  sMenuItem* programs;

  
 public slots:
  void closeMenu(int){close();};

 protected: 
  QMenu *progsPop; 
  
};




#endif
