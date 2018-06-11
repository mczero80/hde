/****************************************************************************
 **
 **				desktp.cpp
 **			=========================
 **
 **  begin                : 2001 based on qlwm
 **  copyright            : (C) 2001 - 2007 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **  License              : GPL
 **
 **  Our Desktop Class.
 **
 ****************************************************************************/
#ifndef DESKTP_H
#define DESKTP_H

#include <QListWidget>

class desktopItem : public QListWidgetItem
{
 public:
    desktopItem( QListWidget *parent ) :
        QListWidgetItem( parent ) {
	  //	  setDragEnabled ( true );
	  //setDropEnabled(true);
	}
	
      //virtual bool acceptDrop( const QMimeSource *mime ) const;
    void setPath(QString p){ path = p; };
    QString getPath(){ return path; };
    void setFilename(QString f){ filename = f; };
    QString getFilename(){ return filename; };

 protected:
    //virtual void dropped( QDropEvent *e, const QValueList<QIconDragItem> & );
    QString path;
    QString filename;
};

class desktp : public QListWidget //, public QDesktopWidget
{

  Q_OBJECT
 protected:
  virtual void mouseReleaseEvent(QMouseEvent *);
  virtual void keyPressEvent( QKeyEvent * event );
  void setBackground(void);
  void createIcon(QString path, QString fname);
  void drawBG();
  QImage rootBG;

 protected slots:
  //void slotNewItem( QDropEvent *evt, const QValueList<QIconDragItem>& list );
  void refreshDesktop(void);
  void refreshIV(void);

public slots:
  void iconClicked( QListWidgetItem* );
  void iconDblClicked( QListWidgetItem* );
  void iconReturnPressed( QListWidgetItem* );
  void rightClicked( QListWidgetItem*, const QPoint& );
  void prop( void );
  void openItem();
  void newItem( void );
  void deleteItem();
  void renameItem();
  void itemProp( void );

 public:
  desktp(QWidget *parent=0);
  void init();
  QMenu *rightmnu;
  QImage desktopBG;
};
#endif
