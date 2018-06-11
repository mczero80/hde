/****************************************************************************
 **
 **				wborder.h
 **			=========================
 **
 **  begin                : 2001 based on qlwm
 **  copyright            : (C) 2001 - 2007 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **  License              : GPL
 **
 **  Creates the window borders
 **
 **  Special Thanks to Alexander Linden <alinden@gmx.de>
 **
 ****************************************************************************/


#ifndef WBORDER_H
#define WBORDER_H

// define a frame that emits mouse events
//#include <QtGui>
#include <QLabel>
#include <QWidget>
#include <QLayout>
#include <QStringList>

class wframe : public QLabel
{
  Q_OBJECT
	
 signals:
  void press(QMouseEvent *);
  void press(void);
  void release(QMouseEvent *);
  void mouse_move(QMouseEvent *);
  void left_press(QMouseEvent *);
  void left_press(void);
  void right_press(void);
  void left_release(QMouseEvent *);
  void left_release(void);
  void left_clicked(void);
  void right_release(void);
  void right_clicked(void);
  void mid_press(void);
  void mid_release(void);
  void mid_clicked(void);
  
 protected:
  virtual void mousePressEvent(QMouseEvent *);
  virtual void mouseReleaseEvent(QMouseEvent *);
  virtual void mouseMoveEvent(QMouseEvent *);
  virtual void resizeEvent(QResizeEvent *);
  virtual void paintEvent( QPaintEvent * );
  virtual void enterEvent ( QEvent * );
  virtual void leaveEvent ( QEvent * );
  bool activepal;

public:
  void setActivePal(bool a){ activepal = a;};
  wframe(QWidget *parent=0, QString name="");
  void set_text(QString, bool);
  void set_max(bool max){ maxed = max;};
  QString frameName;
  bool maxed;
  bool mousedown;
  bool mouseover;

};

// lower window border
class lborder : public QWidget
{
  QHBoxLayout *layout;

 public:
  wframe *leftframe;
  wframe *midframe;
  wframe *rightframe;
  
  lborder(QWidget *parent=0);
};

// upper window border
class uborder : public wframe
{
  QVBoxLayout *layout0;
  QHBoxLayout *layout;

 public:
  void setActivePal(bool);
  wframe *topleftframe;
  wframe *topframe;
  wframe *toprightframe;
  wframe *upperleftframe;
  wframe *upperrightframe;

  wframe *menuframe;
  wframe *midframe;
  wframe *helpframe;
  wframe *minframe;
  wframe *maxframe;
  wframe *minmaxframe;
  wframe *closeframe;
  
  //  uborder(bool showleft=TRUE, QWidget *parent=0);
  uborder(QWidget *parent=0, QStringList to = QStringList());
  void set_small(void);      // set to smaller frame
  void set_normal(void);     // set to normal frame
  void set_max(bool);     // set to normal frame
  QString glowBtn;

 private:
  bool hasTitle;
  QStringList titleOrder;
  bool maxed;
  bool hasMenu;
  bool hasMinBtn;
  bool hasMaxBtn;
  bool hasHelpBtn;
 
};

// Side Left window border
class slborder : public QWidget
{
  QVBoxLayout *layout;

 public:
  wframe *midframe;
  wframe *lowerframe;
  
  slborder( QWidget *parent=0);
  ~slborder(void);
};

// Side Right window border
class srborder : public QWidget
{
  QVBoxLayout *layout;

public:
  wframe *upperframe;
  wframe *midframe;
  wframe *lowerframe;
  
  srborder( QWidget *parent=0);
  ~srborder(void);
};

#endif
