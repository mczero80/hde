/****************************************************************************
 **
 **			      mycomputer.h
 **			=========================
 **
 **  begin                : Wed Jun 21 2003
 **  copyright            : (C) 2003-2006 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **
 **  A widget that has a file list and dirlist.
 **
 ****************************************************************************/


/*****************************************************************************
 *
 * Class HDrive
 *
 *****************************************************************************/
    
#include <qstring.h>
#include <qicon.h>
#include <QList>


#ifndef HDRIVE_H 
#define HDRIVE_H 

class HDrive
{
 public:
  HDrive(QString path, QString type="Hdd", QIcon icn=QIcon());
    
    void setType(QString type){ driveType = type; };
    void setIcon(QIcon icn){ driveIcon = icn; };
    QString path(){ return drivePath;};
    QString type(){ return driveType;};
    QIcon icon(){ return driveIcon;};
    
 private:
    QString driveType;
    QString drivePath;
    QIcon driveIcon;
};
#endif

/*****************************************************************************
 *
 * Class MyComputer
 *
 *****************************************************************************/

#ifndef MYCOMPUTER_H 
#define MYCOMPUTER_H 

class MyComputer
{
 public:
    MyComputer();
    
    void rebuildDrives();
    
    static QList<HDrive> driveList;
    
    QIcon getDriveIcon( HDrive *drive );
    QIcon getDirIcon( QString filename );
    QIcon getFileIcon( QString filename );

    QIcon getIcon( QString filename );
};
#endif

