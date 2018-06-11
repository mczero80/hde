/****************************************************************************
 **
 **				apbar.h
 **			=========================
 **
 **  begin                : 2001 based on qlwm
 **  copyright            : (C) 2001 - 2007 by Haydar Alkaduhimi 
 **  email                : haydar@haydarnet.nl
 **  License              : GPL
 **
 **  Manages the applets on the right side of the toolbar
 **
 **  Special Thanks to Alexander Linden <alinden@gmx.de>
 **
 ****************************************************************************/

#ifndef APBAR_H
#define APBAR_H


class apbar : public QWidget
{
  typedef struct
  {
    Window w;
    QString name;
    int width;
    int number;
  } WINDOW;
  QList <WINDOW*> ap;  // installed clients
	
 protected:
  virtual void paletteChange(const QPalette &);
  virtual void resizeEvent(QResizeEvent *);
  void paintBG();
  
 public:
  apbar(QWidget *parent=0);
  void place_clients(void);          // place clients on toolbar
  void release_all(void);            // reparent back to root window
  bool add(Window, int, QString &);  // add client
  bool client_exists(Window);        // client on list
  bool remove(Window);               // remove client
  void remove(void);                 // remove old clients after configure
};
#endif
