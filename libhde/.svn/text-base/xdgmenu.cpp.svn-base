/****************************************************************************
 **
 **				xdgmenu.cpp
 **			=========================
 **
 **  begin                : Wed Mei 08 2007
 **  copyright            : (C) 2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  Reads and use the new "XDG" menu system used by both kde and gnome.
 **
 ****************************************************************************/


#include <QTextStream>
#include <QMenu>
#include <QFile>
#include <QFileInfo>
#include <QDir>

#include <defaults.h>
#include <libhde.h>
#include "xdgmenu.h"


QString xdgdir = "/etc/xdg/menus/hde";
QString desktopDir = "/usr/share/desktop-directories/";
QString appdir = "/usr/share/applications/";


/************************************************************************
 * createPix tries to get the image for the item or menu.
 * if the image in the path exists return it.
 * otherwize try to find default program icon or default group icon.
 ***********************************************************************/
QPixmap createPix(QString path, QString type =0, int h = 22){
    QPixmap pix0(path);

    if(! pix0.isNull()){
      QPixmap pix = pix0.scaled(h, h);
      return (pix);
    }
    
    if (type == "prg"){
      pix0 = QPixmap(get_ifile("images/prg.xpm", "mini"));
      if(! pix0.isNull()){
	QPixmap pix = pix0.scaled(h, h);
	return (pix);
      }else
	return (QPixmap( get_ifile("images/prg.xpm", "mini")));
    }

    if(type == "grp"){
      pix0 = QPixmap(get_ifile("images/grp.xpm", "mini"));
      if(! pix0.isNull()){
	QPixmap pix = pix0.scaled(h, h);
	return (pix);
      }else
	return (QPixmap( get_ifile("images/grp.xpm", "mini")));
    }

    return (pix0);
}



/**************************************************************************
 *
 * Return a List of categories by reading the <Include> tag.
 * We are ignoring the <Or> and the <Not> tag at the moment.
 *
 *************************************************************************/
QStringList xdgMenu::getCategories(QTextStream &stream)
{
  QStringList cat;

  QString line = stream.readLine().simplified();
  while( (line.right(line.length()-11) != "</Include>") &&  !stream.atEnd())
  {
    if(line == "<Not>")
    {
      line = stream.readLine().simplified();
      while( (line.right(line.length()-7) != "</Not>") &&  !stream.atEnd())
      {
	line = stream.readLine().simplified();
      }
    }
    else if(line == "<And>")
    {
      line = stream.readLine().simplified();
      while( (line.right(line.length()-7) != "</And>") &&  !stream.atEnd())
      {
	if( (line.left(10) == "<Category>") &&
	    ( line.right(11) == "</Category>" ) )
	{
	  line = line.mid( 10, line.length() - 21 );
	  cat << line;
	}
	line = stream.readLine().simplified();
      }
    }
    line = stream.readLine().simplified();
  }

  return cat;
}

