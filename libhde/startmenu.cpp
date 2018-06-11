/****************************************************************************
 **
 **				startmenu.cpp
 **			==========================
 **
 **  begin                : Jan 01 2005
 **  copyright            : (C) 2005 -2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  The start Menu widget in hde.
 **
 ****************************************************************************/



#include "smenuitem.h"
#include "startmenu.h"
#include <libhde.h>

#include <QtGui>

startMenu::startMenu( QWidget* parent, Qt::WFlags  wf )
  : QFrame(parent, wf)
{
}

/***********************************************************************
 *
 * Sets the programs menu and correct connections
 *
 **********************************************************************/
void startMenu::setPgramsMenu(QMenu *pp){
  progsPop = pp;
  connect(progsPop, SIGNAL(activated(int)), this, SLOT(closeMenu(int)) );
  programs->setPopup(progsPop);
}

/***********************************************************************
 *
 * Read recent used programs.
 *
 **********************************************************************/
void startMenu::readRecents()
{
}
