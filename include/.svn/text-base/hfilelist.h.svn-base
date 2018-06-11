/****************************************************************************
 **
 **					hfilelist.h
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2007 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **
 **  A widget that has a file list and dirlist.
 **
 ****************************************************************************/

#ifndef HFILELIST_H
#define HFILELIST_H

#include <QTableWidget>
#include <QDir>
#include "mycomputer.h"

#include <iostream>
using std:: cout; using std::endl;using std::cerr;


class HFileListItem;

/*****************************************************************************
 *
 * Class HFileList
 *
 *****************************************************************************/

class HFileList : public QTableWidget 
{ 
    Q_OBJECT

 public:
    enum ViewMode { Tiles, Icons, List, Detailed };
    HFileList( const QString &dir = NULL, QWidget* parent = 0);
    ~HFileList();
    void setDir( QString dirname ){readDir( QDir(dirname)); };
    void showMyComputer(void);
    void refresh();
    QStringList selectedList();
    
 signals:
    void directoryChanged( const QString & );
    void fileHighlighted( const QString & );
    void fileExecuted( const QString & );
    void focusChanged( bool );

 public slots:
    void clearAll();
    void getFileIcon();
    void currentFileChanged( QTableWidgetItem *, QTableWidgetItem *);
    void fileItemActivated( QTableWidgetItem * );
    void setViewMode( ViewMode );

 protected:
    int getIconsPerColumn(ViewMode mode);
    int getIconsPerRow(ViewMode mode);
    virtual void resizeEvent( QResizeEvent * );
    virtual void keyPressEvent ( QKeyEvent * ); 
    virtual void focusInEvent ( QFocusEvent * ); 
    virtual void focusOutEvent ( QFocusEvent * );
    void readDir( const QDir &dir );
    QString viewDir;
    ViewMode vm;
    bool extraRow;
    bool extraCol;
    int longestItem;
    int longestWarpedItem;
    QList<HFileListItem*> itemsList;
    
    // QSize can represent cordenates ;)
    QSize latsteCordenates;
};


/*****************************************************************************
 *
 * Class HFileListItem
 *
 *****************************************************************************/


class HFileListItem : public QTableWidgetItem
{
    friend class HFileList;

 public:
    HFileListItem( QString path, QString = "File", QIcon ico = QIcon());
    HFileListItem( const HFileListItem& );
    virtual ~HFileListItem(){};

    QString fileType() const;
    QString path() const { return itemPath; };
    QString filename() const { return itemFileName; };
    QFileInfo *fileInfo() const { return itemFileInfo;};

    
 protected:
    QString itemFileName;
    QFileInfo *itemFileInfo;
    QString itemPath;
    bool checkSetText;

};

#endif