menuMenu *xdgMenu::readSubMenus(QTextStream &stream, QString parent)
{
  menuMenu *currentMenu = new menuMenu;

  QString menuPath;
  QString menuName;
  QStringList categories;
  while (!stream.atEnd()) {
    QString line = stream.readLine().simplified();
    if( (line.left(6) == "<Name>") && (line.right(7) == "</Name>") )
    {
      /****************************************
       *
       * Setting Menu Name
       *
       ***************************************/
      menuPath = line.mid( 6, line.length() - 13 );
      currentMenu->setTitle(menuPath);
    }
    else if(line == "<Name>")
    {
      while(line.right(7) != "</Name>")
      {
	QString newLine = stream.readLine().simplified();
	line = line + newLine;
      }
      menuPath = line.mid( 6, line.length() - 13 );
      currentMenu->setTitle(menuPath);
    }
    else if((line.left(11) == "<Directory>") && 
	    (line.right(12) == "</Directory>"))
    {
      /****************************************
       *
       * Read the name of this menu.
       *
       ***************************************/
      QString dirPath = line.mid( 11, line.length() - 23 );;

      hdeItem ditem = defaults::readItem(desktopDir+dirPath);
      menuName = ditem.name;
      if(menuName.isEmpty() || menuName.isNull())
	currentMenu->setTitle(menuPath);
      else
	currentMenu->setTitle(menuName);
      
      QString icon = ditem.icon;
      if(!icon.left(icon.length() - 3).endsWith('.'))
	icon.append(".png");
      icon = getIconFile(icon, "mini");
      currentMenu->setIcon(createPix(icon, "grp", 22));
      
    }
    else if(line == "<Directory>")
    {
      /****************************************
       *
       * Read the name of this menu.
       *
       ***************************************/
      while(line.right(12) != "</Directory>")
      {
	QString newLine = stream.readLine().simplified();
	line = line + newLine;
      }
      QString dirPath = line.mid( 11, line.length() - 23 );

      hdeItem ditem = defaults::readItem(desktopDir+dirPath);
      menuName = ditem.name;
      if(menuName.isEmpty() || menuName.isNull())
	currentMenu->setTitle(menuPath);
      else
	currentMenu->setTitle(menuName);
      
      QString icon = ditem.icon;
      icon = getIconFile(icon, "mini");
      currentMenu->setIcon(QIcon(icon));
      
    }
    else if(line == "<Include>")
    {
      /****************************************
       *
       * Read Categories of this menu.
       *
       ***************************************/
      categories = getCategories(stream);
      currentMenu->setCategories(categories);
    }
    else if(line == "<Menu>")
    {
      /****************************************
       *
       * Add a new SubMenu to it.
       *
       ***************************************/
      QString newParent = parent + "/" + menuPath;
      if((parent == "") &&  menuPath == "Applications")
	newParent = "/applnk";
      currentMenu->setPath(newParent);
      currentMenu->insertMenu(readSubMenus(stream, newParent));
    }
    else if(line == "</Menu>")
    {
      /****************************************
       *
       * We have finished reading our menu.
       * We can now return it to be added.
       *
       ***************************************/
      QString newParent = parent + "/" + menuPath;
      if((parent == "") &&  menuPath == "Applications")
	newParent = "/applnk";
      currentMenu->setPath(newParent);
      return currentMenu;
    }
  }  
  return currentMenu;
}

/**************************************************************************
 *
 * We Read the file applications.menu in xdg directory as folow:
 * 1- Ignore root application menu (since we include it submenus directly).
 * 2- Search recursively every submenu of the root menu.
 * 3- Search all the Applications and put the in there menu's.
 *
 *************************************************************************/

void xdgMenu::readMenus( menuMenu *mnu)
{
  baseMenu = mnu;

  QString filename = xdgdir + "/applications.menu";
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
  
  bool root = true;
  QTextStream stream(&file);
  while (!stream.atEnd()) {
    QString line = stream.readLine().simplified();
    if(line == "<Menu>")
    {
      if(root)
	root = false;
      else
	baseMenu->insertMenu(readSubMenus(stream, ""));
    }
  }

  readItems();
}

/********************************************************************
 *
 * Read the menu item.
 *
 *******************************************************************/
void xdgMenu::readItem( QFileInfo fileInfo )
{
  QString path = fileInfo.filePath();
  if(fileInfo.isSymLink())
    path = fileInfo.symLinkTarget();


  hdeItem ditem = defaults::readItem(path);
  if(!ditem.error.isNull())
    return;
  QString itemName = ditem.name;
  if(itemName.isEmpty() || itemName.isNull())
    itemName = fileInfo.fileName();

  QString icon = ditem.icon;
  icon = getIconFile(icon, "mini");
  QString exec = path;//ditem.exec;
  QString cat = ditem.categories;

  baseMenu->insertItm( QPixmap(icon), itemName, exec, cat);
}


/********************************************************************
 *
 * We check appdir and appdir/kde for menu items, and add each of 
 * them to the menu where it belongs according to it's category.
 *
 *******************************************************************/
