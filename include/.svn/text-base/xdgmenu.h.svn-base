/****************************************************************************
 **
 **				xdgmenu.h
 **			=========================
 **
 **  begin                : Wed Mei 08 2007
 **  copyright            : (C) 2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  Reads and use the new "XDG" menu system used by both kde and gnome.
 **
 ****************************************************************************/

#ifndef XDGMENU_H
#define XDGMENU_H

#include <QMenu>
#include <QList>
class QTextStream;
class QFileInfo;

class menuMenu: public QMenu
{
  Q_OBJECT

 public:
  menuMenu(QString path="");
  void insertMenu( menuMenu *menu );
  void insertItm( QPixmap pix, QString name, QString exec,  QString category);
  menuMenu *checkMenu(QString);
  int checkSubMenus(QString);
  int checkCategory(QString);
  int checkItm(QString path);
  void setPath(QString path){menupath = path;};
  void setCategories(QStringList cat){categories = cat;};
  QString menu_path(void){return menupath;};
  void clearEmpty();

 public slots:
  void actionTriggered( QAction * );

 private:
  QString menupath;
  QStringList categories;
  QList<menuMenu *> menuList;
  QList<QAction *> actionList;
};


class xdgMenu
{
 public:
  xdgMenu(){};
  void readMenus(menuMenu*);

 private:
  menuMenu *readSubMenus(QTextStream &stream, QString parent);
  void readItems();
  void readItem( QFileInfo );
  QStringList getCategories(QTextStream &stream);
  menuMenu *baseMenu;
 
};

#endif
