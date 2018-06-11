/****************************************************************************
 **
 **					hfilewidget.h
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2007 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **
 **  A widget that has a file list and dirlist.
 **
 ****************************************************************************/

#ifndef HFILEWIDGET_H
#define HFILEWIDGET_H

#include <QWidget>
#include <QComboBox>
#include "hfilelist.h"

class QLabel;
class HInfoLabel;
class HDrivesCombo;

class HFileWidget : public QWidget 
{ 
    Q_OBJECT

 public:
   HFileWidget( QWidget* parent = 0);
   ~HFileWidget();
   void setViewMode( HFileList::ViewMode  );
   void showMyComputer(void){hflist->showMyComputer();};
   void showHome(void);
   void setDir( QString dirname ){ hflist->setDir(dirname); };
   void refresh(){ hflist->refresh(); };
   QString currentDir(void) const { return curDir;};
   QString currentFile(void) const{ return curFile;};
   QStringList selectedList(){ return hflist->selectedList(); };
   
 signals:
    void directoryChanged( const QString & );
    void fileExecuted( const QString & );
    void fileHighlighted( const QString & );
    void hasFocus( HFileWidget * );

 public slots:
    void listDirectoryChanged( const QString & );
    void listFileExecuted( const QString & );
    void listFileHighlighted( const QString & );
    void listFocusChanged( bool );
    void driveActivated( const QString& );


 private:
   void setDirLabelBackground( bool );
   HDrivesCombo *driveCombo;
   QLabel *dirLabel;
   HFileList *hflist;
   HInfoLabel *infoLabel;
   QString curDir;
   QString curFile;
};

class HInfoLabel : public QWidget 
{ 
    Q_OBJECT

 public:
   HInfoLabel( QWidget* parent = 0){};
   ~HInfoLabel(){};
   void setFilename(QString file){fileName = file; repaint();};
   
 protected:
   virtual void paintEvent( QPaintEvent *);

 private:
   QString fileName;
};

class HDrivesCombo : public QComboBox
{
    Q_OBJECT

 public:
   HDrivesCombo( QWidget* parent = 0);
   ~HDrivesCombo(){};
   void checkDrive( const QString& );
};

#endif