void xdgMenu::readItems()
{
  QDir dir(appdir);
  dir.setFilter( QDir::Files | QDir::Hidden );

  QFileInfoList list = dir.entryInfoList();
  
  for (int i = 0; i < list.size(); ++i) {
    QFileInfo fileInfo = list.at(i);
    if( fileInfo.suffix() == "desktop")
    {
      readItem( fileInfo );
    }
  }
  
  dir = QDir(appdir+"/kde");
  dir.setFilter( QDir::Files | QDir::Hidden );

  list = dir.entryInfoList();
  for (int i = 0; i < list.size(); ++i) {
    QFileInfo fileInfo = list.at(i);
    if( fileInfo.suffix() == "desktop")
    {
      readItem( fileInfo );
    }
  }


  dir = QDir(appdir+"/hde");
  dir.setFilter( QDir::Files | QDir::Hidden );

  list = dir.entryInfoList();
  for (int i = 0; i < list.size(); ++i) {
    QFileInfo fileInfo = list.at(i);
    if( fileInfo.suffix() == "desktop")
    {
      readItem( fileInfo );
    }
  }
 
  baseMenu->clearEmpty();
}


/****************************************************************
 *
 * menuMenu is a QMenu with some extras allowing us to categories
 * it.
 *
 ***************************************************************/

menuMenu::menuMenu( QString path )
  : QMenu(0), menupath(path)
{
}


void menuMenu::insertMenu( menuMenu *menu )
{
  addMenu((QMenu*)menu);
  menuList << menu;
}

void menuMenu::insertItm( QPixmap pix, QString name, QString exec,
			 QString categories)
{
  QAction *action = checkMenu(categories)->addAction(pix, name);
  action->setData(exec);
  actionList << action;
}

/***************************************************************
 *
 * Check where we should put our item by searching every menu 
 * and it's sub menus accourding to it's categories.
 *
 **************************************************************/
menuMenu *menuMenu::checkMenu(QString categories)
{
  menuMenu *retMenu = this;
  int numMatch = 0;
  for (int i = 0; i < menuList.size(); ++i) {
    int n = menuList.at(i)->checkCategory(categories);
    if(( n > 0) && ( n > numMatch ) )
    {
      retMenu = menuList.at(i);
      numMatch = n;
    }
    n = menuList.at(i)->checkSubMenus(categories);
    if(( n > 0) && ( n > numMatch ))
    {
      retMenu = menuList.at(i)->checkMenu(categories);
      numMatch = n;
    }

   }

  return retMenu;
}

int menuMenu::checkSubMenus(QString categories)
{
  int numMatch = 0;
  for (int i = 0; i < menuList.size(); ++i) {
    int n = menuList.at(i)->checkCategory(categories);
    if(( n > 0) && ( n > numMatch ) )
    {
      numMatch = n;
    }
    n = menuList.at(i)->checkSubMenus(categories);
    if(( n > 0) && ( n > numMatch ))
    {
      numMatch = n;
    }

  }
  return numMatch;
}

int menuMenu::checkCategory(QString cat)
{
  int numMatch = 0;
  QString ccat;
  foreach(ccat , categories) {
    if(cat.contains(ccat))
    {
      numMatch = numMatch + 1;
    }
  }

  return numMatch;
}


int menuMenu::checkItm(QString)
{
  return 0;
}

/*********************************************************************
 *
 * Clear empty menu's to save space on our screen (NOT YET AVILABLE)
 *
 ********************************************************************/
void menuMenu::clearEmpty()
{
  for (int i = 0; i < menuList.size(); ++i) {
      menuList.at(i)->clearEmpty();
    if(menuList.at(i)->isEmpty())
    {
      removeAction(menuList.at(i)->menuAction());
      menuList.removeAt(i);
    }else{
      menuList.at(i)->clearEmpty();
      if(menuList.at(i)->isEmpty())
      {
	removeAction(menuList.at(i)->menuAction());
	menuList.removeAt(i);
      }
    }
  } 
}

void menuMenu::actionTriggered( QAction *action )
{
  QString exec = action->data().toString();
  execCmd( exec );
}

