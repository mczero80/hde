
#ifndef HXKBWIDGET_H
#define HXKBWIDGET_H

#include <qlabel.h>
#include <qlabel.h>
#include <qvariant.h>
#include <qwidget.h>

class QMenu;

class hXkbWidget : public QLabel
{
    Q_OBJECT

 public:
  hXkbWidget( QWidget* parent = 0, const char* name = 0 );
  ~hXkbWidget();
  void setNextXkb();

 protected:
  virtual void mousePressEvent( QMouseEvent * e );
  virtual void mouseReleaseEvent( QMouseEvent * e );

 protected slots:
  virtual void languageChange();
  void changeXkb(QAction*);

 private:
  QMenu *menu;

};

#endif // HXKBWIDGET_H
