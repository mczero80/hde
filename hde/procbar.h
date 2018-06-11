/**********************************************************************
 **
 **				procbar.h
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **  Thanks to            : alinden@gmx.de
 **
 **  Creates the buttons for iconified windows
 **
 *********************************************************************/

#ifndef PROCBAR_H
#define PROCBAR_H

#include "defs.h"
#include "xwindow.h"

/*********************************************************************
 *
 * Tool Button, We need it because of the custom drawing.
 *
 *********************************************************************/
class tbutton : public QPushButton
{
  Q_OBJECT

 public:
  tbutton(QWidget *parent=0);
  ~tbutton();
  void hideLabel();
  void setScreenPixmap( QPixmap pix);

 public slots:
  void showTooltip();

 protected:
  void paintEvent( QPaintEvent * );
  virtual void enterEvent ( QEvent * );
  virtual void leaveEvent ( QEvent * );
  void drawScreenLabel();

  QTimer *tooltipTimer;
  QLabel *screenShotLabel;
  QPixmap screenPixmap;
};

class procbar : public QWidget
{
  int bwidth;                                       // button width  
  typedef struct 
  {
    xwindow *win;
    QPixmap *pixmap;                                // the buttons image
    QString text;                                   // the text of the button
    tbutton *button;                                // button
  } WINLIST;
  QList <WINLIST*> wlist;                           // list of visible buttons

  void draw_button(WINLIST *);                      // draw winlist button
  void draw_buttons(void);                          // draw buttons on bar

protected:
  virtual void resizeEvent(QResizeEvent *);

public:
  procbar(QWidget *parent=NULL);
  void add(xwindow *win);                           // add button
  void set_on(xwindow *win, bool onstat);           // set button to on state
  void upDown(xwindow *win, bool onstat);           // set button to on state
  void remove(xwindow *win);                        // remove from bar
  void remove_all(void);                            // remove all buttons
  void change_palette(const QPalette &, xwindow *); // change button palette
  void change_text(QString *icname, xwindow *win);  // change icon text
  void setScreenPixmap(xwindow *win, QPixmap pix);
};
#endif
